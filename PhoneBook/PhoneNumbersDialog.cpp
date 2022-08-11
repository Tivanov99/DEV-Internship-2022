// CPhoneNumbersDialog.cpp : implementation file
//

#include "pch.h"
#include "PhoneBook.h"
#include "afxdialogex.h"
#include "PhoneNumbersDialog.h"
#include <map>


// CPhoneNumbersDialog dialog

IMPLEMENT_DYNAMIC(CPhoneNumbersDialog, CDialog)

CPhoneNumbersDialog::CPhoneNumbersDialog(DialogWindowActions eOperation, PHONE_NUMBERS& recPhoneNumber, CSelfClearingMap<long, PHONE_TYPES*>& oPhoneTypesMap, CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_PHONE_NUMBERS_DIALOG, pParent), m_recPhoneNumber(recPhoneNumber), m_oPhoneTypesMap(oPhoneTypesMap), m_eOperation(eOperation)
{

}

CPhoneNumbersDialog::~CPhoneNumbersDialog()
{
}
BOOL CPhoneNumbersDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	FillInputFileds();

	if (m_eOperation == DialogWindowActions::InsertData)
	{
		int nFirstPhoneType = 0;
		m_cmbPhoneTypes.SetCurSel(nFirstPhoneType);
	}

	if (m_eOperation == DialogWindowActions::ReadData)
		LockInputFields();


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
	m_edbPhoneNumber.SetWindowText(m_recPhoneNumber.szPhoneNumber);

	map<long, PHONE_TYPES*>::iterator itr;

	PHONE_TYPES* pPhoneType;
	long lId;

	POSITION posPhoneTypes = m_oPhoneTypesMap.GetStartPosition();

	while (posPhoneTypes)
	{
		if (posPhoneTypes == NULL)
			break;

		m_oPhoneTypesMap.GetNextAssoc(posPhoneTypes, lId, pPhoneType);
		if (pPhoneType == NULL)
			continue;

		int nResult = m_cmbPhoneTypes.AddString(pPhoneType->szPhoneType);
		m_cmbPhoneTypes.SetItemData(nResult, pPhoneType->lID);

		if (pPhoneType->lID == m_recPhoneNumber.lPhoneTypeId)
			m_cmbPhoneTypes.SetCurSel(nResult);
	}
}

void CPhoneNumbersDialog::OnBnClickedOk()
{
	CString strPhoneNumber;
	m_edbPhoneNumber.GetWindowText(strPhoneNumber);

	if (strPhoneNumber.GetLength() < GlobalConstants::_nPhoneNumberMinSize || strPhoneNumber.GetLength() > GlobalConstants::_nPhoneNumberSize)
	{
		CString strErrorMessage;
		strErrorMessage.Format(_T("Phone number must me between %d and %d numbers."), GlobalConstants::_nPhoneNumberMinSize, GlobalConstants::_nPhoneNumberSize);

		AfxMessageBox(strErrorMessage);
		return;
	}

	_tcscpy_s(m_recPhoneNumber.szPhoneNumber, strPhoneNumber);

	m_recPhoneNumber.lPhoneTypeId = m_cmbPhoneTypes.GetItemData(m_cmbPhoneTypes.GetCurSel());

	CDialog::OnOK();
}


void CPhoneNumbersDialog::OnBnClickedCancel()
{
	CString strMessage;
	strMessage.Format(_T("If there are any changes made, they will not be saved!"));

	const int msgboxID = MessageBox(
		(LPCWSTR)strMessage,
		(LPCWSTR)L"Message",
		MB_ICONINFORMATION | IDOK
	);

	if (msgboxID == IDOK)
	{
		CDialog::OnCancel();
	}
}

void CPhoneNumbersDialog::LockInputFields()
{
	m_cmbPhoneTypes.EnableWindow(false);
	m_edbPhoneNumber.EnableWindow(false);
}
