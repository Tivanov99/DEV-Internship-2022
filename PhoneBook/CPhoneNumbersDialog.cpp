// CPhoneNumbersDialog.cpp : implementation file
//

#include "pch.h"
#include "PhoneBook.h"
#include "afxdialogex.h"
#include "CPhoneNumbersDialog.h"
#include <map>


// CPhoneNumbersDialog dialog

IMPLEMENT_DYNAMIC(CPhoneNumbersDialog, CDialog)

CPhoneNumbersDialog::CPhoneNumbersDialog(PHONE_NUMBERS& recPhoneNumber, map<long, PHONE_TYPES*>& oMap,CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_PHONE_NUMBERS_DIALOG, pParent), m_recPhoneNumber(recPhoneNumber),m_oMap(oMap)
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
	
	map<long, PHONE_TYPES*>::iterator itr;

	/*for (size_t i = 0; i < m_oMap.size(); i++)
	{

	}*/

	for (itr = m_oMap.begin();itr != m_oMap.end(); ++itr)
	{
		PHONE_TYPES* pPhoneType = itr->second;

		int nResult = m_cmbPhoneTypes.AddString(pPhoneType->szPHONE_TYPE);
		m_cmbPhoneTypes.SetItemData(nResult, reinterpret_cast<DWORD_PTR>(pPhoneType));

		if (pPhoneType->lID == m_recPhoneNumber.lPHONE_TYPE_ID)
			m_cmbPhoneTypes.SetCurSel(nResult);
	}
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
