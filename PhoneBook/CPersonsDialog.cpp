#include "pch.h"
#include "PhoneBook.h"
#include "afxdialogex.h"
#include "CPersonsDialog.h"
#include "resource.h"
#include "CPhoneNumbersDialog.h"


IMPLEMENT_DYNAMIC(CPersonsDialog, CDialog)

BEGIN_MESSAGE_MAP(CPersonsDialog, CDialog)
	ON_WM_CONTEXTMENU()
	ON_WM_LBUTTONDBLCLK()
	//ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDCANCEL, &CPersonsDialog::OnBnClickedCancel)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CONTEXT_EDIT, &CPersonsDialog::ManageContextMenuItems)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CONTEXT_READ_DATA, &CPersonsDialog::ManageContextMenuItems)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CONTEXT_DELETE, &CPersonsDialog::ManageContextMenuItems)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CONTEXT_INSERT, &CPersonsDialog::ManageContextMenuItems)
	ON_COMMAND(ID_EDIT_CONTEXT_EDIT, &CPersonsDialog::OnContextMenuEdit)
	ON_COMMAND(ID_EDIT_CONTEXT_DELETE, &CPersonsDialog::OnContextMenuDelete)
	ON_COMMAND(ID_EDIT_CONTEXT_READ_DATA, &CPersonsDialog::OnContextMenuReadData)
	ON_COMMAND(ID_EDIT_CONTEXT_INSERT, &CPersonsDialog::OnContextMenuInsert)
END_MESSAGE_MAP()


CPersonsDialog::CPersonsDialog(DialogWindowActions eOperation, PERSONS& recPerson, CCitiesArray& oCitiesArray,
	CSelfClearingMap<long, PHONE_NUMBERS*>& oPhoneNumbersMap, CSelfClearingMap<long, PHONE_TYPES*>& oPhoneTypesMap, CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_PERSONS_DIALOG, pParent), m_recPerson(recPerson), m_eOperation(eOperation), m_oCitiesArray(oCitiesArray),
	m_oPhoneNumbersMap(oPhoneNumbersMap), m_oPhoneTypesMap(oPhoneTypesMap)
{
}
CPersonsDialog :: ~CPersonsDialog() {};

BOOL CPersonsDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	ConfiguratePhoneNumbersLsc();

	if (m_eOperation != DialogWindowActions::InsertData)
	{
		FillPersonDataFields();
		FillPhoneNumbers();
	}

	FillCitiesComboBox();
	SetDialogTitle();

	if (m_eOperation == DialogWindowActions::ReadData)
	{
		m_edbPersonFirstName.EnableWindow(false);
		m_edbPersonSecondName.EnableWindow(false);
		m_edbPersonLastName.EnableWindow(false);
		m_edbPersonUcn.EnableWindow(false);
		m_cmbCitiesNames.EnableWindow(false);
		m_lscPersonPhoneNumbers.EnableWindow(false);
	}

	return TRUE;
}

void CPersonsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDB_FIRST_NAME, m_edbPersonFirstName);
	DDX_Control(pDX, IDC_EDB_SECOND_NAME, m_edbPersonSecondName);
	DDX_Control(pDX, IDC_EDB_LAST_NAME, m_edbPersonLastName);
	DDX_Control(pDX, IDC_EDB_PERSON_UCN, m_edbPersonUcn);
	DDX_Control(pDX, IDC_CMB_CITIES_NAMES, m_cmbCitiesNames);
	DDX_Control(pDX, IDC_LSC_PERSON_PHONE_NUMBERS, m_lscPersonPhoneNumbers);
}

void CPersonsDialog::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	if (m_eOperation != DialogWindowActions::ReadData)
	{
#ifndef SHARED_HANDLERS
		theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
	}
}

