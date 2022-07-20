// CCitiesDialog.cpp : implementation file
//

#include "pch.h"
#include "PhoneBook.h"
#include "afxdialogex.h"
#include "CCitiesDialog.h"
#include "CitiesView.h"



// CCitiesDialog dialog

IMPLEMENT_DYNAMIC(CCitiesDialog, CDialog)

CCitiesDialog::CCitiesDialog(CITIES& recCity, CWnd* pParent /*=nullptr*/)
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
	DDX_Control(pDX, IDC_CHB_UPDATE_RECORD, CHBUpdate);
	DDX_Control(pDX, IDC_CHB_DELETE_RECORD, CHBDelete);
	DDX_Control(pDX, IDC_BTN_UPDATE_RECORD, BTNUpdate);
	DDX_Control(pDX, IDC_BTN_DELETE_RECORD, BTNDelete);
}


BEGIN_MESSAGE_MAP(CCitiesDialog, CDialog)
	//ON_COMMAND(ID_OPTIONS_CITIES, &CCitiesDialog::OnOptionsCities)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_BN_CLICKED(IDC_CHB_UPDATE_RECORD, &CCitiesDialog::OnBnClickedChbUpdateRecord)
	ON_BN_CLICKED(IDC_CHB_DELETE_RECORD, &CCitiesDialog::OnBnClickedChbDeleteRecord)
END_MESSAGE_MAP()


// CCitiesDialog message handlers


BOOL CCitiesDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	LockAllInputFileds();

	FillingInputFields();

	BTNDelete.EnableWindow(0);
	BTNUpdate.EnableWindow(0);

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
	CString strText;
	// TODO: Add your specialized code here and/or call the base class

	CDialog::OnOK();
}


void CCitiesDialog::OnBnClickedChbUpdateRecord()
{
	if (CHBDelete.GetCheck() == 1)
	{
		CHBDelete.SetCheck(0);
	}
	if (CHBUpdate.GetCheck() == 1)
	{
		BTNDelete.EnableWindow(0);
		BTNUpdate.EnableWindow(1);
		UnLockAllInputFileds();
	}
	else
	{
		BTNUpdate.EnableWindow(0);
		LockAllInputFileds();
	}
	// TODO: Add your control notification handler code here
}


void CCitiesDialog::OnBnClickedChbDeleteRecord()
{
	if (CHBUpdate.GetCheck() == 1)
	{
		CHBUpdate.SetCheck(0);
	}
	if (CHBDelete.GetCheck() == 1)
	{
		BTNDelete.EnableWindow(1);
		BTNUpdate.EnableWindow(0);
		LockAllInputFileds();
	}
	else
	{
		BTNDelete.EnableWindow(0);
	}
}

void CCitiesDialog::LockAllInputFileds()
{
	StrCitiesName.EnableWindow(0);
	StrAreaName.EnableWindow(0);
	lPostalCode.EnableWindow(0);
}

void CCitiesDialog::UnLockAllInputFileds()
{
	StrCitiesName.EnableWindow(1);
	StrAreaName.EnableWindow(1);
	lPostalCode.EnableWindow(1);
}
