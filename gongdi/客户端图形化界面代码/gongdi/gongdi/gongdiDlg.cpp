
// gongdiDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "gongdi.h"
#include "gongdiDlg.h"
#include "afxdialogex.h"
#include "head.h"
#include<map>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern Gongdi *gonghead;
extern map<CString, CString>nameid;

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


// CgongdiDlg 对话框



CgongdiDlg::CgongdiDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GONGDI_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CgongdiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CgongdiDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, &CgongdiDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CgongdiDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CgongdiDlg 消息处理程序

BOOL CgongdiDlg::OnInitDialog()
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
	readname();
	CEdit *editCtime = (CEdit *)GetDlgItem(IDC_EDIT_Ctime);
	editCtime->SetWindowTextW(_T("工时计算：输入工号"));
	CEdit *editCfind = (CEdit *)GetDlgItem(IDC_EDIT_4);
	editCfind->SetWindowTextW(_T("请输入要查询工号"));

	//定时器
	SetTimer(20173015, 2000, NULL);
	SetTimer(20173016, 10000, NULL);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CgongdiDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CgongdiDlg::OnPaint()
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
HCURSOR CgongdiDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CgongdiDlg::OnTimer(UINT_PTR nIDEvent)	//定时显示与报警
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == 20173015)
	{
		readfile();
		Gongdi *nownode = gonghead;

		//显示功能
		map<CString, bool>mp;
		CListBox *plist1 = (CListBox *)GetDlgItem(IDC_LIST1);
		plist1->ResetContent();
		int index = 0,num=0;
		while (nownode != NULL)
		{
			if (mp[nownode->number] == true)
			{
				nownode = nownode->next;
				continue;
			}

			mp[nownode->number] = true;
			num++;
			CString s = _T("姓名：");
			s += nameid[nownode->number];
			plist1->InsertString(index++, s);
			s = _T("工号：");
			s += nownode->number;
			plist1->InsertString(index++, s);
			s.Format(_T("所在区域：%d号"), nownode->setnum);
			plist1->InsertString(index++, s);
			plist1->InsertString(index++, _T("----------"));
			nownode = nownode->next;
			if (num >= 10)
				break;
		}
	}

	if (nIDEvent == 20173016)	//报警功能
	{
		map<CString, bool>mp2;
		Gongdi *nownode = gonghead;
		while (nownode != NULL)
		{
			if (nownode->setnum == 2 && mp2[nownode->number] != true )
			{
				CString s;
				s.Format(_T("姓名：%s\n工号：%s\n已经进入2号危险区域"), nameid[nownode->number], nownode->number);
				AfxMessageBox(s);
			}
			mp2[nownode->number] = true;
			nownode = nownode->next;
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CgongdiDlg::OnBnClickedButton1()	//工时计算
{
	// TODO: 在此添加控件通知处理程序代码
	CEdit *ptime = (CEdit *)GetDlgItem(IDC_EDIT_Ctime);
	CEdit *phour = (CEdit *)GetDlgItem(IDC_EDIT_hour);
	CEdit *pmin = (CEdit *)GetDlgItem(IDC_EDIT_min);

	TCHAR sc[30];
	ptime->GetWindowTextW(sc, 30);
	if (wcscmp(sc, _T("工时计算：输入工号")) == 0)
	{
		MessageBox(_T("请输入正确的工号"));
		return;
	}

	//将所有相同工号全部找出来
	Gongdi *pnode = gonghead;
	Gongdi *same[100];
	int sum = 0;
	while (pnode != NULL)
	{
		if (wcscmp(sc, pnode->number) == 0)
		{
			same[sum++] = pnode;
		}
		pnode = pnode->next;
	}

	if (sum == 0)
	{
		MessageBox(_T("工号不存在(错误）或\n未进入工地"));
		return;
	}

	//计算工时
	int sumtime = 0;
	for (int i = sum-1; i >= 0 && i - 1 >= 0; i = i - 2)
	{
		sumtime += minus1(same[i], same[i - 1]);
	}

	int hour = sumtime / 60;
	int min = sumtime % 60;
	
	TCHAR st[10],sp[3];
	_itow(min, sp, 10);
	pmin->SetWindowTextW(sp);

	_itow(hour, st, 10);
	phour->SetWindowTextW(st);
}


void CgongdiDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CEdit *pedit_find = (CEdit *)GetDlgItem(IDC_EDIT_4);
	TCHAR sc[30];
	pedit_find->GetWindowTextW(sc, 30);
	
	Gongdi *ptem = gonghead;
	while (ptem != NULL)
	{
		if (wcscmp(sc, ptem->number) == 0)	//存在
		{
			CListBox *plist2 = (CListBox *)GetDlgItem(IDC_LIST2);
			plist2->ResetContent();
			CString s = _T("姓名：");
			s += nameid[ptem->number];
			plist2->InsertString(0, s);
			s = _T("工号：");
			s += ptem->number;
			plist2->InsertString(1, s);
			s.Format(_T("所在区域：%d号"), ptem->setnum);
			plist2->InsertString(2, s);
			return;
		}
		ptem = ptem->next;
	}

	MessageBox(_T("工号不存在(错误）或\n未进入工地"));
}
