#pragma once
#include "afxdialogex.h"


// CCitiesConfirmDeleteDialog dialog

class CCitiesConfirmDeleteDialog : public CDialog
{
	DECLARE_DYNAMIC(CCitiesConfirmDeleteDialog)

public:
	CCitiesConfirmDeleteDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CCitiesConfirmDeleteDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COMFIRM_DELETE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
