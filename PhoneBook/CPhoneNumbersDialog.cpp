// CPhoneNumbersDialog.cpp : implementation file
//

#include "pch.h"
#include "PhoneBook.h"
#include "afxdialogex.h"
#include "CPhoneNumbersDialog.h"
#include <map>
#include "CSelfClearingMap.h"


// CPhoneNumbersDialog dialog

IMPLEMENT_DYNAMIC(CPhoneNumbersDialog, CDialog)

CPhoneNumbersDialog::CPhoneNumbersDialog(PHONE_NUMBERS& recPhoneNumber, map<long, PHONE_TYPES*>& oMap,CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_PHONE_NUMBERS_DIALOG, pParent), m_recPhoneNumber(recPhoneNumber),m_oPhoneTypesMap(oMap)
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

	for (itr = m_oPhoneTypesMap.begin();itr != m_oPhoneTypesMap.end(); ++itr)
	{
		PHONE_TYPES* pPhoneType = itr->second;

		int nResult = m_cmbPhoneTypes.AddString(pPhoneType->szPHONE_TYPE);
		m_cmbPhoneTypes.SetItemData(nResult, pPhoneType->lID);

		if (pPhoneType->lID == m_recPhoneNumber.lPHONE_TYPE_ID)
			m_cmbPhoneTypes.SetCurSel(nResult);
	}
}

void CPhoneNumbersDialog::OnBnClickedOk()
{
	CString strPhoneNumber;
	m_edbPhoneNumber.GetWindowText(strPhoneNumber);

	if (strPhoneNumber.GetLength() < GlobalConstants::_nPhoneNumberMinSize || strPhoneNumber.GetLength() > GlobalConstants::_nPhoneNumberSize)
	{
		AfxMessageBox(_T("Phone number must me between $d and $d numbers."), GlobalConstants::_nPhoneNumberMinSize, GlobalConstants::_nPhoneNumberSize);
		return;
	}

	_tcscpy_s(m_recPhoneNumber.szPHONE_NUMBER, strPhoneNumber);

	m_recPhoneNumber.lPHONE_TYPE_ID = m_cmbPhoneTypes.GetItemData(m_cmbPhoneTypes.GetCurSel());

	CDialog::OnOK();
}


void CPhoneNumbersDialog::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

