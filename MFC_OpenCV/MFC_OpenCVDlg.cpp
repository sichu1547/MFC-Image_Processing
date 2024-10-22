
// MFC_OpenCVDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFC_OpenCV.h"
#include "MFC_OpenCVDlg.h"
#include "afxdialogex.h"
#include "CParamDialog.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCOpenCVDlg 대화 상자



CMFCOpenCVDlg::CMFCOpenCVDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_OPENCV_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCOpenCVDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FUNC_LIST, m_comboFunctions);
}

BEGIN_MESSAGE_MAP(CMFCOpenCVDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTNLOAD, &CMFCOpenCVDlg::OnBnClickedBtnload)
	ON_CBN_SELCHANGE(IDC_FUNC_LIST, &CMFCOpenCVDlg::OnCbnSelchangeFuncList)
	ON_BN_CLICKED(IDC_BTN_PROC, &CMFCOpenCVDlg::OnBnClickedBtnProc)
	ON_BN_CLICKED(IDC_BTN_CHANGE, &CMFCOpenCVDlg::OnBnClickedBtnChange)
	ON_STN_CLICKED(IDC_STATIC_SRCIMG, &CMFCOpenCVDlg::OnStnClickedStaticSrcimg)
END_MESSAGE_MAP()


// CMFCOpenCVDlg 메시지 처리기

BOOL CMFCOpenCVDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	m_comboFunctions.AddString(_T("Filtering"));
	m_comboFunctions.AddString(_T("Inverse"));
	m_comboFunctions.AddString(_T("Rotation"));
	m_comboFunctions.AddString(_T("Resize"));
	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.
	

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCOpenCVDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCOpenCVDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCOpenCVDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFCOpenCVDlg::OnBnClickedBtnload()
{
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, _T("All Files (*.*)|*.*||"), this);

	if (dlg.DoModal() == IDOK)
	{
		CString filePath = dlg.GetPathName();
		CStdioFile file;
		if (IsImageFile(filePath))
		{
			CString fileContent;			
			CString strPath = L"Image PATH: ";

			fileContent = strPath + filePath;						
			string strp = (CT2CA(filePath));
			std::replace(strp.begin(), strp.end(), '\\', '/');
			m_orgImg = imread(strp, IMREAD_GRAYSCALE);
			imshow("org", m_orgImg);
			std::string savePath = "C:/Users/dksk5/Pictures/saved_image.jpg"; // Save
			bool success = cv::imwrite(savePath, m_orgImg);

			if (!PathFileExists(filePath) && m_orgImg.empty())
				AfxMessageBox(_T("파일이 존재하지 않습니다. 경로를 확인하세요."));

			CString strSrc = L"Original Image";
			m_strBeforeSrcImg = strSrc;
			m_dBeforeAngle = 0.0, m_strBeforeScale = "";
			SetDlgItemText(IDC_STATIC_PATH, fileContent);
			SetDlgItemText(IDC_STATIC_SRCIMG, strSrc);
			//m_orgImg.release();
		}
		else
		{
			AfxMessageBox(_T("올바른 이미지 확장자가 아닙니다."));
		}
	}
}

bool CMFCOpenCVDlg::IsImageFile(const CString& filePath)
{
	CString ext = filePath.Right(filePath.GetLength() - filePath.ReverseFind(_T('.')) - 1);
	ext.MakeLower();

	if (ext == _T("jpg") || ext == _T("jpeg") || ext == _T("png") ||
		ext == _T("bmp") || ext == _T("gif") || ext == _T("tiff"))
	{
		return true; 
	}

	return false;
}

void CMFCOpenCVDlg::OnCbnSelchangeFuncList()
{

}
void CMFCOpenCVDlg::ImageFiltering(int iKernelW, int iKernelH)
{
	Mat blurredImage;
	if (iKernelW % 2 == 0)
		iKernelW += 1;
	if (iKernelH % 2 == 0)
		iKernelH += 1;
	GaussianBlur(m_orgImg, blurredImage, Size(iKernelW, iKernelH), 0); // Size -> Blur 커널 크기
	m_ChangeImg = blurredImage;
	imshow("Blurred Image", blurredImage);
	AfxMessageBox(_T("Gaussian Blur"));
}
void CMFCOpenCVDlg::ImageInverse()
{
	Mat InverseImg(m_orgImg.rows, m_orgImg.cols, CV_8UC1);
	__m256i vec255 = _mm256_set1_epi8(255);
	uchar* srcPtr = m_orgImg.data;
	uchar* dstPtr = InverseImg.data;
	int iTotalCnt = m_orgImg.total();
	int iSimdWidth = 32;

	for (int i = 0; i <= iTotalCnt - iSimdWidth; i+= iSimdWidth)
	{
		__m256i srcVec = _mm256_loadu_si256((__m256i*)(srcPtr + i));
		__m256i invVec = _mm256_sub_epi8(vec255, srcVec);
		_mm256_storeu_si256((__m256i*)(dstPtr + i), invVec);
	}
	for (int i = iTotalCnt - iSimdWidth; i < iTotalCnt; i++) {
		dstPtr[i] = 255 - srcPtr[i];
	}
	m_ChangeImg = InverseImg;
	imshow("Inverse Image", InverseImg);
	AfxMessageBox(_T("Inverse"));
}
void CMFCOpenCVDlg::ImageRotation(Mat& src, double angle)
{
	int iWidth = src.cols; 
	int iHeight = src.rows;

	Mat dst(iHeight, iWidth, src.type());
	dst.setTo(Scalar(0)); // Init GrayScale 0

	// 회전 중심
	Point2f center(iWidth / 2.0f, iHeight / 2.0f);
	// 회전 행렬 생성
	Mat rotMatrix = getRotationMatrix2D(center, angle, 1.0); // 1.0은 회전 후 이미지를 확대 또는 축소할 비율
	Rect2f bbox = RotatedRect(Point2f(), src.size(), angle).boundingRect2f();

	// 4. 회전 행렬에 바운딩 박스 크기에 맞추기 위한 이동 값을 적용
	rotMatrix.at<double>(0, 2) += bbox.width / 2.0 - center.x;
	rotMatrix.at<double>(1, 2) += bbox.height / 2.0 - center.y;
	// 회전 변환 적용
	warpAffine(src, dst, rotMatrix, bbox.size(), INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0)); // 이미지 회전, INTER_LINEAR : 선형보간, BORDER_CONSTANT: 빈공간 처리방식(상수), 빈 공간 채울 색상

	m_ChangeImg = dst;

	imshow("Rotation", dst);
	AfxMessageBox(_T("Rotation"));
}

