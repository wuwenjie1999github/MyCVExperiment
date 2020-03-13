// NoiseDlg.cpp: 实现文件
//

#include "pch.h"
#include "MyCVExperiment.h"
#include "NoiseDlg.h"
#include "afxdialogex.h"
#include "stdafx.h"



// NoiseDlg 对话框

IMPLEMENT_DYNAMIC(NoiseDlg, CDialogEx)

NoiseDlg::NoiseDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NOISE, pParent)
{
	m_pImgSrc = NULL;
	m_pProcessedImg = NULL;
	m_nThreadNum = 1;
	m_pThreadParam = new ThreadParam[MAX_THREAD];
	outputStr = "";
	srand(time(0));
}

NoiseDlg::~NoiseDlg()
{
}

void NoiseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ORI_PIC, mOriginalPictureControl);
	DDX_Control(pDX, IDC_PROCESS_PIC, mProcessedPictureControl);
	DDX_Control(pDX, IDC_CHECK_LOOP, m_CheckLoop);
	DDX_Control(pDX, IDC_OUTPUT, m_Output);
}

BOOL NoiseDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO: 在此添加额外的初始化代码

	CComboBox* cmb_thread = ((CComboBox*)GetDlgItem(IDC_PROCESS_METHOD));
	cmb_thread->InsertString(0, _T("WIN多线程"));
	cmb_thread->InsertString(1, _T("OpenMP"));
	cmb_thread->InsertString(2, _T("CUDA"));
	cmb_thread->SetCurSel(0);

	AfxBeginThread((AFX_THREADPROC)&NoiseDlg::Update, this);

	m_Output.SetReadOnly(TRUE);

	return TRUE;
}


BEGIN_MESSAGE_MAP(NoiseDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_OPEN_ORIGINAL, &NoiseDlg::OnBnClickedButtonOpenOriginal)
	ON_BN_CLICKED(IDC_BUTTON_PROCESS, &NoiseDlg::OnBnClickedButtonProcess)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &NoiseDlg::OnBnClickedButtonSave)
END_MESSAGE_MAP()


// NoiseDlg 消息处理程序


void NoiseDlg::OnBnClickedButtonOpenOriginal()
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


void NoiseDlg::OnBnClickedButtonProcess()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_pImgSrc != NULL) {
		CComboBox* cmb_thread = ((CComboBox*)GetDlgItem(IDC_PROCESS_METHOD));
		int thread = cmb_thread->GetCurSel();
		CButton* clb_loop = ((CButton*)GetDlgItem(IDC_CHECK_LOOP));
		int loop = clb_loop->GetCheck() == 0 ? 1 : 100;
		startTime = CTime::GetTickCount();
		switch (thread)
		{
		case 0:	// WIN多线程
			m_pProcessedImg = new CImage();
			ImageCopy(m_pImgSrc, m_pProcessedImg);
			this->Invalidate();
			AddNoise_WIN();


			break;
		case 1:	// openmp
		{
			m_pProcessedImg = new CImage();
			ImageCopy(m_pImgSrc, m_pProcessedImg);
			this->Invalidate();
			int subLength = m_pProcessedImg->GetWidth() * m_pProcessedImg->GetHeight() / m_nThreadNum;

#pragma omp parallel for num_threads(m_nThreadNum)
			for (int i = 0; i < m_nThreadNum; ++i)
			{
				m_pThreadParam[i].startIndex = i * subLength;
				m_pThreadParam[i].endIndex = i != m_nThreadNum - 1 ?
					(i + 1) * subLength - 1 : m_pProcessedImg->GetWidth() * m_pProcessedImg->GetHeight() - 1;
				m_pThreadParam[i].src = m_pProcessedImg;
				ImageProcess::addNoise(&m_pThreadParam[i]);
			}
		}
		break;
		case 2:	// cuda
			break;
		default:
			break;
		}
	}
	else {
		CString warning("请先打开要处理的图片。");
		AfxMessageBox(warning);
	}

}

