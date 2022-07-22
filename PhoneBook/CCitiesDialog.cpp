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

CCitiesDialog::CCitiesDialog(int nOperations, CITIES& recCity, CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CITIES_DIALOG, pParent)
{
	m_recCity = recCity;
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

	StrCitiesName.SetWindowText(m_recCity.szCITY_NAME);
	StrAreaName.SetWindowText(m_recCity.szAREA_NAME);
	CString strPostalCode;
	strPostalCode.Format(_T("%d"), m_recCity.lPOSTAL_CODE);
	lPostalCode.SetWindowText(strPostalCode);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
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

