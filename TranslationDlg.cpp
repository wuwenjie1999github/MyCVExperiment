// TranslationDlg.cpp: 实现文件
//

#include "pch.h"
#include "MyCVExperiment.h"
#include "TranslationDlg.h"
#include "afxdialogex.h"
#include "ImageProcess.h"
#include <opencv.hpp>
#include <regex>


// TranslationDlg 对话框

IMPLEMENT_DYNAMIC(TranslationDlg, CDialogEx)

TranslationDlg::TranslationDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TRANSLATION, pParent)
{
	m_pImgSrc = NULL;
}

TranslationDlg::~TranslationDlg()
{
}

UINT TranslationDlg::Update(void* p)
{
	while (1)
	{
		Sleep(200);
		TranslationDlg* dlg = (TranslationDlg*)p;
		if (dlg->m_pImgSrc != NULL)
		{
			int height;
			int width;
			CRect rect;
			CRect rect1;
			height = dlg->m_pImgSrc->GetHeight();
			width = dlg->m_pImgSrc->GetWidth();

			dlg->mOriginalPictureControl.GetClientRect(&rect);
			CDC* pDC = dlg->mOriginalPictureControl.GetDC();
			SetStretchBltMode(pDC->m_hDC, STRETCH_HALFTONE);

			if (width <= rect.Width() && height <= rect.Width())
			{
				rect1 = CRect(rect.TopLeft(), CSize(width, height));
				dlg->m_pImgSrc->StretchBlt(pDC->m_hDC, rect1, SRCCOPY);
			}
			else
			{
				float xScale = (float)rect.Width() / (float)width;
				float yScale = (float)rect.Height() / (float)height;
				float ScaleIndex = (xScale <= yScale ? xScale : yScale);
				rect1 = CRect(rect.TopLeft(), CSize((int)width * ScaleIndex, (int)height * ScaleIndex));
				dlg->m_pImgSrc->StretchBlt(pDC->m_hDC, rect1, SRCCOPY);
			}
			dlg->ReleaseDC(pDC);
		}
		/*if (dlg->m_pProcessedImg != NULL)
		{
			int height;
			int width;
			CRect rect;
			CRect rect1;
			height = dlg->m_pProcessedImg->GetHeight();
			width = dlg->m_pProcessedImg->GetWidth();

			dlg->mProcessedPictureControl.GetClientRect(&rect);
			CDC* pDC = dlg->mProcessedPictureControl.GetDC();
			SetStretchBltMode(pDC->m_hDC, STRETCH_HALFTONE);

			if (width <= rect.Width() && height <= rect.Width())
			{
				rect1 = CRect(rect.TopLeft(), CSize(width, height));
				dlg->m_pProcessedImg->StretchBlt(pDC->m_hDC, rect1, SRCCOPY);
			}
			else
			{
				float xScale = (float)rect.Width() / (float)width;
				float yScale = (float)rect.Height() / (float)height;
				float ScaleIndex = (xScale <= yScale ? xScale : yScale);
				rect1 = CRect(rect.TopLeft(), CSize((int)width * ScaleIndex, (int)height * ScaleIndex));
				dlg->m_pProcessedImg->StretchBlt(pDC->m_hDC, rect1, SRCCOPY);
			}
			dlg->ReleaseDC(pDC);
		}*/
	}
	return 0;
}

void TranslationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TRAN_ORI_PIC, mOriginalPictureControl);
	DDX_Control(pDX, IDC_TRAN_EDIT_SCALE, m_ScaleNum);
	DDX_Control(pDX, IDC_TRAN_EDIT_ROTATE, m_RotateDegree);
	DDX_Control(pDX, IDC_TRAN_COMBO_ROTATE_DIREC, m_RotateDirec);
}

BOOL TranslationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO: 在此添加额外的初始化代码
	CComboBox* rotateDirec = (CComboBox*)GetDlgItem(IDC_TRAN_COMBO_ROTATE_DIREC);
	rotateDirec->InsertString(0, _T("逆时针"));
	rotateDirec->InsertString(1, _T("顺时针"));
	rotateDirec->SetCurSel(0);

	m_ScaleNum.SetWindowTextW(_T("0.5"));
	m_RotateDegree.SetWindowTextW(_T("90"));

	rotateAngle = 0;

	AfxBeginThread((AFX_THREADPROC)&TranslationDlg::Update, this);
	return 0;
}

