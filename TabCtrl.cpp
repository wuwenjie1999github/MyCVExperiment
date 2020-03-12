#include "pch.h"
#include "TabCtrl.h"
#include "resource.h"

#include "NoiseDlg.h"
#include "MedianFilterDlg.h"

IMPLEMENT_DYNAMIC(TabCtrl, CTabCtrl)

TabCtrl::TabCtrl()
{
	/*m_tabPages[0] = new NoiseDlg;
	m_tabPages[1] = new MedianFilterDlg;*/
	noiseDlg = new NoiseDlg;
	medianFilterDlg = new MedianFilterDlg;

	m_nNumberOfPages = 2;

}

TabCtrl::~TabCtrl()
{
	/*for (int i = 0; i < m_nNumberOfPages; i++)
		delete m_tabPages[i];*/
	delete noiseDlg;
	delete medianFilterDlg;
}

BEGIN_MESSAGE_MAP(TabCtrl, CTabCtrl)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

void TabCtrl::Init()
{
	m_tabCurrent = 0;

	/*(m_tabPages[0])->Create(IDD_NOISE, this);
	(m_tabPages[1])->Create(IDD_MEDIAN_FILTER, this);

	(m_tabPages[0])->ShowWindow(SW_SHOW);
	(m_tabPages[1])->ShowWindow(SW_HIDE);*/

	noiseDlg->Create(IDD_NOISE, this);
	medianFilterDlg->Create(IDD_MEDIAN_FILTER, this);

	noiseDlg->ShowWindow(SW_SHOW);
	medianFilterDlg->ShowWindow(SW_HIDE);


	SetRectangle();
}

void TabCtrl::SetRectangle()
{
	CRect tabRect, itemRect;
	int nX, nY, nXc, nYc;

	GetClientRect(&tabRect);
	GetItemRect(0, &itemRect);

	nX = itemRect.left;
	nY = itemRect.bottom + 1;
	nXc = tabRect.right - itemRect.left - 1;
	nYc = tabRect.bottom - nY - 1;

	/*(m_tabPages[0])->SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_SHOWWINDOW);
	for (int nCount = 1; nCount < m_nNumberOfPages; nCount++)
		(m_tabPages[nCount])->SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_HIDEWINDOW);*/
	noiseDlg->SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_SHOWWINDOW);
	medianFilterDlg->SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_HIDEWINDOW);
}


void TabCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CTabCtrl::OnLButtonDown(nFlags, point);

	if (m_tabCurrent != GetCurFocus()) {
		/*(m_tabPages[m_tabCurrent])->ShowWindow(SW_HIDE);
		m_tabCurrent = GetCurFocus();
		(m_tabPages[m_tabCurrent])->ShowWindow(SW_SHOW);
		(m_tabPages[m_tabCurrent])->SetFocus();*/
		switch (m_tabCurrent)
		{
		case 0:
			noiseDlg->ShowWindow(SW_HIDE);
			break;
		case 1:
			medianFilterDlg->ShowWindow(SW_HIDE);
			break;
		default:
			break;
		}
		m_tabCurrent = GetCurFocus();
		switch (m_tabCurrent)
		{
		case 0:
			noiseDlg->ShowWindow(SW_SHOW);
			noiseDlg->SetFocus();
			break;
		case 1:
			medianFilterDlg->ShowWindow(SW_SHOW);
			medianFilterDlg->SetFocus();
			break;
		default:
			break;
		}
	}
}
