#pragma once


// CExactInferenceDlg �Ի���
class CExactInferenceDlg : public CDialogEx
{
public:
	CExactInferenceDlg(CWnd* pParent = NULL);

	// �Ի�������
	enum { IDD = IDD_EXACTINFERENCE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedButtonBnInit();
};
