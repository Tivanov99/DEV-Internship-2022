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
	ON_WM_LBUTTONDOWN()
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
	CPhoneNumbersArray& oPhoneNumbersArray, map<long, PHONE_TYPES*>& oMap, CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_PERSONS_DIALOG, pParent), m_recPerson(recPerson), m_eOperation(eOperation), m_oCitiesArray(oCitiesArray),
	m_oPhoneNumbersArray(oPhoneNumbersArray),m_oMap(oMap)
{
}
CPersonsDialog :: ~CPersonsDialog() {};

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
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

void CPersonsDialog::ManageContextMenuItems(CCmdUI* pCmdUI)
{
	UINT uSelectedCount = m_lscPersonPhoneNumbers.GetSelectedCount();

	if (pCmdUI->m_nID == ID_EDIT_CONTEXT_INSERT && uSelectedCount==0)
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
	m_edbPersonFirstName.SetWindowText(m_recPerson.szFIRST_NAME);
	m_edbPersonFirstName.SetLimitText(GlobalConstants::_nPersonFirstNameSize);

	m_edbPersonSecondName.SetWindowText(m_recPerson.szSECOND_NAME);
	m_edbPersonSecondName.SetLimitText(GlobalConstants::_nPersonSecondNameSize);

	m_edbPersonLastName.SetWindowText(m_recPerson.szLAST_NAME);
	m_edbPersonLastName.SetLimitText(GlobalConstants::_nPersonLastNameSize);

	m_edbPersonUcn.SetWindowText(m_recPerson.szUCN);
	m_edbPersonUcn.SetLimitText(GlobalConstants::_nPersonUcnSize);
}

void CPersonsDialog::FillCitiesComboBox()
{
	for (INT_PTR i = 0; i < m_oCitiesArray.GetCount(); i++)
	{
		CITIES* pCity = m_oCitiesArray.GetAt(i);
		if (pCity == NULL)
			continue;

		int nResult = m_cmbCitiesNames.AddString(pCity->szCITY_NAME);
		m_cmbCitiesNames.SetItemData(nResult, reinterpret_cast<DWORD_PTR>(pCity));

		if (pCity->lID == m_recPerson.lCITY_ID)
			m_cmbCitiesNames.SetCurSel(nResult);
	}
}

void CPersonsDialog::FillPhoneNumbers()
{
	map<long, PHONE_TYPES*>::iterator itr;
	for (INT_PTR i = 0; i < m_oPhoneNumbersArray.GetCount(); i++)
	{
		PHONE_NUMBERS* pCurrentPhoneNumber = m_oPhoneNumbersArray.GetAt(i);

		itr = m_oMap.find(pCurrentPhoneNumber->lPHONE_TYPE_ID);

		PHONE_TYPES* pPhoneType = itr->second;

		const int nRow = m_lscPersonPhoneNumbers.GetItemCount();

		m_lscPersonPhoneNumbers.InsertItem(nRow, pCurrentPhoneNumber->szPHONE_NUMBER);

		m_lscPersonPhoneNumbers.SetItemText(nRow, 1, pPhoneType->szPHONE_TYPE);

		m_lscPersonPhoneNumbers.SetItemData(nRow, reinterpret_cast<DWORD_PTR>(pCurrentPhoneNumber));
	}
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

	//m_recPerson.szADDRESS
	m_edbPersonFirstName.GetWindowText(strPersonFirstName);
	_tcscpy_s(m_recPerson.szFIRST_NAME, strPersonFirstName);

	m_edbPersonSecondName.GetWindowText(strPersonSecondName);
	_tcscpy_s(m_recPerson.szSECOND_NAME, strPersonSecondName);

	m_edbPersonLastName.GetWindowText(strPersonLastName);
	_tcscpy_s(m_recPerson.szLAST_NAME, strPersonLastName);

	CString strPersonUcn;
	m_edbPersonLastName.GetWindowText(strPersonUcn);
	_tcscpy_s(m_recPerson.szUCN, strPersonUcn);

	m_recPerson.lCITY_ID = pCity->lID;

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

	CPhoneNumbersDialog oPhoneNumbersDialog(*pPhoneNumber, m_oMap);

	if (oPhoneNumbersDialog.DoModal() != IDOK)
		return;
	// TODO: Add your command handler code here
}


void CPersonsDialog::OnContextMenuDelete()
{
	// TODO: Add your command handler code here
}


void CPersonsDialog::OnContextMenuReadData()
{
	// TODO: Add your command handler code here
}


void CPersonsDialog::OnContextMenuInsert()
{
	PHONE_NUMBERS* pPhoneNumber = new PHONE_NUMBERS;
	_tcscpy_s(pPhoneNumber->szPHONE_NUMBER, _T(""));


	CPhoneNumbersDialog oPhoneNumbersDialog(*pPhoneNumber, m_oMap);

	if (oPhoneNumbersDialog.DoModal() != IDOK)
	{
		pPhoneNumber = NULL;
		delete pPhoneNumber;
		return;
	}


	// TODO: Add your command handler code here
}