void NoiseDlg::AddNoise_WIN()
{
	int subLength = m_pProcessedImg->GetWidth() * m_pProcessedImg->GetHeight() / m_nThreadNum;
	for (int i = 0; i < m_nThreadNum; ++i)
	{
		m_pThreadParam[i].startIndex = i * subLength;
		m_pThreadParam[i].endIndex = i != m_nThreadNum - 1 ?
			(i + 1) * subLength - 1 : m_pProcessedImg->GetWidth() * m_pProcessedImg->GetHeight() - 1;
		m_pThreadParam[i].src = m_pProcessedImg;
		AfxBeginThread((AFX_THREADPROC)&ImageProcess::addNoise, &m_pThreadParam[i]);
	}
	
}

void NoiseDlg::ImageCopy(CImage* pImgSrc, CImage* pImgDrt)
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


LRESULT NoiseDlg::OnNoiseThreadMsgReceived(WPARAM wParam, LPARAM lParam)
{
	static int tempCount = 0;
	static int tempProcessCount = 0;
	CButton* clb_circulation = ((CButton*)GetDlgItem(IDC_CHECK_LOOP));
	int circulation = clb_circulation->GetCheck() == 0 ? 1 : 100;
	if ((int)wParam == 1)
		tempCount++;
	CString threadStr;
	threadStr.Format(_T("线程%d退出。\r\n"), tempCount);
	outputStr.Append(threadStr);
	m_Output.SetWindowTextW(outputStr);
	int lines = m_Output.GetLineCount();
	int counts = outputStr.GetLength();
	m_Output.LineScroll(lines, 0);
	m_Output.SetSel(counts, counts);
	if (m_nThreadNum == tempCount)
	{
		//CTime endTime = CTime::GetTickCount();
		//CString timeStr;
		//timeStr.Format(_T("耗时:%dms", endTime - startTime));
		tempCount = 0;
		tempProcessCount++;
		
		if ((tempProcessCount - 1) % 10 == 0) {
			CString processStr;
			processStr.Format(_T("第%d次循环。\r\n"), tempProcessCount);
			outputStr.Append(processStr);
			m_Output.SetWindowTextW(outputStr);
			int lines = m_Output.GetLineCount();
			int counts = outputStr.GetLength();
			m_Output.LineScroll(lines, 0);
			m_Output.SetSel(counts, counts);
		}

		if (tempProcessCount < circulation)
			AddNoise_WIN();
		else
		{
			tempProcessCount = 0;
			CTime endTime = CTime::GetTickCount();
			CString timeStr;
			timeStr.Format(_T("处理%d次,耗时:%dms\r\n==============\r\n"), circulation, endTime - startTime);
			//AfxMessageBox(timeStr);
			outputStr.Append(timeStr);
			m_Output.SetWindowTextW(outputStr);
			int lines = m_Output.GetLineCount();
			int counts = outputStr.GetLength();
			m_Output.LineScroll(lines, 0);
			m_Output.SetSel(counts, counts);
		}
		//	AfxMessageBox(timeStr);
	}
	return 0;
}


void NoiseDlg::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_pProcessedImg == NULL) {
		CString warning(_T("不能保存空图片。"));
		AfxMessageBox(warning);
		return;
	}
	TCHAR szFilter[] = _T("JPEG(*jpg)||*.jpg||*.bmp||*.png||TIFF(*.tif)||*.tif||All Files （*.*）||*.*||");
	CString filePath, fileExtension, picName;
	//CString picName(_T("Processed_Picture"));
	CFileDialog fileDlg(FALSE, _T(""), _T("Processed_Picture"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	picName = fileDlg.m_ofn.lpstrFile;
	if (IDOK == fileDlg.DoModal()) {
		filePath = fileDlg.GetPathName();
//		if (fileDlg.m_ofn.nFileExtension == NULL) {
			switch (fileDlg.m_ofn.nFilterIndex)
			{
			case 1:
			case 2:
				fileExtension = "jpg";
				break;
			case 3:
				fileExtension = "bmp";
				break;
			case 4:
				fileExtension = "png";
				break;
			case 5:
			case 6:
				fileExtension = "tif";
				break;
			default:
				break;
			}
//		}
		filePath = filePath + "." + fileExtension;
		m_pProcessedImg->Save(filePath);
	}
	
}