void CMFCOpenCVDlg::OnBnClickedBtnProc()
{
	if (m_orgImg.empty())
	{
		AfxMessageBox(_T("이미지가 존재하지 않습니다."));
	}
	else
	{
		int iComboIndex = m_comboFunctions.GetCurSel();

		if (iComboIndex != CB_ERR)
		{
			CString selectedText;
			m_comboFunctions.GetLBText(iComboIndex, selectedText);  // 선택된 텍스트 가져오기

			if (selectedText == "Filtering")
			{
				CParamDialog paramDlg;
				
				CString strChange = L"Gaussian Image";
				if (paramDlg.DoModal() == IDOK)
				{
					if (m_strBeforeSrcImg = strChange)
						m_strSrcImg = L"Gaussian Image";
					else
						m_strSrcImg = m_strBeforeSrcImg;

					CString strSize = paramDlg.m_strScale;
					int iPos = strSize.Find(_T(","));
					CString strWidth = strSize.Left(iPos);
					CString strHeight = strSize.Mid(iPos + 1).Trim(); // Trim : 공백 제거
					int iWidth = _ttoi(strWidth), iHeight = _ttoi(strHeight);
					ImageFiltering(iWidth, iHeight);
				}				
			}
			else if (selectedText == "Inverse")
			{
				ImageInverse();
				CString strChange = L"Inverse Image";

				if (m_strSrcImg != strChange)
					m_strSrcImg = L"Inverse Image";
				else
					m_strSrcImg = m_strBeforeSrcImg;
			}
			else if (selectedText == "Rotation")
			{
				CParamDialog paramDlg;
				if (paramDlg.DoModal() == IDOK)
				{
					CString strAngle = paramDlg.m_strAngle;
					CString strChange;
					double dAngle = _ttof(strAngle);
					strChange.Format(L"Rotation Image Angle: %02f", dAngle + m_dBeforeAngle);
					m_strSrcImg = strChange;
					m_Angle = dAngle;
					ImageRotation(m_orgImg, dAngle);
				}
			}
			else if (selectedText == "Resize")
			{
				CParamDialog paramDlg;
				if (paramDlg.DoModal() == IDOK)
				{
					CString strScale = paramDlg.m_strScale;
					CString strChange;
					double dScale = _ttof(strScale);		
					if (m_strBeforeScale != "")
					{
						CString str = m_strBeforeScale + " -> " + strScale;
						strChange.Format(L"Resize Image Scale: %s", str);
						m_strScale = str;
					}
						
					else
					{
						strChange.Format(L"Resize Image Scale: %s", strScale);
						m_strScale = strScale;
					}
						
					m_strSrcImg = strChange;
					
					ImageResize(m_orgImg, dScale);
				}
			}
		}
		else
		{
			AfxMessageBox(_T("선택된 기능이 없습니다."));
		}
	}
}



void CMFCOpenCVDlg::OnBnClickedBtnChange()
{
	if(m_orgImg.empty())
		AfxMessageBox(_T("타겟 이미지가 존재하지 않습니다."));
	else
	{
		m_orgImg = m_ChangeImg;
		m_dBeforeAngle += m_Angle;
		m_strBeforeScale = m_strScale;
		m_strScale = "";
		m_Angle = 0;
		SetDlgItemText(IDC_STATIC_SRCIMG, m_strSrcImg);
		AfxMessageBox(_T("이미지가 변경되었습니다."));
	}

}
void CMFCOpenCVDlg::ImageResize(Mat& src, double dScale)
{
	Mat dst;
	resize(src, dst, Size(), dScale, dScale, dScale > 1 ? INTER_LINEAR : INTER_AREA); // 선형: 2x2 주변 픽셀을 사용한 선형 보간, 확대에 적합, Area: 영역 기반 보간으로 축소 시 품질 보증

	m_ChangeImg = dst;

	imshow("Resize", dst);
	AfxMessageBox(_T("Resize"));
}

void CMFCOpenCVDlg::OnStnClickedStaticSrcimg()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
