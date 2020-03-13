#pragma once
#include "ImageProcess.h"

// MedianFilterDlg 对话框
#define MAX_THREAD 8
#define MAX_SPAN 15
#define MAX_LOOP 10

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
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
//	void MedianFilter();
	void MedianFilter_WIN();
	void ImageCopy(CImage* pImgSrc, CImage* pImgDrt);

	CImage* m_pImgSrc;
	CImage* m_pProcessedImg;
	CStatic mOriginalPictureControl, mProcessedPictureControl;
	CTime startTime;
	int m_nThreadNum;
	int loopTime;
	ThreadParam* m_pThreadParam;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedMedianButtonOpenOriginal();
	afx_msg void OnBnClickedMedianButtonProcess();
	afx_msg void OnBnClickedMedianButtonSave();
	afx_msg LRESULT OnMedianThreadMsgReceived(WPARAM wParam, LPARAM lParam);
//	CButton m_CheckLoop;
	CEdit m_Output;
	CString outputStr;
	CStatic m_loopCountText;
	afx_msg void OnNMCustomdrawMedianSliderThreadNum(NMHDR* pNMHDR, LRESULT* pResult);
	CSliderCtrl m_SliderLoop;
	CStatic m_LoopNum;
	afx_msg void OnNMCustomdrawMedianSliderLoopTime(NMHDR* pNMHDR, LRESULT* pResult);
};