void CPersonsDialog::ManageContextMenuItems(CCmdUI* pCmdUI)
{
	UINT uSelectedCount = m_lscPersonPhoneNumbers.GetSelectedCount();

	if (pCmdUI->m_nID == ID_EDIT_CONTEXT_INSERT && uSelectedCount == 0)
	{
		pCmdUI->Enable(true);
		return;
	}

	if (pCmdUI->m_nID == ID_EDIT_CONTEXT_INSERT && uSelectedCount > 0)
	{
		pCmdUI->Enable(false);
		return;
	}

	if (m_lscPersonPhoneNumbers.GetSelectedCount() == 0)
	{
		pCmdUI->Enable(false);
	}
	else
	{
		pCmdUI->Enable(true);
	}
}


void CPersonsDialog::ConfiguratePhoneNumbersLsc()
{
	m_lscPersonPhoneNumbers.SetExtendedStyle(m_lscPersonPhoneNumbers.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	m_lscPersonPhoneNumbers.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);

	int nColumnNumber = 0;
	m_lscPersonPhoneNumbers.InsertColumn(nColumnNumber++, _T("Номер"), LVCFMT_LEFT, GlobalConstants::_nColumnWidth, 1);
	m_lscPersonPhoneNumbers.InsertColumn(nColumnNumber++, _T("Тип"), LVCFMT_CENTER, GlobalConstants::_nColumnWidth, 1);
}

void CPersonsDialog::SetDialogTitle()
{
	switch (m_eOperation)
	{
	case  DialogWindowActions::InsertData:
		this->SetWindowText(_T("Add person"));
		break;
	case  DialogWindowActions::ReadData:
		this->SetWindowText(_T("Read person data"));
		break;
	case  DialogWindowActions::EditData:
		this->SetWindowText(_T("Edit person"));
		break;
	default:
		break;
	}
}

void CPersonsDialog::FillPersonDataFields()
{
	m_edbPersonFirstName.SetWindowText(m_recPerson.szFirstName);
	m_edbPersonFirstName.SetLimitText(GlobalConstants::_nPersonFirstNameSize);

	m_edbPersonSecondName.SetWindowText(m_recPerson.szSecondName);
	m_edbPersonSecondName.SetLimitText(GlobalConstants::_nPersonSecondNameSize);

	m_edbPersonLastName.SetWindowText(m_recPerson.szLastName);
	m_edbPersonLastName.SetLimitText(GlobalConstants::_nPersonLastNameSize);

	m_edbPersonUcn.SetWindowText(m_recPerson.szUcn);
	m_edbPersonUcn.SetLimitText(GlobalConstants::_nPersonUcnSize);
}

void CPersonsDialog::FillCitiesComboBox()
{
	for (INT_PTR i = 0; i < m_oCitiesArray.GetCount(); i++)
	{
		CITIES* pCity = m_oCitiesArray.GetAt(i);
		if (pCity == NULL)
			continue;

		int nResult = m_cmbCitiesNames.AddString(pCity->szCityName);
		m_cmbCitiesNames.SetItemData(nResult, reinterpret_cast<DWORD_PTR>(pCity));

		if (pCity->lID == m_recPerson.lCityId)
			m_cmbCitiesNames.SetCurSel(nResult);
	}
}

void CPersonsDialog::FillPhoneNumbers()
{
	CSelfClearingMap<long, PHONE_NUMBERS*> map;

	POSITION posPhoneNumbers = m_oPhoneNumbersMap.GetStartPosition();

	long lId;
	PHONE_NUMBERS* pPhoneNumber;

	while (posPhoneNumbers)
	{
		m_oPhoneNumbersMap.GetNextAssoc(posPhoneNumbers, lId, pPhoneNumber);
		if (pPhoneNumber == NULL)
			return;
		InsertRecordToListCtrl(pPhoneNumber);
	}

	//for (itrPhoneNumbers = m_oPhoneNumbersMap.begin(); itrPhoneNumbers != m_oPhoneNumbersMap.end(); ++itrPhoneNumbers)
	//{
	//	PHONE_NUMBERS* pCurrentPhoneNumber = itrPhoneNumbers->second;

	//	if (pCurrentPhoneNumber == NULL)
	//		continue;
	//	InsertRecordToListCtrl(pCurrentPhoneNumber);
	//}
}

