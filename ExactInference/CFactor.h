/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CFactor.h
//功  能：		定义因子类
//开发者：		高志强
//日  期：		2021年03月12日
//更  新：		2021年03月13日
//更  新：		2021年03月29日
//长  度：		210行
/////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <map>							//map头文件
#include <set>							//set头文件
#include <string>						//string头文件
#include <list>							//list头文件
#include <vector>						//vector头文件
#include <algorithm>					//algorithm类头文件
#include <numeric>						//numeric类头文件
#include <sstream>						//sstream类头文件
#include <fstream>						//fstream类头文件
#include <time.h>						//时间函数类头文件
#include "math.h"						//数学函数头文件
#include "Helper.h"						//辅助函数头文件


//声明命名空间
using namespace std;					//使用标准命名空间


//定义因子行
typedef struct
{
	vector<unsigned int> ValueIDs;								//01 变量值ID的列表，按照变量ID列表的顺序排列
	double fValue;												//02 因子的值
}FACTOR_ROW;


//定义因子类
class CFactor
{
	//构造函数与析构函数
public:
	CFactor();													//构造函数
	~CFactor();													//析构函数

	//公有方法
public:
	//初始化
	void SetFactorVariableIDs(vector<unsigned int>&);			//设置因子的变量ID列表
	void SetFactorRow(vector<unsigned int>&, double&);			//设置因子行的值
	//访问
	vector<unsigned int> GetFactorVariableIDs();				//获取变量ID列表
	//操作
	void ReduceGivenVariable(unsigned int, unsigned int);		//因子化简。消除给定变量ID、和变量值ID
	void SumOutVariable(unsigned int);								//因子求和掉给定变量ID
	void Normalize();											//因子归一化
	//查询
	double Query(vector<unsigned int>&,vector<unsigned int>&);	//根据给定变量ID集合、变量值ID的集合，获取具体查询的概率值

	//重载因子积
	CFactor operator*(const CFactor& second)
	{
		//定义新的、待返回的因子
		CFactor factor;


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//步骤1：求两个因子的交，即相同变量ID的集合		
		//定义相同变量ID，从第首因子到第尾因子位置的映射。例如第3个变量对应于第5个变量
		map<unsigned int, unsigned int> FirstToSeconds;

		//步骤1.1：遍历首因子的变量ID
		for (unsigned int i = 0; i <m_VariableIDs.size(); i++)
		{
			//获取首变量ID
			unsigned int nFirstVariableID = m_VariableIDs[i];

			//遍历尾因子的变量ID
			for (unsigned int j = 0; j < second.m_VariableIDs.size(); j++)
			{
				//获取尾变量ID
				unsigned int nSecondVariableID = second.m_VariableIDs[j];

				//检查两个变量ID是否相等
				if (nFirstVariableID == nSecondVariableID)
				{
					//添加到相同变量、从首因子指向尾因子的位置映射
					//注意：采用从位置到位置的映射，而不是从变量ID到变量ID的映射
					FirstToSeconds.insert(make_pair(i, j));
				}
			}
		}
		
		//步骤1.2：获取尾因子中和首因子相同变量的位置集合
		set<unsigned int> RedundantSeconds;
		for (map<unsigned int, unsigned int>::iterator it = FirstToSeconds.begin(); it != FirstToSeconds.end(); it++)
		{
			//添加到相同变量的位置集合
			RedundantSeconds.insert(it->second);
		}

		
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//步骤2：直接拼接
		//检查是否有相同变量ID
		if (FirstToSeconds.size() == 0)//情况一：两个因子没有相同变量，则直接拼接
		{
			//步骤2.1：直接拼接变量值ID
			for (unsigned int i = 0; i < m_FactorRows.size(); i++)
			{
				for (unsigned int j = 0; j < second.m_FactorRows.size(); j++)
				{
					//定义新的因子行
					FACTOR_ROW factor_row;

					//添加变量值的ID集合
					factor_row.ValueIDs = m_FactorRows[i].ValueIDs;//赋予首因子值的序列
					//添加尾因子值的序列
					for (unsigned int m = 0; m < second.m_FactorRows[j].ValueIDs.size(); m++)
					{
						//添加尾因子值的ID
						factor_row.ValueIDs.push_back(second.m_FactorRows[j].ValueIDs[m]);
					}

					//计算因子行的值。需要采用惩罚
					factor_row.fValue = m_FactorRows[i].fValue*second.m_FactorRows[j].fValue;

					//将因子行添加到因子
					factor.m_FactorRows.push_back(factor_row);
				}
			}

			//步骤2.2：拼接变量ID
			factor.m_VariableIDs = m_VariableIDs;//初始化为首因子的变量ID序列
			//添加尾因子的变量ID
			for (unsigned int i = 0; i < second.m_VariableIDs.size(); i++)
			{
				//添加尾因子的变量ID
				factor.m_VariableIDs.push_back(second.m_VariableIDs[i]);
			}
		}
		////////////////////////////////////////////////////////////////////
		//步骤3：间接拼接
		else //情况二：两个因子有相同变量，则间接拼接
		{
			//步骤3.1：间接拼接
			for (unsigned int i = 0; i < m_FactorRows.size(); i++)
			{
				for (unsigned int j = 0; j < second.m_FactorRows.size(); j++)
				{
					//检查对应的变量值的ID是否相等
					if (IsConsistentValueID(m_FactorRows[i], second.m_FactorRows[j], FirstToSeconds))
					{
						//定义因子行
						FACTOR_ROW factor_row;
						factor_row.ValueIDs = m_FactorRows[i].ValueIDs;//初始化因子行的值ID序列
						//遍历尾因子的值
						for (unsigned int m = 0; m < second.m_FactorRows[j].ValueIDs.size(); m++)
						{
							//检查列是否在相同变量集合中
							if (!IsINTInSet(m, RedundantSeconds))
							{
								//添加尾因子的列
								factor_row.ValueIDs.push_back(second.m_FactorRows[j].ValueIDs[m]);
							}
						}

						//计算获取因子行的值
						factor_row.fValue = m_FactorRows[i].fValue*second.m_FactorRows[j].fValue;

						//添加因子行到因子
						factor.m_FactorRows.push_back(factor_row);
					}
				}
			}

			//步骤3.2：添加变量ID的列表
			factor.m_VariableIDs = m_VariableIDs;
			//遍历尾因子
			for (unsigned int i = 0; i < second.m_VariableIDs.size(); i++)
			{
				//检查尾因子变量ID的位置是否属于相同变量ID集合
				if (!IsINTInSet(i, RedundantSeconds))
				{
					//添加尾因子的变量ID
					factor.m_VariableIDs.push_back(second.m_VariableIDs[i]);
				}
			}
		}

		//返回因子
		return factor;
	};		
	
	//私有方法
private:
	//在因子积时判断两行是否可以合并
	bool IsConsistentValueID(const FACTOR_ROW&, const FACTOR_ROW&, map<unsigned int, unsigned int>&);	//检查两行是否兼容	
	//在求和时将因子的值合并到首行
	void MergeIntoFirstRow(FACTOR_ROW&);
	
	//私有数据
private:	
	vector<unsigned int> m_VariableIDs;					//因子变量ID列表
	vector<FACTOR_ROW> m_FactorRows;					//因子行的列表
};