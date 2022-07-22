#pragma once
#include "afxdialogex.h"
#include "Structures.h"


// CCitiesDialog dialog

class CCitiesDialog : public CDialog
{
	DECLARE_DYNAMIC(CCitiesDialog)

	// Constructor / Destructor
	// ----------------
public:
	CCitiesDialog(int nOperations, CITIES& recCity, CWnd* pParent = nullptr);   // standard constructor
	virtual ~CCitiesDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CITIES_DIALOG };
#endif
	DECLARE_MESSAGE_MAP()
	
	// Methods
	// ----------------
private:
	void FillingInputFields();

	// Overrides
	// ----------------
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	// Members
	// ----------------
private:
	CListCtrl m_CitiesList;
	CITIES m_recCity;
	CEdit StrCitiesName;
	CEdit StrAreaName;
	CEdit lPostalCode;
public:
	CButton btn_Ok;
};

