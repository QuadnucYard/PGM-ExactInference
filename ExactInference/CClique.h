/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CClique.h
//功  能：		定义团类
//开发者：		高志强
//日  期：		2021年03月30日
//更  新：		2021年04月11日。和因子类相比，增加了因子除重载
//更  新：		2021年04月12日
//更  新：		2021年05月18日
//长  度：		300行
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


//定义团行
typedef struct
{
	vector<unsigned int> ValueIDs;								//01 变量值ID的列表，按照变量ID列表的顺序排列
	double fValue;												//02 团行的值
}CLIQUE_ROW;


//定义团类
class CClique
{
	//构造函数与析构函数
public:
	CClique();													//构造函数
	~CClique();													//析构函数

	//公有方法
public:
	//初始化
	void SetCliqueID(unsigned int&);							//设置团的ID
	void SetCliqueVariableIDs(vector<unsigned int>&);			//设置团的变量ID列表
	void SetCliqueRow(vector<unsigned int>&, double&);			//设置团行的值
	//访问
	vector<unsigned int> GetCliqueVariableIDs();				//获取团的变量ID列表
	set<unsigned int> GetVariableIDs();							//返回变量ID集合
	unsigned int GetID();										//获取团的ID
	//操作
	void ReduceGivenVariable(unsigned int, unsigned int);		//团化简。消除给定变量ID、和变量值ID
	void SumOutVariable(unsigned int);							//团求和掉给定变量ID
	void Normalize();											//团归一化
	//查询
	double Query(vector<unsigned int>&, vector<unsigned int>&);	//根据给定变量ID集合、变量值ID的集合，获取具体查询的概率值

