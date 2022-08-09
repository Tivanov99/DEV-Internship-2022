#pragma once
#include "Structures.h"
#include "DialogWindowEnumeration.h"
#include "TextDataValidator.h"
#include <map>
#include "CSelfClearingMap.h"
using namespace std;




class CPersonsDialog : public CDialog
{
	//Constants
	// ----------------
	DECLARE_DYNAMIC(CPersonsDialog)

public:
	CPersonsDialog(DialogWindowActions eOperations, PERSONS& recPerson, CCitiesArray& oCitiesArray,
		CPhoneNumbersArray& oPhoneNumbersArray, CSelfClearingMap<long, PHONE_TYPES*>& oPhoneTypesMap, CWnd* pParent = nullptr);  // standard constructor
	virtual ~CPersonsDialog();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PERSONS_DIALOG };
#endif
	DECLARE_MESSAGE_MAP()

	// Methods
	// ----------------

public:
	void OnContextMenu(CWnd* /*pWnd*/, CPoint point);
private:
	/// <summary>Фунцкия която актуализира лист контролата която съдържа телефонните номера.</summary>
	void UpdateListCtrlRecord();
	/// <summary>Функция която добавя нов запис към лист контролата която съдържа телефонните номера.</summary>
	/// <param name="pPhoneNumber">Запис който ще бъде добавен,</param>
	void InsertRecordToListCtrl(PHONE_NUMBERS* pPhoneNumber);
	/// <summary>Функция която връща item data на текущия запис от лист контролата.</summary>
	PHONE_NUMBERS* GetSelectedRecordItemData();
	/// <summary>Функция която определя коя фунцкия от контекстното меню може да бъде използвана.</summary>
	void ManageContextMenuItems(CCmdUI* pCmdUI);
	/// <summary>Попълва всички входни полета с данните идващи от 'm_recPerson'.</summary>
	void FillPersonDataFields();
	/// <summary>Попълва 'm_cmbCitiesNames' с всички градове идващи като аргумент 'oCitiesArray' при извикването на диалога.</summary>
	void FillCitiesComboBox();
	/// <summary>Попълва 'm_lscPersonPhoneNumbers' с всички телефонни номера идващи като аргумент 'oCitiesArray' при извикването на диалога.</summary>
	void FillPhoneNumbers();
	/// <summary>Според командата в 'm_eOperation' задава име на прозореца.</summary>
	void SetDialogTitle();
	/// <summary>Функция която конфигурита лист контролата в която се съдържат всички телефонни номера.</summary>
	void ConfiguratePhoneNumbersLsc();

	// Overrides
	// ----------------
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	/// <summary>Надстройва диалоговия прозорец при стартиране и попълва всички данни на подадения обект в полетата; </summary>
	virtual BOOL OnInitDialog();
	/// <summary>Извиква се при натиска не бутона 'Ок'.</summary>
	virtual void OnOK();

	// Members
	// ----------------
private:
	/// <summary>Мембър съдържащ всички телефонни номера за текущият Person.</summary>
	CPhoneNumbersArray& m_oPhoneNumbersArray;
	/// <summary>Мембър съдържащ релация между ID-то на всички типове телефонни номера и обектите прочетени от базата.</summary>
	CSelfClearingMap<long, PHONE_TYPES*>& m_oPhoneTypesMap;
	/// <summary>Референция към подаден запис при извикването на диалога.</summary>
	PERSONS& m_recPerson;
	/// <summary>Референция към подаден масив  при извикването на диалога който съдържа всички градове.</summary>
	CCitiesArray& m_oCitiesArray;
	/// <summary>Мембър съдържащ типът на текущата операция подаден като аргумент при извикването на диалога.</summary>
	DialogWindowActions m_eOperation;
	/// <summary>Мембър отговарящ за входното поле съдържащо името на контакта.</summary>
	CEdit m_edbPersonFirstName;
	/// <summary>Мембър отговарящ за входното поле съдържащо презимето на контакта.</summary>
	CEdit m_edbPersonSecondName;
	/// <summary>Мембър отговарящ за входното поле съдържащо фамилното име на контакта.</summary>
	CEdit m_edbPersonLastName;
	/// <summary>Мембър отговарящ за входното поле съдържащо егн-то на контакта.</summary>
	CEdit m_edbPersonUcn;
	/// <summary>Мембър отговарящ за падащото меню с всички градове в него.</summary>
	CComboBox m_cmbCitiesNames;
	/// <summary> Мембър отговарящ за всички телефонни номера в него.</summary>
	CListCtrl m_lscPersonPhoneNumbers;
	/// <summary>Мембър помагащ с валидацията на стойносите във входните тексови полета.</summary>
	TextDataValidator m_oTextValidator;
public:
	/// <summary>Функция при натискането на бутона 'Cancel' в диалоговия прозорец.</summary>
	afx_msg void OnBnClickedCancel();
	/// <summary>Функция при избирането на 'Edit' от контекстното меню която дава възможност за редакция на запис.</summary>
	afx_msg void OnContextMenuEdit();
	/// <summary>Функция при избирането на 'Delete' от контекстното меню която дава възможност за изтриване на запис.</summary>
	afx_msg void OnContextMenuDelete();
	/// <summary>Функция при избирането на 'Read data' от контекстното меню която дава възможност за изчитане на запис.</summary>
	afx_msg void OnContextMenuReadData();
	/// <summary>Функция при избирането на 'Insert' от контекстното меню която дава възможност за добавяне на нов запис.</summary>
	afx_msg void OnContextMenuInsert();
};

