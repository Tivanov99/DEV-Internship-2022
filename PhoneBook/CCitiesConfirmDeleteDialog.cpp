// CCitiesConfirmDeleteDialog.cpp : implementation file
//

#include "pch.h"
#include "PhoneBook.h"
#include "afxdialogex.h"
#include "CCitiesConfirmDeleteDialog.h"


// CCitiesConfirmDeleteDialog dialog

IMPLEMENT_DYNAMIC(CCitiesConfirmDeleteDialog, CDialog)

CCitiesConfirmDeleteDialog::CCitiesConfirmDeleteDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_COMFIRM_DELETE, pParent)
{

}

CCitiesConfirmDeleteDialog::~CCitiesConfirmDeleteDialog()
{
}

void CCitiesConfirmDeleteDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, BTNConfirm);
}


BEGIN_MESSAGE_MAP(CCitiesConfirmDeleteDialog, CDialog)
END_MESSAGE_MAP()


// CCitiesConfirmDeleteDialog message handlers
