////////////////////////////////////////////////////////////////////////////////
// CFactorTree_Read_QueryCT.cpp
// ��ȡ����Clique�Ĳ�ѯ���񡣰�����Ե�ڵ㡢�����ڵ��ID��ֵID
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CCliqueTree_IO.h"


//��ȡ������ѯ���񡣰�����ѯ�ڵ㡢�����ڵ�
CCliqueTree::QueryList CCliqueTreeReader::Read_Query(const std::string& filename)
{
	namespace fs = std::filesystem;
	CCliqueTree::QueryList queries;

#ifndef USE_YAML

	fs::path sPath = fs::current_path() / "Data" / (filename + ".xml");
	if (!fs::exists(sPath))
	{
		throw std::runtime_error("�ļ������ڣ�" + filename + ".xml");
	}

	TiXmlDocument aDoc(sPath.string().c_str());
	if (!aDoc.LoadFile())
	{
		throw std::runtime_error("���ļ�ʧ�ܣ�" + filename + ".xml");
	}

	//��ȡ�����
	TiXmlElement* pQueries = aDoc.RootElement();
	for (auto& pQuery : pQueries)
	{
		CCliqueTree::CTQuery ct_query;

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

		queries.push_back(std::move(ct_query));
	}

	aDoc.Clear();


#else

	fs::path sPath = fs::current_path() / "Data" / (filename + ".yaml");
	YAML::Node doc = YAML::LoadFile(sPath.string());

	for (auto q : doc["queries"]) {
		queries.emplace_back(
			q["marginal"].as<fidmap>(fidmap {}) | std::views::transform(CCliqueTree::GroundingVariable::fromPair) | qy::views::to<CCliqueTree::GVarList>,
			q["given"].as<fidmap>(fidmap {}) | std::views::transform(CCliqueTree::GroundingVariable::fromPair) | qy::views::to<CCliqueTree::GVarList>
		);
	}

#endif // USE_YAML

	return queries;
}