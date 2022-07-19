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
	DDX_Control(pDX, IDC_EDB_POSTAL_CODE, nPostalCode);
}


BEGIN_MESSAGE_MAP(CCitiesDialog, CDialog)
	//ON_COMMAND(ID_OPTIONS_CITIES, &CCitiesDialog::OnOptionsCities)
END_MESSAGE_MAP()


// CCitiesDialog message handlers


BOOL CCitiesDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CCitiesDialog::OnOK()
{
	CString strText;
	// TODO: Add your specialized code here and/or call the base class

	CDialog::OnOK();
}

