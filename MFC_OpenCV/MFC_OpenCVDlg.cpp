
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
	ON_BN_CLICKED(IDC_BTN_HIST, &CMFCOpenCVDlg::OnBnClickedBtnHist)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CMFCOpenCVDlg::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_DEF, &CMFCOpenCVDlg::OnBnClickedBtnDef)
	ON_BN_CLICKED(IDC_BTN_DTT1, &CMFCOpenCVDlg::OnBnClickedBtnDtt1)
	ON_BN_CLICKED(IDC_BTN_DTTS, &CMFCOpenCVDlg::OnBnClickedBtnDtts)
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
	m_comboFunctions.AddString(_T("Mirror_TD"));
	m_comboFunctions.AddString(_T("Mirror_LR"));
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
			replace(strp.begin(), strp.end(), '\\', '/');
			m_orgImg = imread(strp, IMREAD_GRAYSCALE);
			imshow("org", m_orgImg);

			if (!PathFileExists(filePath) && m_orgImg.empty())
				AfxMessageBox(_T("파일이 존재하지 않습니다. 경로를 확인하세요."));

			CString strSrc = L"SRC Image : Original Image";
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

	for (int i = 0; i <= iTotalCnt - iSimdWidth; i += iSimdWidth)
	{
		__m256i srcVec = _mm256_loadu_si256((__m256i*)(srcPtr + i));
		__m256i invVec = _mm256_sub_epi8(vec255, srcVec);
		_mm256_storeu_si256((__m256i*)(dstPtr + i), invVec);
	}
	for (int i = iTotalCnt - iSimdWidth; i < iTotalCnt; i++) 
	{
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
	rotMatrix.ptr<double>(0)[2] += bbox.width / 2.0 - center.x;
	rotMatrix.ptr<double>(1)[2] += bbox.height / 2.0 - center.y;
	// 회전 변환 적용
	warpAffine(src, dst, rotMatrix, bbox.size(), INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0)); // 이미지 회전, INTER_LINEAR : 선형보간, BORDER_CONSTANT: 빈공간 처리방식(상수), 빈 공간 채울 색상

	m_ChangeImg = dst;

	imshow("Rotation", dst);
	AfxMessageBox(_T("Rotation"));
}
void CMFCOpenCVDlg::Mirroring(Mat& src, bool bTD)
{
	int iWidth = src.cols;
	int iHeight = src.rows;
	int iSimdWidth = 32;

	Mat dst(iHeight, iWidth, src.type());

	uchar* srcPtr = src.data;
	uchar* dstPtr = dst.data;
	if (bTD)
	{
		// 행을 기준으로 반전
		for (int j = 0; j <= iHeight / 2; j++)
		{
			uchar* srcTopRow = srcPtr + j * iWidth;                       // 위쪽 행
			uchar* srcBottomRow = srcPtr + (iHeight - j - 1) * iWidth;    // 아래쪽 행
			uchar* dstTopRow = dstPtr + j * iWidth;
			uchar* dstBottomRow = dstPtr + (iHeight - j - 1) * iWidth;

			int i = 0;

			for (; i <= iWidth - iSimdWidth; i += iSimdWidth)
			{
				__m256i topRowVec = _mm256_loadu_si256((__m256i*)(srcTopRow + i));
				__m256i bottomRowVec = _mm256_loadu_si256((__m256i*)(srcBottomRow + i));

				_mm256_storeu_si256((__m256i*)(dstBottomRow + i), topRowVec);
				_mm256_storeu_si256((__m256i*)(dstTopRow + i), bottomRowVec);
			}
			// 나머지(%simd pixel)
			for (; i < iWidth; i++)
			{
				dstTopRow[i] = srcBottomRow[i];
				dstBottomRow[i] = srcTopRow[i];
			}
		}
		
		imshow("MirrorUptoDown", dst);
		AfxMessageBox(_T("MirrorUptoDown"));
	}
	else
	{
		flip(src, dst, 1); // 0 -> 상하반전
		imshow("Mirror L->R", dst);
		AfxMessageBox(_T("Mirror L->R"));
	}

	m_ChangeImg = dst;
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
			else if (selectedText == "Mirror_TD")
			{
				Mirroring(m_orgImg, TRUE);
				CString strChange = L"Top -> Down(Mirror) Image";

				m_strSrcImg = strChange;
			}
			else if (selectedText == "Mirror_LR")
			{
				Mirroring(m_orgImg, FALSE);
				CString strChange = L"Left -> Right(Mirror) Image";

				m_strSrcImg = strChange;
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
		CString strText;
		strText.Format(_T("SRC Image : %s"), m_strSrcImg);
		SetDlgItemText(IDC_STATIC_SRCIMG, strText);
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


void CMFCOpenCVDlg::OnBnClickedBtnHist()
{
	int iHistSize = 256;
	float fRange[] = { 0, 256 };
	const float* fHistRange = { fRange };

	Mat dst;
	calcHist(&m_orgImg, 1, 0, Mat(), dst, 1, &iHistSize, &fHistRange);

	int iHist_w = 512; int iHist_h = 400;
	int bin_w = cvRound((double)iHist_w / iHistSize);

	int iHistArea = 50;

	Mat histImage(iHist_h + iHistArea, iHist_w, CV_8UC1, Scalar(0));

	// 정규화 (시각화를 위해)
	normalize(dst, dst, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	// 히스토그램 그리기
	for (int i = 1; i < iHistSize; i++)
	{
		line(histImage, Point(bin_w * (i - 1), iHist_h - cvRound(dst.at<float>(i - 1))),
			Point(bin_w * (i), iHist_h - cvRound(dst.at<float>(i))),
			Scalar(255), 2, 8, 0);
	}

	putText(histImage, "0", Point(0, iHist_h + 30), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255), 1);
	putText(histImage, "128", Point(iHist_w / 2 - 20, iHist_h + 30), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255), 1);
	putText(histImage, "255", Point(iHist_w - 40, iHist_h + 30), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255), 1);

	imshow("Source image", m_orgImg);
	imshow("Histogram", histImage);
}


