
// StartupManagerDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "StartupManager.h"
#include "StartupManagerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// CStartupManagerDlg dialog



CStartupManagerDlg::CStartupManagerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STARTUPMANAGER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStartupManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STARTUP_LIST, m_startup_list);
	DDX_Control(pDX, IDC_USER_RUN_LIST, m_user_run_list);
}

BEGIN_MESSAGE_MAP(CStartupManagerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_STARTUP_LIST, &CStartupManagerDlg::OnLvnItemchangedStartupList)
	ON_BN_CLICKED(IDC_DEL_BTN, &CStartupManagerDlg::OnBnClickedDelBtn)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_USER_RUN_LIST, &CStartupManagerDlg::OnLvnItemchangedUserRunList)
	ON_BN_CLICKED(IDC_DEL_BTN2, &CStartupManagerDlg::OnBnClickedDelBtn2)
END_MESSAGE_MAP()


// CStartupManagerDlg message handlers

BOOL CStartupManagerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	InitStartupList();
	ShowStartupList();
	InitUserRunList();
	ShowUserRunList();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// ��ʼ��startupList
void CStartupManagerDlg::InitStartupList() {

	// ������ʽ
	m_startup_list.SetExtendedStyle(
		m_startup_list.GetExtendedStyle()
		| LVS_EX_GRIDLINES					// ������
		| LVS_EX_FULLROWSELECT				// ѡ����
	);

	// ���ñ�ͷ
	m_startup_list.InsertColumn(0, "���");
	m_startup_list.InsertColumn(1, "����");
	m_startup_list.InsertColumn(2, "��ֵ");

	m_startup_list.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_startup_list.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	m_startup_list.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
}

void CStartupManagerDlg::InitUserRunList() {

	// ������ʽ
	m_user_run_list.SetExtendedStyle(
		m_user_run_list.GetExtendedStyle()
		| LVS_EX_GRIDLINES					// ������
		| LVS_EX_FULLROWSELECT				// ѡ����
	);

	// ���ñ�ͷ
	m_user_run_list.InsertColumn(0, "���");
	m_user_run_list.InsertColumn(1, "����");
	m_user_run_list.InsertColumn(2, "��ֵ");

	m_user_run_list.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_user_run_list.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	m_user_run_list.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
}

// ��ʾ�������б�
void CStartupManagerDlg::ShowStartupList() {

	// ����б�����������
	m_startup_list.DeleteAllItems();

	DWORD dwType = 0;
	DWORD dwBufferSize = MAXBYTE;
	DWORD dwKeySize = MAXBYTE;
	char szValueName[MAXBYTE] = { 0 };
	char szValueKey[MAXBYTE] = { 0 };

	// ���_ע�Ա�
	HKEY hKey = NULL;
	LONG lRet = RegOpenKey(HKEY_LOCAL_MACHINE, REG_RUN, &hKey);
	if (lRet != ERROR_SUCCESS) {
		AfxMessageBox("ע�Ա���_ʧ����");
		return;
	}

	int i = 0;
	CString strTmp;
	while (TRUE) {
		lRet = RegEnumValue(hKey, i, szValueName, &dwBufferSize, NULL, &dwType, (unsigned char*)szValueKey, &dwKeySize);
		if (ERROR_NO_MORE_ITEMS == lRet) {
			break;
		}
		strTmp.Format("%d", i);
		m_startup_list.InsertItem(i, strTmp);
		m_startup_list.SetItemText(i, 1, szValueName);
		m_startup_list.SetItemText(i, 2, szValueKey);
		i++;
		ZeroMemory(szValueName, MAXBYTE);
		ZeroMemory(szValueKey, MAXBYTE);
	}

	// �P�]ע�Ա�
	RegCloseKey(hKey);
}


void CStartupManagerDlg::ShowUserRunList() {

	// ����б�����������
	m_user_run_list.DeleteAllItems();

	DWORD dwType = 0;
	DWORD dwBufferSize = MAXBYTE;
	DWORD dwKeySize = MAXBYTE;
	char szValueName[MAXBYTE] = { 0 };
	char szValueKey[MAXBYTE] = { 0 };

	// ���_ע�Ա�
	HKEY hKey = NULL;
	LONG lRet = RegOpenKey(HKEY_CURRENT_USER, REG_USER_RUN, &hKey);
	if (lRet != ERROR_SUCCESS) {
		AfxMessageBox("ע�Ա���_ʧ����");
		return;
	}

	int i = 0;
	CString strTmp;
	while (TRUE) {
		lRet = RegEnumValue(hKey, i, szValueName, &dwBufferSize, NULL, &dwType, (unsigned char*)szValueKey, &dwKeySize);
		if (ERROR_NO_MORE_ITEMS == lRet) {
			break;
		}
		strTmp.Format("%d", i);
		m_user_run_list.InsertItem(i, strTmp);
		m_user_run_list.SetItemText(i, 1, szValueName);
		m_user_run_list.SetItemText(i, 2, szValueKey);
		i++;
		ZeroMemory(szValueName, MAXBYTE);
		ZeroMemory(szValueKey, MAXBYTE);
	}

	// �P�]ע�Ա�
	RegCloseKey(hKey);
}

void CStartupManagerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CStartupManagerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CStartupManagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CStartupManagerDlg::OnLbnSelchangeList2()
{
	// TODO: Add your control notification handler code here
}


void CStartupManagerDlg::OnLvnItemchangedList3(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}


void CStartupManagerDlg::OnLvnItemchangedListControl(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}


void CStartupManagerDlg::OnLvnItemchangedStartupList(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void CStartupManagerDlg::OnBnClickedDelBtn()
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_startup_list.GetFirstSelectedItemPosition();
	int nSel = -1;
	while (pos) {
		nSel = m_startup_list.GetNextSelectedItem(pos);
	}
	if (-1 == nSel) {
		AfxMessageBox("Ո�x��Ҫ�h���Ć����");
		return;
	}

	char szKeyName[MAXBYTE] = { 0 };
	m_startup_list.GetItemText(nSel, 1, szKeyName, MAXBYTE);
	AfxMessageBox(szKeyName);

	HKEY hKey = NULL;
	LONG lRet = RegOpenKey(HKEY_LOCAL_MACHINE, REG_RUN, &hKey);
	lRet = RegDeleteValue(hKey, szKeyName);
	if (-1 == lRet) {
		AfxMessageBox("�h�������ʧ��");
	}
	else
	{
		AfxMessageBox("�h������헳ɹ�");
	}
	RegCloseKey(hKey);
	ShowStartupList();
}


void CStartupManagerDlg::OnLvnItemchangedUserRunList(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void CStartupManagerDlg::OnBnClickedDelBtn2()
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_user_run_list.GetFirstSelectedItemPosition();
	int nSel = -1;
	while (pos) {
		nSel = m_user_run_list.GetNextSelectedItem(pos);
	}
	if (-1 == nSel) {
		AfxMessageBox("Ո�x��Ҫ�h���Ć����");
		return;
	}

	char szKeyName[MAXBYTE] = { 0 };
	m_user_run_list.GetItemText(nSel, 1, szKeyName, MAXBYTE);

	HKEY hKey = NULL;
	LONG lRet = RegOpenKey(HKEY_CURRENT_USER, REG_USER_RUN, &hKey);
	lRet = RegDeleteValue(hKey, szKeyName);
	if (-1 == lRet) {
		AfxMessageBox("�h�������ʧ��");
	}
	else
	{
		AfxMessageBox("�h������헳ɹ�");
	}
	RegCloseKey(hKey);
	ShowUserRunList();
}