void TranslationDlg::OnPaint()
{

	CDialogEx::OnPaint();

	if (m_pImgSrc != NULL)
	{
		int height;
		int width;
		CRect rect;
		CRect rect1;
		height = m_pImgSrc->GetHeight();
		width = m_pImgSrc->GetWidth();

		mOriginalPictureControl.GetClientRect(&rect);
		CDC* pDC = mOriginalPictureControl.GetDC();
		SetStretchBltMode(pDC->m_hDC, STRETCH_HALFTONE);

		if (width <= rect.Width() && height <= rect.Width())
		{
			rect1 = CRect(rect.TopLeft(), CSize(width, height));
			m_pImgSrc->StretchBlt(pDC->m_hDC, rect1, SRCCOPY);
		}
		else
		{
			float xScale = (float)rect.Width() / (float)width;
			float yScale = (float)rect.Height() / (float)height;
			float ScaleIndex = (xScale <= yScale ? xScale : yScale);
			rect1 = CRect(rect.TopLeft(), CSize((int)width * ScaleIndex, (int)height * ScaleIndex));
			m_pImgSrc->StretchBlt(pDC->m_hDC, rect1, SRCCOPY);
		}
		ReleaseDC(pDC);
	}

	/*if (m_pProcessedImg != NULL)
	{
		int height;
		int width;
		CRect rect;
		CRect rect1;
		height = m_pProcessedImg->GetHeight();
		width = m_pProcessedImg->GetWidth();

		mProcessedPictureControl.GetClientRect(&rect);
		CDC* pDC = mProcessedPictureControl.GetDC();
		SetStretchBltMode(pDC->m_hDC, STRETCH_HALFTONE);

		if (width <= rect.Width() && height <= rect.Width())
		{
			rect1 = CRect(rect.TopLeft(), CSize(width, height));
			m_pProcessedImg->StretchBlt(pDC->m_hDC, rect1, SRCCOPY);
		}
		else
		{
			float xScale = (float)rect.Width() / (float)width;
			float yScale = (float)rect.Height() / (float)height;
			float ScaleIndex = (xScale <= yScale ? xScale : yScale);
			rect1 = CRect(rect.TopLeft(), CSize((int)width * ScaleIndex, (int)height * ScaleIndex));
			m_pProcessedImg->StretchBlt(pDC->m_hDC, rect1, SRCCOPY);
		}
		ReleaseDC(pDC);
	}*/
}


BEGIN_MESSAGE_MAP(TranslationDlg, CDialogEx)
	ON_BN_CLICKED(IDC_TRAN_BUTTON_OPEN_ORIGINAL, &TranslationDlg::OnBnClickedTranButtonOpenOriginal)
	ON_BN_CLICKED(IDC_TRAN_BUTTON_PROCESS, &TranslationDlg::OnBnClickedTranButtonScale)
	ON_BN_CLICKED(IDC_TRAN_BUTTON_ROTATE, &TranslationDlg::OnBnClickedTranButtonRotate)
END_MESSAGE_MAP()


// TranslationDlg 消息处理程序

void TranslationDlg::OnBnClickedTranButtonOpenOriginal()
{

	// TODO: 在此添加控件通知处理程序代码
	TCHAR szFilter[] = _T("JPEG(*jpg)||*.jpg||*.bmp||*.png||TIFF(*.tif)||*.tif||All Files （*.*）||*.*||");
	CString filePath("");

	CFileDialog fileOpenDialog(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);
	if (fileOpenDialog.DoModal() == IDOK)
	{
		VERIFY(filePath = fileOpenDialog.GetPathName());
		CString strFilePath(filePath);
		//		mEditInfo.SetWindowTextW(strFilePath);	//在文本框中显示图像路径

		if (m_pImgSrc != NULL)
		{
			m_pImgSrc->Destroy();
			delete m_pImgSrc;
		}
		m_pImgSrc = new CImage();
		m_pImgSrc->Load(strFilePath);

		m_pHiddenImg = new CImage();
		ImageCopy(m_pImgSrc, m_pHiddenImg);

		this->Invalidate();


	}
}


