// NoiseDlg.cpp: 实现文件
//

#include "pch.h"
#include "MyCVExperiment.h"
#include "NoiseDlg.h"
#include "afxdialogex.h"
#include "TabCtrl.h"


// NoiseDlg 对话框

IMPLEMENT_DYNAMIC(NoiseDlg, CDialogEx)

NoiseDlg::NoiseDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NOISE, pParent)
{
	m_pImgSrc = NULL;
	m_pProcessedImg = NULL;
}

NoiseDlg::~NoiseDlg()
{
}

void NoiseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ORI_PIC, mOriginalPictureControl);
	DDX_Control(pDX, IDC_PROCESS_PIC, mProcessedPictureControl);
}


BEGIN_MESSAGE_MAP(NoiseDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_OPEN_ORIGINAL, &NoiseDlg::OnBnClickedButtonOpenOriginal)
END_MESSAGE_MAP()


// NoiseDlg 消息处理程序


void NoiseDlg::OnBnClickedButtonOpenOriginal()
{
	// TODO: 在此添加控件通知处理程序代码
	TCHAR szFilter[] = _T("JPEG(*jpg)|*.jpg|*.bmp|*.png|TIFF(*.tif)|*.tif|All Files （*.*）|*.*||");
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
		
		this->Invalidate();

	}
}

UINT NoiseDlg::Update(void* p)
{
	while (1)
	{
		Sleep(200);
		NoiseDlg* dlg = (NoiseDlg*)p;
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
		if (dlg->m_pProcessedImg != NULL)
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
		}
	}
	return 0;
}

void NoiseDlg::OnPaint()
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

	if (m_pProcessedImg != NULL)
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
	}
}
