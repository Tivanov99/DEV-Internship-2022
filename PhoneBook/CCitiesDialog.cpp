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
	ON_BN_CLICKED(IDC_BTN_DELETE_RECORD, &CCitiesDialog::OnBnClickedBtnDeleteRecord)
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
	if (CHBDelete.GetCheck() == nTurnOn)
	{
		CHBDelete.SetCheck(nTurnOff);
	}
	if (CHBUpdate.GetCheck() == nTurnOn)
	{
		BTNDelete.EnableWindow(nTurnOff);
		BTNUpdate.EnableWindow(nTurnOn);
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
	if (CHBUpdate.GetCheck() == nTurnOn)
	{
		CHBUpdate.SetCheck(nTurnOff);
		BTNUpdate.EnableWindow(nTurnOff);
	}
	if (CHBDelete.GetCheck() == nTurnOn)
	{
		BTNDelete.EnableWindow(nTurnOn);
		LockAllInputFileds();
	}
	else
	{
		BTNDelete.EnableWindow(nTurnOff);
	}
}

void CCitiesDialog::LockAllInputFileds()
{
	StrCitiesName.EnableWindow(nTurnOff);
	StrAreaName.EnableWindow(nTurnOff);
	lPostalCode.EnableWindow(nTurnOff);
}

void CCitiesDialog::UnLockAllInputFileds()
{
	StrCitiesName.EnableWindow(nTurnOn);
	StrAreaName.EnableWindow(nTurnOn);
	lPostalCode.EnableWindow(nTurnOn);
}


void CCitiesDialog::OnBnClickedBtnDeleteRecord()
{
	CCitiesConfirmDeleteDialog oConfirmDialog;
	oConfirmDialog.DoModal();
}
