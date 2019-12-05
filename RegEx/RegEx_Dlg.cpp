
// RegEx_CPP11Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "RegEx.h"
#include "RegEx_Dlg.h"
#include "afxdialogex.h"
#include <regex>
#include <boost/regex.hpp>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRegExDlg dialog



CRegExDlg::CRegExDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_REGEX_CPP11_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRegExDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CRegExDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
        ON_BN_CLICKED(IDC_BUTTON_ReplaceRN,
                      &CRegExDlg::OnBnClickedButtonReplacern)
        ON_BN_CLICKED(IDC_BUTTON_Match, &CRegExDlg::OnBnClickedButtonMatch)
        ON_BN_CLICKED(IDC_BUTTON_Replace,
                      &CRegExDlg::OnBnClickedButtonReplace)
        END_MESSAGE_MAP()


// CRegExDlg message handlers

BOOL CRegExDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRegExDlg::OnPaint()
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
HCURSOR CRegExDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CRegExDlg::OnBnClickedButtonReplacern() {
  CString text;
  GetDlgItemTextW(IDC_EDIT_Text, text);
  text.Replace(L"\r\n", L"\n");
  text.Replace(L"\n", L"\r\n");
  SetDlgItemTextW(IDC_EDIT_Text, text);
}

void CRegExDlg::OnBnClickedButtonMatch() {
  CString cs_regex, text;
  GetDlgItemTextW(IDC_EDIT_RegEx, cs_regex);
  GetDlgItemTextW(IDC_EDIT_Text, text);
  if (cs_regex.IsEmpty() || text.IsEmpty()) return;

  bool iCase = false;
  if (((CButton*)GetDlgItem(IDC_CHECK_ICase))->GetCheck() == BST_CHECKED)
    iCase = true;

  boost::regex::flag_type flag = boost::regex_constants::normal;
  if (iCase) flag |= boost::regex::icase;

  try {
    boost::wregex reg(cs_regex.GetString(), flag);

    std::wstring result;
    std::wstring ws_text(text.GetString());
    boost::wsmatch match;

    size_t n = 1;
    while (boost::regex_search(ws_text, match, reg)) {
      result += L"match(" + std::to_wstring(n++) + L"): \r\n";
      size_t i = 0;
      for (auto sub : match) {
        result += L"    sub(" + std::to_wstring(i++) + L"): " + sub.str();
        result += L"\r\n";
      }
      ws_text = match.suffix().str();

      result += L"\r\n";
    }
    result = L"total(" + std::to_wstring(--n) + L") match:\r\n" + result;
    SetDlgItemTextW(IDC_EDIT_Match_Result, result.c_str());
  } catch (boost::regex_error& e) {
    MessageBoxA(NULL, e.what(), "error", MB_OK);
  }
}

void CRegExDlg::OnBnClickedButtonReplace() {
  CString cs_regex, text, replace;
  GetDlgItemTextW(IDC_EDIT_RegEx, cs_regex);
  GetDlgItemTextW(IDC_EDIT_Text, text);
  GetDlgItemTextW(IDC_EDIT_Replace, replace);
  if (cs_regex.IsEmpty() || text.IsEmpty() || replace.IsEmpty()) return;

  bool iCase = false;
  if (((CButton*)GetDlgItem(IDC_CHECK_ICase))->GetCheck() == BST_CHECKED)
    iCase = true;
  boost::regex::flag_type flag = boost::regex_constants::normal;
  if (iCase) flag |= boost::regex::icase;

  try {
    boost::wregex reg(cs_regex.GetString(), flag);

    std::wstring ws_text(text.GetString());
    std::wstring replace_result =
        boost::regex_replace(ws_text, reg, replace.GetString());

    SetDlgItemTextW(IDC_EDIT_Replace_Result, replace_result.c_str());
  } catch (boost::regex_error& e) {
    MessageBoxA(NULL, e.what(), "error", MB_OK);
  }
}
