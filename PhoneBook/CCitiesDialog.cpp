// CCitiesDialog.cpp : implementation file
//

#include "pch.h"
#include "PhoneBook.h"
#include "afxdialogex.h"
#include "CCitiesDialog.h"
#include "CitiesView.h"



// CCitiesDialog dialog

IMPLEMENT_DYNAMIC(CCitiesDialog, CDialog)

CCitiesDialog::CCitiesDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CITIES_DIALOG, pParent)
{

}

CCitiesDialog::~CCitiesDialog()
{
}

void CCitiesDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CITIES_LIST, m_CitiesList);
}


BEGIN_MESSAGE_MAP(CCitiesDialog, CDialog)
	//ON_COMMAND(ID_OPTIONS_CITIES, &CCitiesDialog::OnOptionsCities)
END_MESSAGE_MAP()


// CCitiesDialog message handlers


BOOL CCitiesDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_CitiesList.InsertColumn(0, _T("Име"));
	m_CitiesList.InsertColumn(1, _T("Регион"));

	m_CitiesList.SetColumnWidth(0, 90);
	m_CitiesList.SetColumnWidth(1, 90);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CCitiesDialog::OnOK()
{
	CString strText;
	// TODO: Add your specialized code here and/or call the base class

	CDialog::OnOK();
}

