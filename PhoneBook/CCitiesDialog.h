#pragma once
#include "afxdialogex.h"


// CCitiesDialog dialog

class CCitiesDialog : public CDialog
{
	DECLARE_DYNAMIC(CCitiesDialog)

public:
	CCitiesDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CCitiesDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CITIES_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	
	DECLARE_MESSAGE_MAP()
private:
	CListCtrl m_CitiesList;
public:
	CEdit StrCitiesName;
	CEdit StrAreaName;
	CEdit nPostalCode;
};

