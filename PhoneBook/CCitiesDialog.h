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
	CCitiesDialog(ContextMenuOperations eOperations, CITIES& recCity, CWnd* pParent = nullptr);   // standard constructor
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
	void SetDialogWindowAndOkButtonText();
	bool ValidateCityName();
	bool ValidateAreaName();
	bool ValidatePostalCode();


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
	ContextMenuOperations m_eOperations;
public:
	CButton btn_Ok;
};

