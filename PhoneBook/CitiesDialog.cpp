// CCitiesDialog.cpp : implementation file
//
#include "pch.h"
#include "PhoneBook.h"
#include "afxdialogex.h"
#include "CitiesDialog.h"
#include "CitiesView.h"
#include "GlobalConstants.h"
// CCitiesDialog dialog

IMPLEMENT_DYNAMIC(CCitiesDialog, CDialog)

CCitiesDialog::CCitiesDialog(DialogWindowActions eOperation, CITIES& recCity, CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CITIES_DIALOG, pParent), m_recCity(recCity), m_eOperation(eOperation)
{
}

CCitiesDialog::~CCitiesDialog()
{
}

void CCitiesDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDB_CITIES_NAME, m_edbCityName);
	DDX_Control(pDX, IDC_EDB_AREA_NAME, m_edbCityAreaName);
	DDX_Control(pDX, IDC_EDB_POSTAL_CODE, m_edbCityPostalCode);
	DDX_Control(pDX, IDOK, btn_Ok);
}


BEGIN_MESSAGE_MAP(CCitiesDialog, CDialog)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()


// CCitiesDialog message handlers


BOOL CCitiesDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (m_eOperation != DialogWindowActions::InsertData)
		FillingInputFields();

	m_edbCityName.SetLimitText(GlobalConstants::_nCityNameSize);
	m_edbCityAreaName.SetLimitText(GlobalConstants::_nCityAreaNameSize);
	SetDialogTitle();

	if (m_eOperation == DialogWindowActions::ReadData)
	{
		m_edbCityName.EnableWindow(false);
		m_edbCityAreaName.EnableWindow(false);
		m_edbCityPostalCode.EnableWindow(false);
	}
	return TRUE;
}

void CCitiesDialog::FillingInputFields()
{
	m_edbCityName.SetWindowText(m_recCity.szCityName);
	m_edbCityAreaName.SetWindowText(m_recCity.szAreaName);

	CString strPostalCode;
	strPostalCode.Format(_T("%d"), m_recCity.lPostalCode);
	m_edbCityPostalCode.SetWindowText(strPostalCode);
}

void CCitiesDialog::OnOK()
{
	CString strCityName;
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

	SetDataToRecord();

	CDialog::OnOK();
}

void CCitiesDialog::SetDataToRecord()
{
	long lPostalCode = GetPostalCodeFromInputFiled();
	m_recCity.lPostalCode = lPostalCode;

	CString strCityName;
	m_edbCityName.GetWindowText(strCityName);
	_tcscpy_s(m_recCity.szCityName, strCityName);

	CString strAreaName;
	m_edbCityAreaName.GetWindowText(strAreaName);
	_tcscpy_s(m_recCity.szAreaName, strAreaName);
}

void CCitiesDialog::SetDialogTitle()
{
	switch (m_eOperation)
	{
	case  DialogWindowActions::InsertData:
		this->SetWindowText(_T("Add city"));
		break;
	case  DialogWindowActions::ReadData:
		this->SetWindowText(_T("Read city data"));
		break;
	case  DialogWindowActions::EditData:
		this->SetWindowText(_T("Edit city"));
		break;
	default:
		break;
	}
}

long CCitiesDialog::GetPostalCodeFromInputFiled()
{
	CString strNewPostalCode;
	m_edbCityPostalCode.GetWindowText(strNewPostalCode);
	long lPostalCode = _wtol(strNewPostalCode);

	return lPostalCode;
}