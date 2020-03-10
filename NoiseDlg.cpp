// NoiseDlg.cpp: 实现文件
//

#include "pch.h"
#include "MyCVExperiment.h"
#include "NoiseDlg.h"
#include "afxdialogex.h"


// NoiseDlg 对话框

IMPLEMENT_DYNAMIC(NoiseDlg, CDialogEx)

NoiseDlg::NoiseDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NOISE, pParent)
{

}

NoiseDlg::~NoiseDlg()
{
}

void NoiseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(NoiseDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_ORIGINAL, &NoiseDlg::OnBnClickedButtonOpenOriginal)
END_MESSAGE_MAP()


// NoiseDlg 消息处理程序


void NoiseDlg::OnBnClickedButtonOpenOriginal()
{
	// TODO: 在此添加控件通知处理程序代码
}