void TranslationDlg::OnBnClickedTranButtonScale()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	m_ScaleNum.GetWindowTextW(str);
	if (str.IsEmpty())
	{
		CString emptyWarning(_T("输入倍数不能为空。"));
		AfxMessageBox(emptyWarning);
		return;
	}
	else {
		if (m_pImgSrc == NULL) {
			CString warning(_T("请先打开图片。"));
			AfxMessageBox(warning);
			return;
		}
		std::regex reg("^([0-9]{1,}[.]?[0-9]*)$");
		std::string str1 = CT2A(str.GetString());
		if (std::regex_match(str1, reg))
		{
			float scaleNum = _ttof(str);
			ImageProcess::scale(m_pImgSrc, scaleNum, scaleNum);
		}
		else
		{
			CString wrongFormatWaring(_T("参数格式有误。"));
			AfxMessageBox(wrongFormatWaring);
			return;
		}
	}
	
	/*HDC dc = m_pImgSrc->GetDC();
	SetStretchBltMode(dc, HALFTONE);
	m_pImgSrc->StretchBlt(dc, 0, 0, m_pImgSrc->GetWidth() / 2, m_pImgSrc->GetHeight() / 2);
	m_pImgSrc->ReleaseDC();*/
}

void TranslationDlg::OnBnClickedTranButtonRotate()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	m_RotateDegree.GetWindowTextW(str);
	if (str.IsEmpty())
	{
		CString emptyWarning(_T("输入角度不能为空。"));
		AfxMessageBox(emptyWarning);
		return;
	}
	else {
		if (m_pImgSrc == NULL || m_pHiddenImg == NULL) {
			CString warning(_T("请先打开图片。"));
			AfxMessageBox(warning);
			return;
		}
		std::regex reg("^([-]?[0-9]{1,}[.]?[0-9]*)$");
		std::string str1 = CT2A(str.GetString());
		if (std::regex_match(str1, reg))
		{
			float degree = _ttof(str);
			CComboBox* rotateDirec = (CComboBox*)GetDlgItem(IDC_TRAN_COMBO_ROTATE_DIREC);
			int direc = rotateDirec->GetCurSel();
			rotateAngle = direc == 0 ? rotateAngle + degree : rotateAngle - degree;

			//ImageCopy(m_pHiddenImg, m_pImgSrc);
			ImageProcess::rotate(m_pHiddenImg, m_pImgSrc, rotateAngle);
		}
		else
		{
			CString wrongFormatWaring(_T("参数格式有误。"));
			AfxMessageBox(wrongFormatWaring);
			return;
		}
	}
}

LRESULT TranslationDlg::OnTranslationScaleThreadMsgReceived(WPARAM wParam, LPARAM lParam)
{	
	ImageCopy(m_pImgSrc, m_pHiddenImg);
	rotateAngle = 0;
	this->Invalidate();
	
	return 0;
}

LRESULT TranslationDlg::OnTranslationRotateThreadMsgReceived(WPARAM wParam, LPARAM lParam)
{
	this->Invalidate();
	return 0;
}




void TranslationDlg::ImageCopy(CImage* pImgSrc, CImage* pImgDrt)
{
	int MaxColors = pImgSrc->GetMaxColorTableEntries();
	RGBQUAD* ColorTab;
	ColorTab = new RGBQUAD[MaxColors];

	CDC* pDCsrc, * pDCdrc;
	if (!pImgDrt->IsNull())
	{
		pImgDrt->Destroy();
	}
	pImgDrt->Create(pImgSrc->GetWidth(), pImgSrc->GetHeight(), pImgSrc->GetBPP(), 0);

	if (pImgSrc->IsIndexed())
	{
		pImgSrc->GetColorTable(0, MaxColors, ColorTab);
		pImgDrt->SetColorTable(0, MaxColors, ColorTab);
	}

	pDCsrc = CDC::FromHandle(pImgSrc->GetDC());
	pDCdrc = CDC::FromHandle(pImgDrt->GetDC());
	pDCdrc->BitBlt(0, 0, pImgSrc->GetWidth(), pImgSrc->GetHeight(), pDCsrc, 0, 0, SRCCOPY);
	pImgSrc->ReleaseDC();
	pImgDrt->ReleaseDC();
	delete ColorTab;
}
