
// RegEx_CPP11Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "RegEx_CPP11.h"
#include "RegEx_CPP11Dlg.h"
#include "afxdialogex.h"
#include <regex>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRegExCPP11Dlg dialog



CRegExCPP11Dlg::CRegExCPP11Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_REGEX_CPP11_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRegExCPP11Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CRegExCPP11Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
        ON_BN_CLICKED(IDC_BUTTON_ReplaceRN,
                      &CRegExCPP11Dlg::OnBnClickedButtonReplacern)
        ON_BN_CLICKED(IDC_BUTTON_Match, &CRegExCPP11Dlg::OnBnClickedButtonMatch)
        END_MESSAGE_MAP()


// CRegExCPP11Dlg message handlers

BOOL CRegExCPP11Dlg::OnInitDialog()
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

void CRegExCPP11Dlg::OnPaint()
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
HCURSOR CRegExCPP11Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CRegExCPP11Dlg::OnBnClickedButtonReplacern() {
  CString text;
  GetDlgItemTextW(IDC_EDIT_Text, text);
  text.Replace(L"\r\n", L"\n");
  text.Replace(L"\n", L"\r\n");
  SetDlgItemTextW(IDC_EDIT_Text, text);
}

void CRegExCPP11Dlg::OnBnClickedButtonMatch() {
  CString cs_regex;
  GetDlgItemTextW(IDC_EDIT_RegEx, cs_regex);
  if (cs_regex.IsEmpty()) return;
  CString text;
  GetDlgItemTextW(IDC_EDIT_Text, text);
  if (text.IsEmpty()) return;

  bool iCase = false;
  if (((CButton*)GetDlgItem(IDC_CHECK_ICase))->GetCheck() == BST_CHECKED)
    iCase = true;

  using namespace std::regex_constants;
  syntax_option_type flag = ECMAScript;
  if (iCase) flag |= icase;

  std::wregex reg(cs_regex.GetString(), flag);

  std::wstring result;
  std::wsmatch match;
  std::wstring ws_text(text.GetString());
  size_t n = 1;
  while (std::regex_search(ws_text, match, reg)) {
    result += L"match(" + std::to_wstring(n++) + L")\r\n";
	size_t i = 0;
    for (auto sub : match) {
      result += L"sub(" + std::to_wstring(i++) + L"): " + sub.str();
      result += L"\r\n";
	}
    ws_text = match.suffix().str();

    result += L"\r\n";
  }
  result = L"total(" + std::to_wstring(--n) + L") match\r\n" + result;

  SetDlgItemTextW(IDC_EDIT_Match_Result, result.c_str());
}
