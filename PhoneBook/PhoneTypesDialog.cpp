#include "pch.h"
#include "PhoneTypesDialog.h"
#include "resource.h"

IMPLEMENT_DYNAMIC(CPhoneTypesDialog, CDialog)

BEGIN_MESSAGE_MAP(CPhoneTypesDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CPhoneTypesDialog::OnBnClickedOk)
END_MESSAGE_MAP()

CPhoneTypesDialog::CPhoneTypesDialog(DialogWindowActions eOperations, PHONE_TYPES& recPhoneType, CWnd* pParent /*=nullptr*/)
	:CDialog(IDD_PHONE_TYPES_DIALOG, pParent), m_recPhoneType(recPhoneType), m_eOperation(eOperations)
{};
CPhoneTypesDialog::~CPhoneTypesDialog() {};

BOOL CPhoneTypesDialog::OnInitDialog()
{
	if (!CDialog::OnInitDialog())
		return FALSE;

	if(m_eOperation!= DialogWindowActions::InsertData)
		SetDialogTitle();

	if (m_eOperation == DialogWindowActions::ReadData)
		m_edbPhoneType.EnableWindow(false);

	m_edbPhoneType.SetWindowText(m_recPhoneType.szPhoneType);
	return TRUE;
}

void CPhoneTypesDialog::SetDialogTitle()
{
	switch (m_eOperation)
	{
	case  DialogWindowActions::InsertData:
		this->SetWindowText(_T("Add phone type"));
		break;
	case  DialogWindowActions::ReadData:
		this->SetWindowText(_T("Read phone type"));
		break;
	case  DialogWindowActions::EditData:
		this->SetWindowText(_T("Edit phone type"));
		break;
	default:
		break;
	}
}
void CPhoneTypesDialog::SetDataToRecord()
{
	CString strPhoneType;
	m_edbPhoneType.GetWindowText(strPhoneType);

	_tcscpy_s(m_recPhoneType.szPhoneType, strPhoneType);
}

void CPhoneTypesDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDB_PHONE_TYPE, m_edbPhoneType);
}

void CPhoneTypesDialog::OnBnClickedOk()
{
	CString strPhoneType;
	m_edbPhoneType.GetWindowText(strPhoneType);
	if (strPhoneType.GetLength() <= 2)
	{
		CString strErrorMessage;
		strErrorMessage.Format(_T("Phone Types should be between %d and %d characters long!"), GlobalConstants::_nPhoneTypeMinLenght, GlobalConstants::_nPhoneTypeMaxLenght);
		AfxMessageBox(strErrorMessage);
		return;
	}
	SetDataToRecord();
	CDialog::OnOK();
}
