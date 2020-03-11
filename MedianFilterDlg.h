#pragma once
#include "ImageProcess.h"

// MedianFilterDlg 对话框

class MedianFilterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(MedianFilterDlg)

public:
	MedianFilterDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~MedianFilterDlg();
	static UINT Update(void* p);
	

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MEDIAN_FILTER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnPaint();
	CImage* m_pImgSrc;
	CImage* m_pProcessedImg;
	CStatic mOriginalPictureControl, mProcessedPictureControl;
	DECLARE_MESSAGE_MAP()
};
