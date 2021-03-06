﻿
// MyCVExperimentDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MyCVExperiment.h"
#include "MyCVExperimentDlg.h"
#include "afxdialogex.h"
#include "ImageProcess.h"
#include "stdafx.h"
#include "NoiseDlg.h"
#include "MedianFilterDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框


class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMyCVExperimentDlg 对话框



CMyCVExperimentDlg::CMyCVExperimentDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MYCVEXPERIMENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyCVExperimentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_TAB, m_tabCtrl);
}

LRESULT CMyCVExperimentDlg::OnNoiseThreadMsgReceived(WPARAM wParam, LPARAM lParam)
{
	m_tabCtrl.noiseDlg->OnNoiseThreadMsgReceived(wParam, lParam);
	return 0;
}

LRESULT CMyCVExperimentDlg::OnMedianThreadMsgReceived(WPARAM wParam, LPARAM lParam)
{
	m_tabCtrl.medianFilterDlg->OnMedianThreadMsgReceived(wParam, lParam);
	return 0;
}

LRESULT CMyCVExperimentDlg::OnTranslationThreadScaleMsgReceived(WPARAM wParam, LPARAM lParam)
{
	m_tabCtrl.translationDlg->OnTranslationScaleThreadMsgReceived(wParam, lParam);
	return 0;
}

LRESULT CMyCVExperimentDlg::OnTranslationThreadRotateMsgReceived(WPARAM wParam, LPARAM lParam)
{
	m_tabCtrl.translationDlg->OnTranslationRotateThreadMsgReceived(wParam, lParam);
	return 0;
}



BEGIN_MESSAGE_MAP(CMyCVExperimentDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_NOISE, &CMyCVExperimentDlg::OnNoiseThreadMsgReceived)
	ON_MESSAGE(WM_MEDIAN_FILTER, &CMyCVExperimentDlg::OnMedianThreadMsgReceived)
	ON_MESSAGE(WM_TRANSFORM_SCALE, &CMyCVExperimentDlg::OnTranslationThreadScaleMsgReceived)
	ON_MESSAGE(WM_TRANSFORM_ROTATE, &CMyCVExperimentDlg::OnTranslationThreadRotateMsgReceived)
//	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, &CMyCVExperimentDlg::OnTcnSelchangeTab)
//ON_WM_LBUTTONDOWN()
//ON_WM_LBUTTONDOWN()
ON_WM_SIZE()
END_MESSAGE_MAP()


// CMyCVExperimentDlg 消息处理程序

BOOL CMyCVExperimentDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_tabCtrl.InsertItem(0, _T("椒盐噪声"));
	m_tabCtrl.InsertItem(1, _T("中值滤波"));
	m_tabCtrl.InsertItem(2, _T("图像变换"));

	m_tabCtrl.Init();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMyCVExperimentDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMyCVExperimentDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMyCVExperimentDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}







//void CMyCVExperimentDlg::OnSize(UINT nType, int cx, int cy)
//{
//	CDialogEx::OnSize(nType, cx, cy);
//
//	// TODO: 在此处添加消息处理程序代码
//	if (SIZE_MINIMIZED == nType)    //防止最小化时程序崩溃
//		return;
//
//	CRect rectDlg;
//	GetWindowRect(&rectDlg);
//	int height = rectDlg.Height();
//	int width = rectDlg.Width();
//	CRect rect = CRect(rectDlg.TopLeft(), CSize(width, height));
//	CWnd* tabWnd = GetDlgItem(IDC_TAB);
//	if (tabWnd != NULL)
//		tabWnd->SetWindowPos()
//}
