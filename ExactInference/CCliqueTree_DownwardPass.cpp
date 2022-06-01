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
	std::queue<fid_t> OPEN;
	std::set<fid_t> CLOSED;

	OPEN.push(m_nRootID);

	//���OPEN���Ƿ�Ϊ��
	while (OPEN.size() > 0)
	{
		//����
		fid_t nID = OPEN.front();
		OPEN.pop();
		CLOSED.insert(nID);

		//���Һ��
		const auto& Children = m_Parent2Childs[nID];
		//����Ƿ��к��
		if (Children.size() == 0)
		{
			//������Ƿ����
			if (IsCliqueReady(nID, CliqueWaitedMessages))
			{
				//����������������Ϣ
				ReceiveMessages(nID, CliqueWaitedMessages);
			}
		}
		else
		{
			//����������
			for (fid_t nChildID : Children)
			{

				//����̽ڵ��Ƿ���CLOSED������Ѿ����ڣ�����Ҫ���
				if (!CLOSED.contains(nChildID) &&
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
