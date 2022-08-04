// CPhoneNumbersDialog.cpp : implementation file
//

#include "pch.h"
#include "PhoneBook.h"
#include "afxdialogex.h"
#include "CPhoneNumbersDialog.h"


// CPhoneNumbersDialog dialog

IMPLEMENT_DYNAMIC(CPhoneNumbersDialog, CDialog)

CPhoneNumbersDialog::CPhoneNumbersDialog(PHONE_NUMBERS& recPhoneNumber, CPhoneTypesArray& oPhonetypesArray,CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_PHONE_NUMBERS_DIALOG, pParent), m_recPhoneNumber(recPhoneNumber),m_oPhonetypesArray(oPhonetypesArray)
{

}

CPhoneNumbersDialog::~CPhoneNumbersDialog()
{
}
BOOL CPhoneNumbersDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	FillInputFileds();

	return TRUE;
}

void CPhoneNumbersDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMB_PHONE_TYPE, m_cmbPhoneTypes);
	DDX_Control(pDX, IDC_EDB_PHONE_NUMBER, m_edbPhoneNumber);
}


BEGIN_MESSAGE_MAP(CPhoneNumbersDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CPhoneNumbersDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CPhoneNumbersDialog::OnBnClickedCancel)
END_MESSAGE_MAP()


// CPhoneNumbersDialog message handlers

void CPhoneNumbersDialog::FillInputFileds()
{
	m_edbPhoneNumber.SetWindowText(m_recPhoneNumber.szPHONE_NUMBER);
	
	int nDa = 0;
	/*for (INT_PTR i = 0; i < m_oPhonetypesArray.GetCount(); i++)
	{

	}*/
}

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
