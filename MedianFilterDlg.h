﻿#pragma once


// MedianFilterDlg 对话框

class MedianFilterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(MedianFilterDlg)

public:
	MedianFilterDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~MedianFilterDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MEDIAN_FILTER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
