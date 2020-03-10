#pragma once


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

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOpenOriginal();
};
