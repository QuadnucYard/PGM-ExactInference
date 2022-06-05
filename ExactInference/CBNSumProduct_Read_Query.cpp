////////////////////////////////////////////////////////////////////////////////
// CBNSumProduct_Read_Query.cpp
// ��ȡ��ѯ���񡣰�����ѯ�ڵ㡢�����ڵ㡢�ڵ�ɾ��˳��
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CBNSumProduct_IO.h"


//��ȡ��ѯ���񡣰�����ѯ�ڵ㡢�����ڵ㡢ɾ���ڵ�˳��
CBNSumProduct::QueryList CBNSumProductReader::Read_Query(const std::string& filename)
{
	namespace fs = std::filesystem;
	CBNSumProduct::QueryList queries;

#ifndef USE_YAML

	fs::path sPath = fs::current_path() / "Data" / (filename + ".xml");
	if (!fs::exists(sPath))
	{
		throw std::runtime_error("�ļ������ڣ�" + filename + ".xml");
	}

	//���ļ�
	TiXmlDocument aDoc(sPath.string().c_str());
	if (!aDoc.LoadFile())
	{
		throw std::runtime_error("���ļ�ʧ�ܣ�" + filename + ".xml");
	}

	//��ȡ�����
	TiXmlElement* pRoot = aDoc.RootElement();
	for (TiXmlElement& pQuery : pRoot)
	{
		CBNSumProduct::BNQuery query;

		//����1����ȡ��Եָ��
		TiXmlElement* pMarginal = pQuery.FirstChildElement();
		std::transform(begin(pMarginal), end(pMarginal), std::back_inserter(query.QueryVariables),
			[](TiXmlElement& pVariable) { return CBNSumProduct::GroundingVariable(
				GetAttributeI(pVariable, "ID"),
				GetAttributeI(pVariable, "VALUE")
			); });

		//����2����ȡ��������ָ��
		TiXmlElement* pGiven = pMarginal->NextSiblingElement();
		std::transform(begin(pGiven), end(pGiven), std::back_inserter(query.GivenVariables),
			[](TiXmlElement& pVariable) { return CBNSumProduct::GroundingVariable(
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

		queries.push_back(std::move(query));
	}

	aDoc.Clear();

#else

	fs::path sPath = fs::current_path() / "Data" / (filename + ".yaml");
	YAML::Node doc = YAML::LoadFile(sPath.string());

	for (auto q : doc["queries"]) {
		queries.emplace_back(
			q["marginal"].as<fidmap>(fidmap {}) | std::views::transform(CBNSumProduct::GroundingVariable::fromPair) | qy::views::to<CBNSumProduct::GVarList>,
			q["given"].as<fidmap>(fidmap {}) | std::views::transform(CBNSumProduct::GroundingVariable::fromPair) | qy::views::to<CBNSumProduct::GVarList>,
			q["eliminate"].as<fidlist>(fidlist {})
		);
	}

#endif // USE_YAML

	return queries;
}