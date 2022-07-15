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
	DDX_Control(pDX, IDC_EDB_CITIES_NAME, m_EditBoxName);
}


BEGIN_MESSAGE_MAP(CCitiesDialog, CDialog)
	//ON_COMMAND(ID_OPTIONS_CITIES, &CCitiesDialog::OnOptionsCities)
END_MESSAGE_MAP()


// CCitiesDialog message handlers


BOOL CCitiesDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_EditBoxName.SetWindowText(_T("Burgas"));


	//m_EditBoxName.SetLimitText();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CCitiesDialog::OnOK()
{
	CString strText;
	m_EditBoxName.GetWindowText(strText);
	// TODO: Add your specialized code here and/or call the base class

	CDialog::OnOK();
}

