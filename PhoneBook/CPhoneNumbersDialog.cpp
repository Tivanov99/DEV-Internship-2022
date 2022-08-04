// CPhoneNumbersDialog.cpp : implementation file
//

#include "pch.h"
#include "PhoneBook.h"
#include "afxdialogex.h"
#include "CPhoneNumbersDialog.h"


// CPhoneNumbersDialog dialog

IMPLEMENT_DYNAMIC(CPhoneNumbersDialog, CDialog)

CPhoneNumbersDialog::CPhoneNumbersDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_PHONE_NUMBERS_DIALOG, pParent)
{

}

CPhoneNumbersDialog::~CPhoneNumbersDialog()
{
}

void CPhoneNumbersDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPhoneNumbersDialog, CDialog)
END_MESSAGE_MAP()


// CPhoneNumbersDialog message handlers
