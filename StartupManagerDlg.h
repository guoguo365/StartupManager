
// StartupManagerDlg.h : header file
//

#pragma once

#define REG_RUN "Software\\Microsoft\\Windows\\CurrentVersion\\Run"
#define REG_USER_RUN "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"

// CStartupManagerDlg dialog
class CStartupManagerDlg : public CDialogEx
{
// Construction
public:
	CStartupManagerDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STARTUPMANAGER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg
	void InitStartupList();
	void InitUserRunList();
	void ShowStartupList();
	void ShowUserRunList();
	void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLbnSelchangeList2();
	afx_msg void OnLvnItemchangedList3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLvnItemchangedListControl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLvnItemchangedStartupList(NMHDR* pNMHDR, LRESULT* pResult);
	CListCtrl m_startup_list;
	afx_msg void OnBnClickedDelBtn();
	CListCtrl m_user_run_list;
	afx_msg void OnLvnItemchangedUserRunList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLvnItemchangedStartupList2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedDelBtn2();
};
