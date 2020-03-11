#pragma once
#include <afxcmn.h>
#include "ImageProcess.h"
class TabCtrl :
	public CTabCtrl
{
	DECLARE_DYNAMIC(TabCtrl)
public:
	TabCtrl();
	virtual ~TabCtrl();

	void Init();
	void SetRectangle();


	
	CDialogEx* m_tabPages[2];

	int m_tabCurrent;
	int m_nNumberOfPages;
protected:
	DECLARE_MESSAGE_MAP();
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

