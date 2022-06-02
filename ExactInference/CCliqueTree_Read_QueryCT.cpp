////////////////////////////////////////////////////////////////////////////////
// CFactorTree_Read_QueryCT.cpp
// ��ȡ����Clique�Ĳ�ѯ���񡣰�����Ե�ڵ㡢�����ڵ��ID��ֵID
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CCliqueTree.h"


//��ȡ������ѯ���񡣰�����ѯ�ڵ㡢�����ڵ�
void CCliqueTree::Read_QueryCT()
{
	namespace fs = std::filesystem;

#ifndef USE_YAML

	fs::path sPath = fs::current_path() / "Data" / "CliqueTree_Query.xml";
	if (!fs::exists(sPath))
	{
		return;
	}

	TiXmlDocument aDoc(sPath.string().c_str());
	if (!aDoc.LoadFile())
	{
		AfxMessageBox(_T("��CliqueTree_Query.xmlʧ��:"));
		return exit(0);
	}

	//��ȡ�����
	TiXmlElement* pQueries = aDoc.RootElement();
	for (auto& pQuery : pQueries)
	{
		CTQuery ct_query;

		//����1����ȡ��Եָ��
		TiXmlElement* pMarginal = pQuery.FirstChildElement();
		//�������б�Ե
		for (auto& pVariable : pMarginal)
		{
			ct_query.MarginalVariables.emplace_back(
				GetAttributeI(pVariable, "ID"),
				GetAttributeI(pVariable, "VALUE")
			);
		}

		//����2����ȡ��������ָ��
		TiXmlElement* pGiven = pMarginal->NextSiblingElement();
		//������ѯ����
		for (auto& pVariable : pGiven)
		{
			ct_query.GivenVariables.emplace_back(
				GetAttributeI(pVariable, "ID"),
				GetAttributeI(pVariable, "VALUE")
			);
		}

		m_CTQueries.push_back(std::move(ct_query));
	}

	aDoc.Clear();


#else

	fs::path sPath = fs::current_path() / "Data" / "CliqueTree_Query.yaml";
	YAML::Node doc = YAML::LoadFile(sPath.string());

	for (auto q : doc["queries"]) {
		m_CTQueries.emplace_back(
			q["marginal"].as<fidmap>(fidmap {}) | std::views::transform(GroundingVariable::fromPair) | qy::views::to<GVarList>,
			q["given"].as<fidmap>(fidmap {}) | std::views::transform(GroundingVariable::fromPair) | qy::views::to<GVarList>
		);
	}

#endif // USE_YAML

}