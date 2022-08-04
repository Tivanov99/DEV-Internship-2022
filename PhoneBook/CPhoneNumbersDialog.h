#pragma once
#include "afxdialogex.h"


// CPhoneNumbersDialog dialog

class CPhoneNumbersDialog : public CDialog
{
	DECLARE_DYNAMIC(CPhoneNumbersDialog)

public:
	CPhoneNumbersDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CPhoneNumbersDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PHONE_NUMBERS_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
