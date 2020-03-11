#pragma once
#include "ImageProcess.h"

// NoiseDlg 对话框
#define MAX_THREAD 8
#define MAX_SPAN 15

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
	virtual BOOL OnInitDialog();
	void AddNoise_WIN();
	void ImageCopy(CImage* pImgSrc, CImage* pImgDrt);
	afx_msg LRESULT OnNoiseThreadMsgReceived(WPARAM wParam, LPARAM lParam);

	CImage* m_pImgSrc;
	CImage* m_pProcessedImg;
	CStatic mOriginalPictureControl, mProcessedPictureControl;
	CTime startTime;
	int m_nThreadNum;
	ThreadParam* m_pThreadParam;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOpenOriginal();
	static UINT Update(void* p);
	afx_msg void OnPaint();
	
	afx_msg void OnBnClickedButtonProcess();
	CButton m_CheckLoop;
};
