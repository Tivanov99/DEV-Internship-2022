#include "pch.h"
#include "PhoneBook.h"
#include "afxdialogex.h"
#include "CPersonsDialog.h"
#include "resource.h"


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
	map<PHONE_NUMBERS*, PHONE_TYPES*>& oMap, CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_PERSONS_DIALOG, pParent), m_recPerson(recPerson), m_eOperation(eOperation), m_oCitiesArray(oCitiesArray),
	m_oMap(oMap)
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
	m_lscPersonPhoneNumbers.InsertColumn(nColumnNumber++, _T("�����"), LVCFMT_LEFT, GlobalConstants::_nColumnWidth, 1);
	m_lscPersonPhoneNumbers.InsertColumn(nColumnNumber++, _T("���"), LVCFMT_CENTER, GlobalConstants::_nColumnWidth, 1);
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

		CString strCityName;
		strCityName.Append(pCity->szCITY_NAME);

		if (pCity->lID == m_recPerson.lCITY_ID)
			strCityName.Append(_T("(CURRENT)"));

		int nResult = m_cmbCitiesNames.AddString(strCityName);
		m_cmbCitiesNames.SetItemData(nResult, reinterpret_cast<DWORD_PTR>(pCity));
	}
}

void CPersonsDialog::FillPhoneNumbers()
{

	map<PHONE_NUMBERS*, PHONE_TYPES*>::iterator itr;

	for (itr = m_oMap.begin(); itr != m_oMap.end(); ++itr)
	{
		PHONE_NUMBERS* pCurrentPhoneNumber = itr->first;
		if (pCurrentPhoneNumber == NULL)
			continue;

		PHONE_TYPES* pCurrentPhoneType = itr->second;
		if (pCurrentPhoneType == NULL)
			continue;

		const int nRow = m_lscPersonPhoneNumbers.GetItemCount();

		m_lscPersonPhoneNumbers.InsertItem(nRow, pCurrentPhoneNumber->szPHONE_NUMBER);

		m_lscPersonPhoneNumbers.SetItemText(nRow, 1, pCurrentPhoneType->szPHONE_TYPE);

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

	CString strPersonLastdName;
	m_edbPersonLastName.GetWindowText(strPersonLastdName);

	CString strPersonLastNameErrorMessage = m_oTextValidator.ValidateTextData(strPersonLastdName,
		GlobalConstants::_nPersonLastNameMinSize);
	if (strPersonLastNameErrorMessage.GetLength() > 0)
	{
		AfxMessageBox(_T("The 'Last name' field: ") + strPersonLastNameErrorMessage);
		return;
	}

	CITIES* pCity = (CITIES*)m_cmbCitiesNames.GetItemData(m_cmbCitiesNames.GetCurSel());

	m_recPerson.lCITY_ID = pCity->lID;

	CDialog::OnOK();
}

void CPersonsDialog::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}


void CPersonsDialog::OnContextMenuEdit()
{
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
	// TODO: Add your command handler code here
}
