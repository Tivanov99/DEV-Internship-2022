#pragma once
#include "afxdialogex.h"
#include "Structures.h"
#include "CSelfClearingMap.h"
#include "DialogWindowEnumeration.h"


// CPhoneNumbersDialog dialog

class CPhoneNumbersDialog : public CDialog
{
	DECLARE_DYNAMIC(CPhoneNumbersDialog)

	//Constructor/Destructor
	//-----------------
public:
	CPhoneNumbersDialog(DialogWindowActions eOperation, PHONE_NUMBERS& recPhoneNumber, CSelfClearingMap<long, PHONE_TYPES*>& oPhoneTypesMap, CWnd* pParent = nullptr);   // standard constructor
	virtual ~CPhoneNumbersDialog();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PHONE_NUMBERS_DIALOG };
#endif

	//Methods
	//-----------------
private:
	/// <summary>Фунцкия заключваща всички входни полета.(Не разрешава редакция или въвеждане в тях)</summary>
	void LockInputFields();
	/// <summary>Попълва всички полета с данните от обекта който е подаден като аргумент 'recPhoneNumber' при извикването на диалога.<summary>
	void FillInputFileds();
	/// <summary>Функция която попълва всички въведени данни във входните полета по обекта 'm_recPhoneNumber' и запазва промените при клик на бутона 'Ok'.</summary>
	afx_msg void OnBnClickedOk();
	/// <summary>Функция която отменя всички направени промени и затваря диалоговия прозорец при клик на бутона 'Cancel'.</summary>
	afx_msg void OnBnClickedCancel();

	//Overrides
	//-----------------
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	/// <summary>Надстройва диалоговия прозорец при стартиране и попълва всички данни на подадения обект в полетата; </summary>
	/// <returns></returns>
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

	//Members
	//-----------------
private:
	/// <summary>Мембър съдържащ типът текуща операция</summary>
	DialogWindowActions m_eOperation;
	/// <summary>Мембър съдържащ запис представляващ телефонен номер.</summary>
	PHONE_NUMBERS& m_recPhoneNumber;
	/// <summary>Мембър съдържащ релация между ID-то на всички типове телефонни номера и обектите прочетени от базата.</summary>
	CSelfClearingMap<long, PHONE_TYPES*>& m_oPhoneTypesMap;
	/// <summary>Мембър представляващ падащо меню за типът телефонен номер в диалога.</summary>
	CComboBox m_cmbPhoneTypes;
	/// <summary>Мембър представляващ входното поле за телефонен номер в диалога.</summary>
	CEdit m_edbPhoneNumber;
};
