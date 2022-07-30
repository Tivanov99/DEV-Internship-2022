#include "pch.h"
#include "PhoneBook.h"
#include "afxdialogex.h"
#include "CPersonsDialog.h"
#include "resource.h"


IMPLEMENT_DYNAMIC(CPersonsDialog, CDialog)

CPersonsDialog::CPersonsDialog(DialogWindowActions eOperation, PERSONS& recPerson, CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_PERSONS_DIALOG, pParent), m_recPerson(recPerson), m_eOperation(eOperation)
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
}

BEGIN_MESSAGE_MAP(CPersonsDialog, CDialog)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

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
		//m_cmblscPhoneNumbers.EnableWindow(false);
	}


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
void CPersonsDialog::OnOK()
{
	/*CString strCityName;
	m_edbCityName.GetWindowText(strCityName);

	CString strCityNameErrorMessage = m_oDataValidator.ValidateTextData(strCityName, GlobalConstants::_nMinCityNameSize);
	if (strCityNameErrorMessage.GetLength() > 0)
	{
		AfxMessageBox(_T("The 'City name' field: ") + strCityNameErrorMessage);
		return;
	}

	CString strCityAreaName;
	m_edbCityAreaName.GetWindowText(strCityAreaName);

	CString strAreaNameErrorMessage = m_oDataValidator.ValidateTextData(strCityAreaName, GlobalConstants::_nMinCityAreaNameSize);
	if (strAreaNameErrorMessage.GetLength() > 0)
	{
		AfxMessageBox(_T("The 'Area name' field: ") + strAreaNameErrorMessage);
		return;
	}

	long lPostalCode = GetPostalCodeFromInputFiled();
	if (!m_oDataValidator.ValidatePostalCode(lPostalCode))
	{
		AfxMessageBox(_T("The 'Postal Code' filed must be positive number!"));
		return;
	}

	SetDataToRecord();*/

	CDialog::OnOK();
}