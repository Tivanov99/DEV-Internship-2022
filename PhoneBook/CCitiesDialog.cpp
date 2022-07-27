// CCitiesDialog.cpp : implementation file
//

#include "pch.h"
#include "PhoneBook.h"
#include "afxdialogex.h"
#include "CCitiesDialog.h"
#include "CitiesView.h"
#include "GlobalConstants.h"




// CCitiesDialog dialog

IMPLEMENT_DYNAMIC(CCitiesDialog, CDialog)

CCitiesDialog::CCitiesDialog(ContextMenuOperations eOperations, CITIES& recCity, CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CITIES_DIALOG, pParent), m_recCity(recCity), m_eOperations(eOperations)
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

	if (m_eOperations != ContextMenuOperations::Create)
		FillingInputFields();

	m_edbCityName.SetLimitText(GlobalConstants::_nCityNameSize);
	m_edbCityAreaName.SetLimitText(GlobalConstants::_nCityAreaNameSize);
	SetDialogTitle();

	return TRUE;
}

void CCitiesDialog::FillingInputFields()
{
	m_edbCityName.SetWindowText(m_recCity.szCITY_NAME);
	m_edbCityAreaName.SetWindowText(m_recCity.szAREA_NAME);

	CString strPostalCode;
	strPostalCode.Format(_T("%d"), m_recCity.lPOSTAL_CODE);
	m_edbCityPostalCode.SetWindowText(strPostalCode);
}

void CCitiesDialog::OnOK()
{
	CString strCityNameErrorMessage = ValidateTextData(m_edbCityName, GlobalConstants::_nMinCityNameSize);
	if (strCityNameErrorMessage.GetLength() > 0)
	{
		AfxMessageBox(_T("The 'City name' field: ") + strCityNameErrorMessage);
		return;
	}

	CString strAreaNameErrorMessage = ValidateTextData(m_edbCityAreaName, GlobalConstants::_nMinCityAreaNameSize);
	if (strAreaNameErrorMessage.GetLength() > 0)
	{
		AfxMessageBox(_T("The 'Area name' field: ") + strAreaNameErrorMessage);
		return;
	}

	bool bValidPostalCode = ValidatePostalCode();
	if (!bValidPostalCode)
	{
		AfxMessageBox(_T("The 'Postal Code' filed must be positive number!"));
		return;
	}

	SetDataToRecord();

	CDialog::OnOK();
}

void CCitiesDialog ::SetDataToRecord()
{
	long lPostalCode = GetPostalCodeFromInputFiled();
	m_recCity.lPOSTAL_CODE = lPostalCode;

	CString strCityName;
	m_edbCityName.GetWindowText(strCityName);
	_tcscpy_s(m_recCity.szCITY_NAME, strCityName);

	CString strAreaName;
	m_edbCityAreaName.GetWindowText(strAreaName);
	_tcscpy_s(m_recCity.szAREA_NAME, strAreaName);
}

void CCitiesDialog::SetDialogTitle()
{
	switch (m_eOperations)
	{
	case  ContextMenuOperations::Create:
		this->SetWindowText(_T("Add city"));
		break;
	case  ContextMenuOperations::Edit:
		this->SetWindowText(_T("Edit city"));
		break;
	default:
		break;
	}
}


CString CCitiesDialog::ValidateTextData(const CEdit& oCEdit, const int nMinLenght)
{
	CString strData;
	oCEdit.GetWindowText(strData);

	CString strErrorMessage;

	if (strData.GetLength() < nMinLenght)
	{
		strErrorMessage.AppendFormat(_T("The minimum length must be at least %i! "), nMinLenght);
	}
	if (!CheckForSymbols(strData))
	{
		strErrorMessage.Append(_T("The text field contains forbidden sybmols!"));
	}

	return strErrorMessage;
}


long CCitiesDialog::GetPostalCodeFromInputFiled()
{
	CString strNewPostalCode;
	m_edbCityPostalCode.GetWindowText(strNewPostalCode);
	long lPostalCode = _wtol(strNewPostalCode);

	return lPostalCode;
}
bool CCitiesDialog::ValidatePostalCode()
{
	long lPostalCode = GetPostalCodeFromInputFiled();

	return	lPostalCode <= 0 ? false : true;
}

bool CCitiesDialog::CheckForSymbols(const CString& strValue) const
{
	for (INT_PTR i = 0; i < strValue.GetLength(); i++)
	{
		switch (strValue.GetAt(i))
		{
		case '!':;
		case '.':;
		case '?':;
		case ';':;
		case ':':;
		case ',':;
		case '|':;
		default:
			continue;
		}
		return false;
	}
	return true;
}