void CMFCOpenCVDlg::OnBnClickedBtnSave()
{
	CFileDialog saveDlg(FALSE, _T("*.jpg"), _T("SavedImage"),
		OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY,
		_T("JPEG Files (*.jpg)|*.jpg|PNG Files (*.png)|*.png|All Files (*.*)|*.*||"),
		this);

	if (saveDlg.DoModal() == IDOK)
	{
		CString strPath = saveDlg.GetPathName();

		string strSavePath = (CT2CA(strPath));
		replace(strSavePath.begin(), strSavePath.end(), '\\', '/');

		if (m_orgImg.empty())
		{
			AfxMessageBox(_T("No Image"));
		}
		else
		{
			if (imwrite(strSavePath, m_orgImg))
			{
				AfxMessageBox(_T("Save Image"));
			}
			else
			{
				AfxMessageBox(_T("Failed to save"));
			}
		}
	}
}

Mat CMFCOpenCVDlg::AddRandomDefect(Mat src, int iCnt)
{
	vector<Rect> vDefPos;
	Mat dst = src.clone();
	int iDefCnt = iCnt;

	for (int i = 0; i < iDefCnt; i++)
	{
		srand((unsigned int)time(nullptr)); // 랜덤 시드 설정

		BOOL bOverlapping = FALSE;
		int iPattern = rand() % 3;
		int iX = rand() % src.cols;
		int iY = rand() % src.rows;
		int iW = rand() % 50 + 50;
		int iH = rand() % 50 + 50;
		Rect newDefect = Rect(iX, iY, iW, iH);
		Scalar color(rand() % 256, rand() % 256, rand() % 256);

		if (iDefCnt - iCnt < 3)
		{
			for (const auto& defect : vDefPos)
			{
				if ((newDefect & defect).area() > 0) { // 중복 영역 확인
					iDefCnt++;
					bOverlapping = TRUE;
				}
			}
		}

		if (!bOverlapping)
		{
			vDefPos.push_back(newDefect);

			if (iPattern == 0)
				rectangle(dst, Rect(iX, iY, iW, iH), color, -1);
			else if (iPattern == 1)
				circle(dst, Point(iX, iY), iW / 2, color, -1);
			else
				line(dst, Point(iX, iY), Point(iX + iW, iY + iH), color, 3);
		}
	}
	imshow("Def Image", dst);

	return dst;
}

