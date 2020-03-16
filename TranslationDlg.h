#pragma once


// TranslationDlg 对话框

class TranslationDlg : public CDialogEx
{
	DECLARE_DYNAMIC(TranslationDlg)

public:
	TranslationDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~TranslationDlg();
	static UINT Update(void* p);

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TRANSLATION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();

	CImage* m_pImgSrc;
	CImage* m_pHiddenImg;
	CStatic mOriginalPictureControl, mProcessedPictureControl;
	float rotateAngle;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedTranButtonOpenOriginal();
	afx_msg void OnBnClickedTranButtonScale();
	afx_msg LRESULT OnTranslationScaleThreadMsgReceived(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnTranslationRotateThreadMsgReceived(WPARAM wParam, LPARAM lParam);
	CEdit m_ScaleNum;
	CEdit m_RotateDegree;
	CComboBox m_RotateDirec;
	afx_msg void OnBnClickedTranButtonRotate();
	void ImageCopy(CImage* pImgSrc, CImage* pImgDrt);
};