void CPersonsDialog::InsertRecordToListCtrl(PHONE_NUMBERS* pPhoneNumber)
{
	PHONE_TYPES* pPhoneType;


	if (!m_oPhoneTypesMap.Lookup(pPhoneNumber->lPhoneTypeId, pPhoneType))
		return;

	if (pPhoneType == NULL)
		return;


	/*CSelfClearingMap<long, PHONE_TYPES*>::iterator intrPhoneTypes = m_oPhoneTypesMap.find(pPhoneNumber->lPhoneTypeId);

	if (intrPhoneTypes == m_oPhoneTypesMap.end())
		return;

	PHONE_TYPES* pPhoneType = intrPhoneTypes->second;

	if (pPhoneType == NULL)
		return;*/

	const int nRow = m_lscPersonPhoneNumbers.GetItemCount();

	m_lscPersonPhoneNumbers.InsertItem(nRow, pPhoneNumber->szPhoneNumber);

	m_lscPersonPhoneNumbers.SetItemText(nRow, 1, pPhoneType->szPhoneType);

	m_lscPersonPhoneNumbers.SetItemData(nRow, reinterpret_cast<DWORD_PTR>(pPhoneNumber));
}

void CPersonsDialog::UpdateListCtrlRecord()
{
	PHONE_NUMBERS* pPhoneNumber = GetSelectedRecordItemData();

	const int nSelectedRow = m_lscPersonPhoneNumbers.GetSelectionMark();

	int nColumn = 0;

	m_lscPersonPhoneNumbers.SetItemText(nSelectedRow, nColumn++, pPhoneNumber->szPhoneNumber);

	PHONE_TYPES* pPhoneType;

	if (!m_oPhoneTypesMap.Lookup(pPhoneNumber->lID, pPhoneType))
		return;

	if (pPhoneType == NULL)
		return;

	m_lscPersonPhoneNumbers.SetItemText(nSelectedRow, nColumn, pPhoneType->szPhoneType);
}



void CPersonsDialog::OnOK()
{
	CString strPersonFirstName;
	m_edbPersonFirstName.GetWindowText(strPersonFirstName);

	CString strPersonFirstNameErrorMessage = m_oTextValidator.ValidateTextData(strPersonFirstName, GlobalConstants::_nPersonFirstNameMinSize);
	if (strPersonFirstNameErrorMessage.GetLength() > 0)
	{
		AfxMessageBox(_T("The 'First name' field: ") + strPersonFirstNameErrorMessage);
		return;
	}

	CString strPersonSecondName;
	m_edbPersonSecondName.GetWindowText(strPersonSecondName);

	CString strPersonSecondNameErrorMessage = m_oTextValidator.ValidateTextData(strPersonSecondName, GlobalConstants::_nPersonSecondNameMinSize);
	if (strPersonSecondNameErrorMessage.GetLength() > 0)
	{
		AfxMessageBox(_T("The 'Second name' field: ") + strPersonSecondNameErrorMessage);
		return;
	}

	CString strPersonLastName;
	m_edbPersonLastName.GetWindowText(strPersonLastName);

	CString strPersonLastNameErrorMessage = m_oTextValidator.ValidateTextData(strPersonLastName,
		GlobalConstants::_nPersonLastNameMinSize);
	if (strPersonLastNameErrorMessage.GetLength() > 0)
	{
		AfxMessageBox(_T("The 'Last name' field: ") + strPersonLastNameErrorMessage);
		return;
	}

	CITIES* pCity = (CITIES*)m_cmbCitiesNames.GetItemData(m_cmbCitiesNames.GetCurSel());

	//m_recPerson.szAddress
	m_edbPersonFirstName.GetWindowText(strPersonFirstName);
	_tcscpy_s(m_recPerson.szFirstName, strPersonFirstName);

	m_edbPersonSecondName.GetWindowText(strPersonSecondName);
	_tcscpy_s(m_recPerson.szSecondName, strPersonSecondName);

	m_edbPersonLastName.GetWindowText(strPersonLastName);
	_tcscpy_s(m_recPerson.szLastName, strPersonLastName);

	CString strPersonUcn;
	m_edbPersonLastName.GetWindowText(strPersonUcn);
	_tcscpy_s(m_recPerson.szUcn, strPersonUcn);

	m_recPerson.lCityId = pCity->lID;

	CDialog::OnOK();
}