	//重载因子积
	CClique operator*(const CClique& second)
	{
		//定义新的、待返回的因子团
		CClique clique;

		////////////////////////////////////////////////////////////////////////
		//注意：在因子积中要保留团ID。团是不变的，这和因子不同。因子是动态变化的
		clique.m_nCliqueID = m_nCliqueID;
		////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//步骤1：求两个团的交，即相同变量ID的集合		
		//定义相同变量ID，从第首团到第尾团位置的映射。例如第3个变量对应于第5个变量
		map<unsigned int, unsigned int> FirstToSeconds;

		//步骤1.1：遍历首团的变量ID
		for (unsigned int i = 0; i <m_VariableIDs.size(); i++)
		{
			//获取首变量ID
			unsigned int nFirstVariableID = m_VariableIDs[i];

			//遍历尾团的变量ID
			for (unsigned int j = 0; j < second.m_VariableIDs.size(); j++)
			{
				//获取尾变量ID
				unsigned int nSecondVariableID = second.m_VariableIDs[j];

				//检查两个变量ID是否相等
				if (nFirstVariableID == nSecondVariableID)
				{
					//添加到相同变量、从首团指向尾团的位置映射
					//注意：采用从位置到位置的映射，而不是从变量ID到变量ID的映射
					FirstToSeconds.insert(make_pair(i, j));
				}
			}
		}

		//步骤1.2：获取尾团中和首团相同变量的位置集合
		set<unsigned int> RedundantSeconds;
		for (map<unsigned int, unsigned int>::iterator it = FirstToSeconds.begin(); it != FirstToSeconds.end(); it++)
		{
			//添加到相同变量的位置集合
			RedundantSeconds.insert(it->second);
		}


		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//步骤2：直接拼接
		//检查是否有相同变量ID
		if (FirstToSeconds.size() == 0)//情况一：两个团没有相同变量，则直接拼接
		{
			//步骤2.1：直接拼接变量值ID
			for (unsigned int i = 0; i < m_CliqueRows.size(); i++)
			{
				for (unsigned int j = 0; j < second.m_CliqueRows.size(); j++)
				{
					//定义新的团行
					CLIQUE_ROW clique_row;

					//添加变量值的ID集合
					clique_row.ValueIDs = m_CliqueRows[i].ValueIDs;//赋予首团值的序列
					//添加尾团值的序列
					for (unsigned int m = 0; m < second.m_CliqueRows[j].ValueIDs.size(); m++)
					{
						//添加尾团值的ID
						clique_row.ValueIDs.push_back(second.m_CliqueRows[j].ValueIDs[m]);
					}

					//计算团行的值。需要采用乘法
					clique_row.fValue = m_CliqueRows[i].fValue*second.m_CliqueRows[j].fValue;

					//将团行添加到团
					clique.m_CliqueRows.push_back(clique_row);
				}
			}

			//步骤2.2：拼接变量ID
			clique.m_VariableIDs = m_VariableIDs;//初始化为首团的变量ID序列
			//添加尾团的变量ID
			for (unsigned int i = 0; i < second.m_VariableIDs.size(); i++)
			{
				//添加尾团的变量ID
				clique.m_VariableIDs.push_back(second.m_VariableIDs[i]);
			}
		}
		////////////////////////////////////////////////////////////////////
		//步骤3：间接拼接
		else //情况二：两个团有相同变量，则间接拼接
		{
			//步骤3.1：间接拼接
			for (unsigned int i = 0; i < m_CliqueRows.size(); i++)
			{
				for (unsigned int j = 0; j < second.m_CliqueRows.size(); j++)
				{
					//检查对应的变量值的ID是否相等
					if (IsConsistentValueID(m_CliqueRows[i], second.m_CliqueRows[j], FirstToSeconds))
					{
						//定义因子行
						CLIQUE_ROW clique_row;
						clique_row.ValueIDs = m_CliqueRows[i].ValueIDs;//初始化团行的值ID序列
						//遍历尾团的值
						for (unsigned int m = 0; m < second.m_CliqueRows[j].ValueIDs.size(); m++)
						{
							//检查列是否在相同变量集合中
							if (!IsINTInSet(m, RedundantSeconds))
							{
								//添加尾团的列
								clique_row.ValueIDs.push_back(second.m_CliqueRows[j].ValueIDs[m]);
							}
						}

						//计算获取团行的值
						clique_row.fValue = m_CliqueRows[i].fValue*second.m_CliqueRows[j].fValue;

						//添加因子行到因子
						clique.m_CliqueRows.push_back(clique_row);
					}
				}
			}

			//步骤3.2：添加变量ID的列表
			clique.m_VariableIDs = m_VariableIDs;
			//遍历尾团
			for (unsigned int i = 0; i < second.m_VariableIDs.size(); i++)
			{
				//检查尾团变量ID的位置是否属于相同变量ID集合
				if (!IsINTInSet(i, RedundantSeconds))
				{
					//添加尾团的变量ID
					clique.m_VariableIDs.push_back(second.m_VariableIDs[i]);
				}
			}
		}

		//返回团
		return clique;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////
	//重载因子除
	CClique operator/(const CClique& second)
	{
		//定义新的、待返回的团
		CClique clique;

		///////////////////////////
		//注意：保持已有的变量集
		clique.m_VariableIDs = m_VariableIDs;
		///////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//步骤1：求两个团的交，即相同变量ID的集合		
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

		/////////////////////////////////////////////////////////////////////////////////
		//步骤2：因子除
		//说明：被除团的辖域一定包含除团的辖域
		for (unsigned int i = 0; i < m_CliqueRows.size(); i++)
		{
			for (unsigned int j = 0; j < second.m_CliqueRows.size(); j++)
			{
				//检查对应的变量值的ID是否相等
				if (IsConsistentValueID(m_CliqueRows[i], second.m_CliqueRows[j], FirstToSeconds))
				{
					//定义团行
					CLIQUE_ROW clique_row;
					
					//初始化团行的值ID序列
					clique_row.ValueIDs = m_CliqueRows[i].ValueIDs;					
					//计算获取因子行的值
					clique_row.fValue = m_CliqueRows[i].fValue/second.m_CliqueRows[j].fValue;

					//添加团行到团
					clique.m_CliqueRows.push_back(clique_row);
				}
			}
		}

		//返回团
		return clique;
	};

	//私有方法
private:
	//在因子积时判断两行是否可以合并
	bool IsConsistentValueID(const CLIQUE_ROW&, const CLIQUE_ROW&, map<unsigned int, unsigned int>&);	//检查两行是否兼容	
	//在求和时将因子的值合并到首行
	void MergeIntoFirstRow(CLIQUE_ROW&);

	//私有数据
private:
	unsigned int m_nCliqueID;							//团ID
	vector<unsigned int> m_VariableIDs;					//团变量ID列表
	vector<CLIQUE_ROW> m_CliqueRows;					//团行的列表
};