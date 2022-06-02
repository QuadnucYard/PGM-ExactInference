////////////////////////////////////////////////////////////////////////////////
// CBNSumProduct_Read_Query.cpp
// ��ȡ��ѯ���񡣰�����ѯ�ڵ㡢�����ڵ㡢�ڵ�ɾ��˳��
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CBNSumProduct.h"


//��ȡ��ѯ���񡣰�����ѯ�ڵ㡢�����ڵ㡢ɾ���ڵ�˳��
void CBNSumProduct::Read_Query()
{
	namespace fs = std::filesystem;

#ifndef USE_YAML

	fs::path sPath = fs::current_path() / "Data" / "BayesianNetwork_Query.xml";
	if (!fs::exists(sPath)) return;

	//���ļ�
	TiXmlDocument aDoc(sPath.string().c_str());
	if (!aDoc.LoadFile())
	{
		AfxMessageBox(_T("��BayesianNetwork_Query.xmlʧ��:"));
		return exit(0);
	}

	//��ȡ�����
	TiXmlElement* pRoot = aDoc.RootElement();
	for (TiXmlElement& pQuery : pRoot)
	{
		BNQuery query;

		//����1����ȡ��Եָ��
		TiXmlElement* pMarginal = pQuery.FirstChildElement();
		std::transform(begin(pMarginal), end(pMarginal), std::back_inserter(query.QueryVariables),
			[](TiXmlElement& pVariable) { return GroundingVariable(
				GetAttributeI(pVariable, "ID"),
				GetAttributeI(pVariable, "VALUE")
			); });

		//����2����ȡ��������ָ��
		TiXmlElement* pGiven = pMarginal->NextSiblingElement();
		std::transform(begin(pGiven), end(pGiven), std::back_inserter(query.GivenVariables),
			[](TiXmlElement& pVariable) { return GroundingVariable(
				GetAttributeI(pVariable, "ID"),
				GetAttributeI(pVariable, "VALUE")
			); });

		//����3����ȡɾ������˳��
		if (TiXmlElement* pEliminate = pGiven->NextSiblingElement(); pEliminate != NULL)
		{
			//��ȡɾ������ID�б�
			if (std::string sTemp = GetAttribute(pEliminate, "IDs"); sTemp != "")
			{
				query.EliminateVariables = sTemp
					| qy::views::tokenize(std::regex("[\\s,;]+"))
					| std::views::transform(stoi_)
					| qy::views::to<fidlist>;
			}
		}

		m_Queries.push_back(std::move(query));
	}

	aDoc.Clear();

#else

	fs::path sPath = fs::current_path() / "Data" / "BayesianNetwork_Query.yaml";
	YAML::Node doc = YAML::LoadFile(sPath.string());

	for (auto q : doc["queries"]) {
		m_Queries.emplace_back(
			q["marginal"].as<fidmap>(fidmap {}) | std::views::transform(GroundingVariable::fromPair) | qy::views::to<GVarList>,
			q["given"].as<fidmap>(fidmap {}) | std::views::transform(GroundingVariable::fromPair) | qy::views::to<GVarList>,
			q["eliminate"].as<fidlist>(fidlist {})
		);
	}

#endif // USE_YAML

}