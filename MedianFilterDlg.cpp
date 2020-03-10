// MedianFilterDlg.cpp: 实现文件
//

#include "pch.h"
#include "MyCVExperiment.h"
#include "MedianFilterDlg.h"
#include "afxdialogex.h"


// MedianFilterDlg 对话框

IMPLEMENT_DYNAMIC(MedianFilterDlg, CDialogEx)

MedianFilterDlg::MedianFilterDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MEDIAN_FILTER, pParent)
{

}

MedianFilterDlg::~MedianFilterDlg()
{
}

void MedianFilterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MedianFilterDlg, CDialogEx)
END_MESSAGE_MAP()


// MedianFilterDlg 消息处理程序
