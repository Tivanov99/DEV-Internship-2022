// CCitiesDialog.cpp : implementation file
//

#include "pch.h"
#include "PhoneBook.h"
#include "afxdialogex.h"
#include "CCitiesDialog.h"
#include "CitiesView.h"
#include "CCitiesConfirmDeleteDialog.h"



// CCitiesDialog dialog

IMPLEMENT_DYNAMIC(CCitiesDialog, CDialog)

CCitiesDialog::CCitiesDialog(ContextMenuOperations eOperations, CITIES& recCity, CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CITIES_DIALOG, pParent)
{
	m_recCity = recCity;
	m_eOperations = eOperations;
}

CCitiesDialog::~CCitiesDialog()
{
}

void CCitiesDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDB_CITIES_NAME, StrCitiesName);
	DDX_Control(pDX, IDC_EDB_AREA_NAME, StrAreaName);
	DDX_Control(pDX, IDC_EDB_POSTAL_CODE, lPostalCode);
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

	StrCitiesName.SetLimitText(nMaxCityNameLenght);
	StrAreaName.SetLimitText(nMaxCityAreaNameLenght);

	FillingInputFields();
	SetDialogWindowAndOkButtonText();
	return TRUE;
}

void CCitiesDialog::FillingInputFields()
{
	StrCitiesName.SetWindowText(m_recCity.szCITY_NAME);
	StrAreaName.SetWindowText(m_recCity.szAREA_NAME);
	CString strPostalCode;
	strPostalCode.Format(_T("%d"), m_recCity.lPOSTAL_CODE);
	lPostalCode.SetWindowText(strPostalCode);
}

void CCitiesDialog::OnOK()
{

	CDialog::OnOK();
}


void CCitiesDialog::SetDialogWindowAndOkButtonText()
{
	switch (m_eOperations)
	{
	case  ContextMenuOperations::Create:
		this->SetWindowText(_T("Add city"));
		btn_Ok.SetWindowText(_T("Add"));
		break;
	case  ContextMenuOperations::Edit:
		this->SetWindowText(_T("Edit city"));
		btn_Ok.SetWindowText(_T("Edit"));
		break;
	default:
		break;
	}
}


bool CCitiesDialog::ValidateCityName()
{
	CString strCityName;
	StrCitiesName.GetWindowText(strCityName);
	if (strCityName.GetLength() < nMinCityNameLenght)
		return false;
	if (strCityName.GetString() == m_recCity.szCITY_NAME)
		return false;
	if (!CheckForNotAllowedChars(strCityName))
		return false;

	return true;
}
bool CCitiesDialog::ValidateAreaName()
{
	CString strAreaName;
	StrAreaName.GetWindowText(strAreaName);

	if (strAreaName.GetLength() < nMinCityAreaNameLenght)
		return false;
	if (strAreaName.GetString() == m_recCity.szAREA_NAME)
		return false;
	if (!CheckForNotAllowedChars(strAreaName))
		return false;

	return true;
}
bool CCitiesDialog::ValidatePostalCode()
{

}
bool CCitiesDialog::CheckForNotAllowedChars(CString strValue)
{
	for (INT_PTR i = 0; i < strValue.GetLength(); i++)
	{
		switch (strValue.GetAt(i))
		{
		case '!': return false;
		case '.': return false;
		case '?': return false;
		case ';': return false;
		case ':': return false;
		case ',': return false;
		case '|': return false;
		default:
			break;
		}
	}
	return true;
}