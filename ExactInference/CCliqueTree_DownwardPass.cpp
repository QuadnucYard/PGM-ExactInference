/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CCliqueTree_DownwardPass.cpp
//��  �ܣ�		�ɸ������´�����Ϣ
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��04��04��
//��  �£�		2021��05��18��
//��  �ȣ�		110��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC��׼ͷ�ļ�
#include "CCliqueTree.h"							//������ȷ������ͷ�ļ�
#include "Helper.h"									//��������ͷ�ļ�


//��  �ƣ�		DownwardPass()
//��  �ܣ�		�ɸ������´�����Ϣ
//��  ����		��
//����ֵ��		��
void CCliqueTree::DownwardPass()
{	
	//////////////////////////////////////////////////////////////////
	//����1�������ŵȴ�����Ϣ����
	map <unsigned int, set<unsigned int>> CliqueWaitedMessages;
	CreateCliqueWaitedMessages_Downward(CliqueWaitedMessages);


	//////////////////////////////////////////////////////////////////
	//����2�����ù�����ȣ�ʹ�����������´�����Ϣ
	//����OPEN�б��CLOSED��
	queue <unsigned int> OPEN;
	set<unsigned int> CLOSED;

	//��ʼ��OPEN��
	OPEN.push(m_nRootID);

	//���OPEN���Ƿ�Ϊ��
	while (OPEN.size() > 0)
	{
		//����
		unsigned int nID = OPEN.front();
		OPEN.pop();

		//����CLOSED��
		CLOSED.insert(nID);

		//���Һ��
		set<unsigned int> Children = GetChildren(nID);
		//����Ƿ��к��
		if (Children.size() == 0)
		{
			//������Ƿ����
			if(IsCliqueReady(nID, CliqueWaitedMessages))
			{
				//����������������Ϣ
				ReceiveMessages(nID, CliqueWaitedMessages);
			}
		}
		else
		{
			//����Ƿ���ں�̣����������
			for (set<unsigned int>::iterator it = Children.begin(); it != Children.end(); it++)
			{
				//��ȡ��̽��
				unsigned int nChildID = *it;

				//����̽ڵ��Ƿ���CLOSED������Ѿ����ڣ�����Ҫ���
				if (!qy::ranges::includes(CLOSED, nChildID) &&
					IsCliqueReady(nID, CliqueWaitedMessages))
				{
					//������Ϣ
					ReceiveMessages(nID, CliqueWaitedMessages);

					//�򸸽ڵ㷢����Ϣ
					SendCliqueMessage_Downward(nChildID, nID);

					//��ӵ�OPEN��
					OPEN.push(nChildID);
				}
			}
		}
	}
}

//��  �ƣ�		GetChildren()
//��  �ܣ�		��ȡ����
//��  ����		unsigned int
//				��ID
//����ֵ��		set<unsigned int>
//				�ŵĺ���ID����
set<unsigned int> CCliqueTree::GetChildren(unsigned int nID)
{
	//��˫�׵����Ӽ��ϵ�ӳ���в���
	map<unsigned int, set<unsigned int>>::iterator it = m_Parent2Childs.find(nID);
	
	if (it != m_Parent2Childs.end())
	{
		//����ҵ��Ļ����򷵻غ���ID����
		return it->second;
	}
}