#pragma once
#include "afxdialogex.h"


// CParamDialog 대화 상자

class CParamDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CParamDialog)

public:
	CParamDialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CParamDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VAR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	CString m_strAngle; // 각도
	CString m_strSize;
	afx_msg void OnBnClickedBtnCheck();
};
