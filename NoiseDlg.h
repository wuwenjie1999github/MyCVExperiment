#pragma once
#include "ImageProcess.h"

// NoiseDlg 对话框

class NoiseDlg : public CDialogEx
{
	DECLARE_DYNAMIC(NoiseDlg)

public:
	NoiseDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~NoiseDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NOISE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	CImage* m_pImgSrc;
	CImage* m_pProcessedImg;
	CStatic mOriginalPictureControl, mProcessedPictureControl;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOpenOriginal();
	UINT Update(void* p);
	afx_msg void OnPaint();
	
};
