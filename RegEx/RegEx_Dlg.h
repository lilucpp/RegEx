
// RegExDlg.h : header file
//

#pragma once


// CRegExDlg dialog
class CRegExDlg : public CDialogEx
{
// Construction
public:
	CRegExDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REGEX_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
       public:
        afx_msg void OnBnClickedButtonReplacern();
        afx_msg void OnBnClickedButtonMatch();
        afx_msg void OnBnClickedButtonReplace();
};
