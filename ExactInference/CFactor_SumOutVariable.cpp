/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CFactor_SumOutVariable.cpp
//功  能：		根据给定变量，对因子求和
//开发者：		高志强
//日  期：		2021年03月13日
//更  新：		2021年03月23日
//更  新：		2021年03月29日
//长  度：		150行
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CFactor.h"


void CFactor::SumOutVariable(fid_t nVariableID)
{
	//检查是否找到变量ID
	if (size_t nRemovePos = qy::index_of(m_VariableIDs, nVariableID); nRemovePos != -1) 
	{
		//找到变量ID，需要进行求和化简

		//步骤1：化简变量ID的列表
		m_VariableIDs.erase(m_VariableIDs.begin() + nRemovePos);

		//步骤2：化简变量值的ID列表  删除行中冗余的变量值
		for (FACTOR_ROW& t : m_FactorRows)
			t.ValueIDs.erase(t.ValueIDs.begin() + nRemovePos);

		//步骤3：对因子中相应的行求和  把ValueIDs相同的行合并到第一次出现的行
		for (auto it = m_FactorRows.begin(); it != m_FactorRows.end();)
		{
			auto jt = std::find_if(m_FactorRows.begin(), it, [it](auto& t) {return t.ValueIDs == it->ValueIDs; });
			if (jt != it) {
				jt->fValue += it->fValue;
				it = m_FactorRows.erase(it);
			}
			else
			{
				it++;
			}
		}
	}
}