void CPersonsDialog::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

PHONE_NUMBERS* CPersonsDialog::GetSelectedRecordItemData()
{
	const int nSelectedRow = m_lscPersonPhoneNumbers.GetSelectionMark();
	if (nSelectedRow == -1)
	{
		AfxMessageBox(_T("This function is only called on record!"));
		return NULL;
	}
	PHONE_NUMBERS* pPhoneNumber = reinterpret_cast<PHONE_NUMBERS*>(m_lscPersonPhoneNumbers.GetItemData(nSelectedRow));
	return pPhoneNumber;
}

void CPersonsDialog::OnContextMenuEdit()
{
	PHONE_NUMBERS* pPhoneNumber = GetSelectedRecordItemData();

	CPhoneNumbersDialog oPhoneNumbersDialog(DialogWindowActions::EditData,*pPhoneNumber, m_oPhoneTypesMap);

	if (oPhoneNumbersDialog.DoModal() != IDOK)
		return;

	UpdateListCtrlRecord();
}

void CPersonsDialog::OnContextMenuDelete()
{
	PHONE_NUMBERS* pPhoneNumber = GetSelectedRecordItemData();

	if (pPhoneNumber == NULL)
		return;

	CString strMessage;
	strMessage.Format(_T("Do you want the record to be deleted? Phone number : %s "), pPhoneNumber->szPhoneNumber);

	const int msgboxID = MessageBox(
		(LPCWSTR)strMessage,
		(LPCWSTR)L"Delete record.",
		MB_ICONINFORMATION | IDOK
	);

	if (msgboxID == IDOK)
	{
		const int nSelectedRow = m_lscPersonPhoneNumbers.GetSelectionMark();
		m_lscPersonPhoneNumbers.DeleteItem(nSelectedRow);

		m_oPhoneNumbersMap.RemoveKey(pPhoneNumber->lID);

		delete pPhoneNumber;
		pPhoneNumber = NULL;
	}
}

void CPersonsDialog::OnContextMenuReadData()
{
	PHONE_NUMBERS* pPhoneNumber = GetSelectedRecordItemData();

	CPhoneNumbersDialog oPhoneNumbersDialog(DialogWindowActions::ReadData, *pPhoneNumber, m_oPhoneTypesMap);

	oPhoneNumbersDialog.DoModal();
}


void CPersonsDialog::OnContextMenuInsert()
{
	PHONE_NUMBERS* pPhoneNumber = new PHONE_NUMBERS;
	_tcscpy_s(pPhoneNumber->szPhoneNumber, _T(""));

	CPhoneNumbersDialog oPhoneNumbersDialog(DialogWindowActions::InsertData,*pPhoneNumber, m_oPhoneTypesMap);

	if (oPhoneNumbersDialog.DoModal() != IDOK)
	{
		pPhoneNumber = NULL;
		delete pPhoneNumber;
		return;
	}

	pPhoneNumber->lID = 0;
	pPhoneNumber->lPersonId = m_recPerson.lID;

	PHONE_NUMBERS* p;

	m_oPhoneNumbersMap.SetAt(pPhoneNumber->lID, pPhoneNumber);

	InsertRecordToListCtrl(pPhoneNumber);
}
