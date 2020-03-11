// MedianFilterDlg.cpp: 实现文件
//

#include "pch.h"
#include "MyCVExperiment.h"
#include "MedianFilterDlg.h"
#include "afxdialogex.h"
#include "ImageProcess.h"


// MedianFilterDlg 对话框

IMPLEMENT_DYNAMIC(MedianFilterDlg, CDialogEx)

MedianFilterDlg::MedianFilterDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MEDIAN_FILTER, pParent)
{

}

MedianFilterDlg::~MedianFilterDlg()
{
}

UINT MedianFilterDlg::Update(void* p)
{
	while (1)
	{
		Sleep(200);
		MedianFilterDlg* dlg = (MedianFilterDlg*)p;
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

void MedianFilterDlg::OnPaint()
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

void MedianFilterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MedianFilterDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// MedianFilterDlg 消息处理程序
