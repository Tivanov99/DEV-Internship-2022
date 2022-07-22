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
	DDX_Control(pDX, IDC_EDB_POSTAL_CODE, StrPostalCode);
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
	StrPostalCode.SetWindowText(strPostalCode);
}

void CCitiesDialog::OnOK()
{
	CString strCityNameErrorMessage = ValidateTextData(StrCitiesName, nMinCityNameLenght, nMaxCityNameLenght);
	if (strCityNameErrorMessage.GetLength() > 0)
	{
		AfxMessageBox(_T("The 'City name' field: ") + strCityNameErrorMessage);
		return;
	}

	CString strAreaNameErrorMessage = ValidateTextData(StrAreaName, nMinCityAreaNameLenght, nMaxCityAreaNameLenght);
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

	long lPostalCode = GetPostalCodeFromInputFiled();
	m_recCity.lPOSTAL_CODE = lPostalCode;

	CString strCityName;
	StrCitiesName.GetWindowText(strCityName);

	//TODO: Map input values to m_recCity;
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


CString CCitiesDialog::ValidateTextData(const CEdit& oCEdit, const int nMinLenght, const int nMaxLenght)
{
	CString strData;
	oCEdit.GetWindowText(strData);

	CString strErrorMessage;

	if (strData.GetLength() < nMinLenght)
	{
		strErrorMessage.AppendFormat(_T("The minimum length must be at least %i! "), nMinLenght);
	}
	if (strData.GetLength() > nMaxLenght)
	{
		strErrorMessage.AppendFormat(_T("The maximum length is %i! "), nMaxLenght);
	}
	if (!CheckForNotAllowedChars(strData))
	{
		strErrorMessage.Append(_T("The text field contains forbidden characters!"));
	}

	return strErrorMessage;
}


long CCitiesDialog :: GetPostalCodeFromInputFiled()
{
	CString strNewPostalCode;
	StrPostalCode.GetWindowText(strNewPostalCode);
	long lPostalCode = _wtol(strNewPostalCode);

	return lPostalCode;
}
bool CCitiesDialog::ValidatePostalCode()
{
	long lPostalCode = GetPostalCodeFromInputFiled();

	if (lPostalCode <= 0)
	{
		return false;
	}
	return true;
}

bool CCitiesDialog::CheckForNotAllowedChars(const CString& strValue)
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