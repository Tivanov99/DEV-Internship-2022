#pragma once
#include "afxdialogex.h"
#include "Structures.h"


// CPhoneNumbersDialog dialog

class CPhoneNumbersDialog : public CDialog
{
	DECLARE_DYNAMIC(CPhoneNumbersDialog)

	//Constructor/Destructor
	//-----------------
public:
	CPhoneNumbersDialog(PHONE_NUMBERS& recPhoneNumber,CPhoneTypesArray& oPhonetypesArray, CWnd* pParent = nullptr);   // standard constructor
	virtual ~CPhoneNumbersDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PHONE_NUMBERS_DIALOG };
#endif

	//Methods
	//-----------------
private:
	void FillInputFileds();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

	//Overrides
	//-----------------
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	/// <summary>
	///Надстройва диалоговия прозорец при стартиране и попълва всички данни на подадения обект в полетата; 
	/// </summary>
	/// <returns></returns>
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

	//Members
	//-----------------
private:
	/// <summary>
	/// Мембър съдържащ запис представляващ телефонен номер.
	/// </summary>
	PHONE_NUMBERS& m_recPhoneNumber;

	/// <summary>
	/// Мембър съдържащ всички типове телефонен номер
	/// </summary>
	CPhoneTypesArray& m_oPhonetypesArray;

	/// <summary>
	/// Мембър представляващ падащо меню за типът телефонен номер в диалога.
	/// </summary>
	CComboBox m_cmbPhoneTypes;

	/// <summary>
	/// Мембър представляващ входното поле за телефонен номер в диалога.
	/// </summary>
	CEdit m_edbPhoneNumber;
};
