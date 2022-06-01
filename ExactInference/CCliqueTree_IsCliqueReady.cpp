/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CCliqueTree_IsReady.cpp
//��  �ܣ�		������Ƿ����
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��04��01��
//��  �£�		2021��04��03��
//��  �£�		2021��05��18��
//��  �ȣ�		110��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC��׼ͷ�ļ�
#include "CCliqueTree.h"							//������ȷ������ͷ�ļ�
#include "Helper.h"									//��������ͷ�ļ�


//��  �ƣ�		IsCliqueReady()
//��  �ܣ�		������Ƿ����
//��  ����		unsigned int,map<unsigned int, set<unsigned int>>&
//				��ID���ȴ�����Ϣ����
//����ֵ��		bool
//				���Ƿ������
bool CCliqueTree::IsCliqueReady(fid_t nCliqueID, const fidsetmap& WaitedMessages) const
{
	const fidset& msg = WaitedMessages.at(nCliqueID);
	return msg.empty() || IsAllSEPSetExisted(nCliqueID, msg);
}

//��  �ƣ�		IsAllSEPSetExisted()
//��  �ܣ�		����Ƿ����и���Ѿ�����
//��  ����		unsigned int,set<unsigned int>&
//				��ID���ȴ�����Ϣ����
//����ֵ��		bool
//				�Ƿ�����ĸ���Ѿ����ڣ�
bool CCliqueTree::IsAllSEPSetExisted(fid_t nID, const fidset& WaitedMessages) const
{
	return std::ranges::all_of(WaitedMessages,
		[=](fid_t nStartID) { return IsAllSEPSetExisted_Helper(nStartID, nID); });
}

//��  �ƣ�		IsAllSEPSetExisted_Helper()
//��  �ܣ�		����Ƿ����и���Ѿ����ڵĸ�������
//��  ����		unsigned int,unsigned int
//				�����ID���յ���ID
//����ֵ��		bool
//				�Ƿ����ڣ�
bool CCliqueTree::IsAllSEPSetExisted_Helper(fid_t nStartID, fid_t nID) const
{
	return std::ranges::any_of(m_SEPSets,
		[=](const SEP_SET& s) { return nStartID == s.nStartID && nID == s.nEndID; });
}