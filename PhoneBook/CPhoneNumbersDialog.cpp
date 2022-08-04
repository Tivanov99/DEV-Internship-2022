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
	DDX_Control(pDX, IDC_EDB_PHONE_NUMBER, m_edbPhoneNumber);
	DDX_Control(pDX, IDC_EDB_PHONE_TYPE, m_edbPhoneType);
}


BEGIN_MESSAGE_MAP(CPhoneNumbersDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CPhoneNumbersDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CPhoneNumbersDialog::OnBnClickedCancel)
END_MESSAGE_MAP()


// CPhoneNumbersDialog message handlers


void CPhoneNumbersDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}


void CPhoneNumbersDialog::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}
