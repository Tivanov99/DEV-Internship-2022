#include "pch.h"
#include "CPersonsDialog.h"
#include "resource.h"


CPersonsDialog::CPersonsDialog(DialogWindowActions eOperations, PERSONS& recPerson, CWnd* pParent = nullptr)
	:CDialog(IDD_PERSONS_DIALOG,pParent),m_recPerson(recPerson),m_eOperation(eOperations)
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
	//DDX_Control(pDX, IDC_LSC_PERSON_PHONE_NUMBERS, m_lscPhoneNumbers);

	/*m_cmbCitiesNames.SetItemData();
	m_cmbCitiesNames.InsertString();*/
	/*DDX_Control(pDX, IDC_LIST2, test);*/
	DDX_Control(pDX, IDC_CMB_LSC_PERONS_PHONE_NUMBERS, m_cmblscPhoneNumbers);
}

BOOL CPersonsDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (m_eOperation != DialogWindowActions::InsertData)
		//FillingInputFields();

	/*m_edbCityName.SetLimitText(GlobalConstants::_nCityNameSize);
	m_edbCityAreaName.SetLimitText(GlobalConstants::_nCityAreaNameSize);*/
	SetDialogTitle();

	if (m_eOperation == DialogWindowActions::ReadData)
	{
		m_edbPersonFirstName.EnableWindow(false);
		m_edbPersonSecondName.EnableWindow(false);
		m_edbPersonLastName.EnableWindow(false);
		m_edbPersonUcn.EnableWindow(false);
		m_cmbCitiesNames.EnableWindow(false);
		m_cmblscPhoneNumbers.EnableWindow(false);
	}

	m_cmblscPhoneNumbers.InsertColumn(0, _T("Phone number"), LVCFMT_LEFT, GlobalConstants::_nColumnWidth, 1);
	m_cmblscPhoneNumbers.InsertColumn(1, _T("Phone number type"), LVCFMT_LEFT, GlobalConstants::_nColumnWidth, 1);

	m_cmblscPhoneNumbers.SetComboColumns(1);


	return TRUE;
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