void CMFCOpenCVDlg::OnBnClickedBtnDef()
{

	CParamDialog paramDlg;
	if (paramDlg.DoModal() == IDOK)
	{
		CString strCnt = paramDlg.m_strRanDefCnt;
		int iCnt = _ttoi(strCnt);
		m_DefImg = AddRandomDefect(m_orgImg, iCnt);
	}					
}

void CMFCOpenCVDlg::DetectDefect(Mat orgImg, Mat defImg)
{
	Mat grayDiff, thresh;

	absdiff(orgImg, defImg, grayDiff);


	threshold(grayDiff, thresh, 30, 255, THRESH_BINARY);
	//adaptiveThreshold(grayDiff, thresh, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 11, 2); // 동적 임계값 설정, 조명 또는 결함 위치 변화하는 경우 사용, 주변 픽셀의 평균값 등을 기준으로 임계값 설정

	vector<vector<Point>> contours;
	findContours(thresh, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	for (const auto& contour : contours)
	{
		Rect defectArea = boundingRect(contour);
		rectangle(defImg, defectArea, Scalar(0, 0, 255), 2);
	}

	imshow("Result Image", defImg);
}

void CMFCOpenCVDlg::DetectShiftedDefects(Mat orgImg, Mat defImg, int iShiftX, int iShiftY) 
{
	Mat shiftedDefect;

	// 시프트이미지 생성
	Mat shiftMatrix1 = (Mat_<double>(2, 3) << 1, 0, iShiftX, 0, 1, iShiftY);
	warpAffine(defImg, shiftedDefect, shiftMatrix1, defImg.size());

	Ptr<ORB> orb = ORB::create();
	vector<KeyPoint> keypoints1, keypoints2;
	Mat descriptors1, descriptors2;

	// 특징점과 디스크립터 추출
	orb->detectAndCompute(orgImg, Mat(), keypoints1, descriptors1);
	orb->detectAndCompute(shiftedDefect, Mat(), keypoints2, descriptors2);

	// BF 매처로 특징점 매칭
	BFMatcher matcher(NORM_HAMMING);
	vector<DMatch> matches;
	matcher.match(descriptors1, descriptors2, matches);

	// 좋은 매칭점만 추려내기 (거리가 짧은 매칭점)
	double max_dist = 0; double min_dist = 100;
	for (int i = 0; i < descriptors1.rows; i++) {
		double dist = matches[i].distance;
		if (dist < min_dist) min_dist = dist;
		if (dist > max_dist) max_dist = dist;
	}

	vector<DMatch> good_matches;
	for (int i = 0; i < descriptors1.rows; i++) {
		if (matches[i].distance <= max(2 * min_dist, 0.02)) {
			good_matches.push_back(matches[i]);
		}
	}

	// 변환 행렬 계산
	vector<Point2f> pts1, pts2;
	for (size_t i = 0; i < good_matches.size(); i++) {
		pts1.push_back(keypoints1[good_matches[i].queryIdx].pt);
		pts2.push_back(keypoints2[good_matches[i].trainIdx].pt);
	}

	// 시프트 수치 계산 변환 행렬 추정
	Mat shiftMatrix = estimateAffinePartial2D(pts1, pts2);
	shiftMatrix.ptr<double>(0)[2] = -shiftMatrix.ptr<double>(0)[2];
	shiftMatrix.ptr<double>(1)[2] = -shiftMatrix.ptr<double>(1)[2];

	Mat alignedDefectImg;
	warpAffine(shiftedDefect, alignedDefectImg, shiftMatrix, shiftedDefect.size());

	Mat diff;
	absdiff(orgImg, alignedDefectImg, diff);

	Mat thresh;
	threshold(diff, thresh, 30, 255, THRESH_BINARY);
	//adaptiveThreshold(diff, thresh, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 11, 2); //동적 이진화

	vector<vector<Point>> contours;
	Mat CroppedImage;
	Rect roi;	

	if (shiftMatrix.ptr<double>(0)[2] > 0) //시프트로 인한 이미지 손실 구간 자르기
		roi = Rect(shiftMatrix.ptr<double>(0)[2], shiftMatrix.ptr<double>(1)[2], thresh.cols - shiftMatrix.ptr<double>(0)[2], thresh.rows - shiftMatrix.ptr<double>(1)[2]);
	else
		roi = Rect(0, 0, thresh.cols + shiftMatrix.ptr<double>(0)[2], thresh.rows + shiftMatrix.ptr<double>(1)[2]);

	CroppedImage = thresh(roi);
	findContours(CroppedImage, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	for (const auto& contour : contours) {		
		if (contour.size() > 30)
		{
			Rect boundingBox = boundingRect(contour);
			rectangle(shiftedDefect, boundingBox, Scalar(0, 0, 255), 2);
		}
	}

	imshow("Result", shiftedDefect);
}


void CMFCOpenCVDlg::DetectPatternDefect(const Mat& img1, const Mat& img2)
{
	if (img1.empty() || img2.empty()) {
		AfxMessageBox(_T("유효하지 않은 이미지입니다."));
		return;
	}

	Mat gray1 = img1, gray2 = img2;

	// 주파수 도메인 변환
	Mat dftImg1, dftImg2;
	gray1.convertTo(gray1, CV_32F);
	gray2.convertTo(gray2, CV_32F);
	dft(gray1, dftImg1, DFT_COMPLEX_OUTPUT);
	dft(gray2, dftImg2, DFT_COMPLEX_OUTPUT);

	// 패턴 강조를 위한 고주파 필터링
	Mat highFreq1, highFreq2;
	Mat lowPassMask = getGaussianKernel(dftImg1.rows, 30, CV_32F) * getGaussianKernel(dftImg1.cols, 30, CV_32F).t(); // 저주파 성분 제거
	Mat complexMask[] = { lowPassMask, lowPassMask }; // 실수, 허수 채널 생성
	Mat lowPassFilter;
	merge(complexMask, 2, lowPassFilter);

	multiply(dftImg1, lowPassFilter, highFreq1);  // 필터 적용
	multiply(dftImg2, lowPassFilter, highFreq2);

	// 역변환
	Mat filteredImg1, filteredImg2;
	idft(highFreq1, filteredImg1, DFT_SCALE | DFT_REAL_OUTPUT);
	idft(highFreq2, filteredImg2, DFT_SCALE | DFT_REAL_OUTPUT);
	normalize(filteredImg1, filteredImg1, 0, 255, NORM_MINMAX);
	normalize(filteredImg2, filteredImg2, 0, 255, NORM_MINMAX);
	filteredImg1.convertTo(filteredImg1, CV_8U);
	filteredImg2.convertTo(filteredImg2, CV_8U);

	Mat diff;
	absdiff(filteredImg1, filteredImg2, diff);

	Mat defectMask;
	threshold(diff, defectMask, 30, 255, THRESH_BINARY);

	Mat result;
	img1.copyTo(result);
	vector<std::vector<Point>> contours;
	findContours(defectMask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	for (const auto& contour : contours) {
		Rect rect = boundingRect(contour);
		rectangle(result, rect, Scalar(0, 0, 255), 2);  
	}

	imshow("Org Image", img1);
	imshow("Filtered Image 1", filteredImg1);
	imshow("Filtered Image 2", filteredImg2);
	imshow("Result", result);
}

void CMFCOpenCVDlg::OnBnClickedBtnDtt1()
{
	if(!m_orgImg.empty() && !m_DefImg.empty())
		DetectPatternDefect(m_orgImg, m_DefImg);
}


void CMFCOpenCVDlg::OnBnClickedBtnDtts()
{
	CParamDialog paramDlg;

	if (paramDlg.DoModal() == IDOK)
	{
		CString strSize = paramDlg.m_strScale;
		int iPos = strSize.Find(_T(","));
		CString strX = strSize.Left(iPos);
		CString strY = strSize.Mid(iPos + 1).Trim(); // Trim : 공백 제거
		int iShiftX = _ttoi(strX), iShiftY = _ttoi(strY);

		if (!m_orgImg.empty() && !m_DefImg.empty())
			DetectShiftedDefects(m_orgImg, m_DefImg, iShiftX, iShiftY);

	}
}
