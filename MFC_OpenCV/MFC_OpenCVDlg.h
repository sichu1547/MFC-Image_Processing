#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <afxdlgs.h>  // CFileDialog 클래스
#include <atlconv.h>
#include <iostream>
#include <string>
#include <Shlwapi.h>  // PathFileExists 함수 사용을 위해 필요
#include <immintrin.h> // AVX
#include <cstdlib>
#include <ctime> //Random
#pragma comment(lib, "Shlwapi.lib")  // 링크 설정
// MFC_OpenCVDlg.h: 헤더 파일
//

#pragma once
using namespace std;
using namespace cv;
// CMFCOpenCVDlg 대화 상자
class CMFCOpenCVDlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCOpenCVDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	CComboBox m_comboFunctions;
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_OPENCV_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	Mat m_orgImg, m_ChangeImg;
	afx_msg void OnBnClickedBtnload();
	afx_msg void OnCbnSelchangeFuncList();
	void ImageFiltering(int iKernelW, int iKernelH);
	void ImageInverse();
	void ImageRotation(Mat& src, double angle);
	void ImageResize(Mat& src, double dSize);
	void Mirroring(Mat& src, bool bTD);
	Mat AddRandomDefect(Mat src, int iCnt);
	void DetectDefect(Mat orgImg, Mat defImg);
	void DetectShiftedDefects(Mat orgImg, Mat defImg, int iShiftX, int iShiftY);
	void DetectPatternDefect(const Mat& img1, const Mat& img2);
	bool IsImageFile(const CString& filePath);
	afx_msg void OnBnClickedBtnProc();
	CStatic m_picOrg;
	afx_msg void OnBnClickedBtnChange();
	afx_msg void OnStnClickedStaticSrcimg();
	CString m_strSrcImg;
	CString m_strBeforeSrcImg, m_strBeforeScale, m_strScale;
	double m_dBeforeAngle, m_Angle;
	Mat m_DefImg;
	afx_msg void OnBnClickedBtnHist();
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnBnClickedBtnDef();
	afx_msg void OnBnClickedBtnDtt1();
	afx_msg void OnBnClickedBtnDtts();
};
