// CParamDialog.cpp: 구현 파일
//

#include "pch.h"
#include "MFC_OpenCV.h"
#include "afxdialogex.h"
#include "CParamDialog.h"


// CParamDialog 대화 상자

IMPLEMENT_DYNAMIC(CParamDialog, CDialogEx)

CParamDialog::CParamDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_VAR, pParent)
{

}

CParamDialog::~CParamDialog()
{
}

void CParamDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strAngle);
    DDX_Text(pDX, IDC_EDIT1, m_strScale);
    DDX_Text(pDX, IDC_EDIT1, m_strResize);
    DDX_Text(pDX, IDC_EDIT1, m_strRanDefCnt);
    DDX_Text(pDX, IDC_EDIT1, m_strShift);
}

void CParamDialog::OnPaint()
{
    // 다이얼로그의 기본 그리기 처리
    CDialogEx::OnPaint();

    // Edit Control에 중앙 정렬된 텍스트를 수동으로 그리기
    CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT1);  // 각도 입력 Edit Control
    if (pEdit != nullptr)
    {
        CString strText;
        pEdit->GetWindowText(strText);

        if (!strText.IsEmpty())
        {
            // Edit Control의 그리기 영역 가져오기
            CRect rect;
            pEdit->GetClientRect(&rect);

            // DC 얻기
            CDC* pDC = pEdit->GetDC();
            if (pDC)
            {
                // 글꼴 설정
                CFont* pOldFont = pDC->SelectObject(pEdit->GetFont());

                // 텍스트 높이를 계산
                SIZE sizeText;
                GetTextExtentPoint32(pDC->m_hDC, strText, strText.GetLength(), &sizeText);

                // 텍스트를 중앙으로 배치
                int yPos = (rect.Height() - sizeText.cy) / 2;
                rect.top = yPos;

                // 중앙에 텍스트 그리기
                pDC->DrawText(strText, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

                // 리소스 해제
                pDC->SelectObject(pOldFont);
                pEdit->ReleaseDC(pDC);
            }
        }
    }
}
BEGIN_MESSAGE_MAP(CParamDialog, CDialogEx)
    ON_WM_PAINT()
    ON_BN_CLICKED(IDC_BTN_CHECK, &CParamDialog::OnBnClickedBtnCheck)
END_MESSAGE_MAP()

void CParamDialog::OnBnClickedBtnCheck()
{
    CString strValue;
    GetDlgItemText(IDC_EDIT1, strValue);
    OnOK();
}
