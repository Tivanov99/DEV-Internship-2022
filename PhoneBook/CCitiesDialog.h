#pragma once
#include "afxdialogex.h"
#include "Structures.h"
#include "Enumerations.h"
#include "DataValidator.h"


// CCitiesDialog dialog

class CCitiesDialog : public CDialog
{
	//Constants
	// ----------------
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
	/// <summary>
	/// Попълва всички входни полета с данните идващи от 'm_recCity'.
	/// </summary>
	void FillingInputFields();

	/// <summary>
	/// Според командата в 'm_eOperations' задава име на прозореца и на бутона за потвърждаване на операцията.
	/// </summary>
	void SetDialogTitle();

	/// <summary>
	/// Взема въвдената стойност от полето за пощенски код.
	/// </summary>
	/// <returns>Връша въвдената стойност в полето за пощенски код.</returns>
	long GetPostalCodeFromInputFiled();

	/// <summary>
	/// Задава сойносите попълнени в полетата на записът който подлежи на обработка.
	/// </summary>
	void SetDataToRecord();
	// Overrides
	// ----------------
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	/// <summary>
	///Надстройва диалоговия прозорец при стартиране и попълва всички данни на подадения обект в полетата; 
	/// </summary>
	/// <returns></returns>
	virtual BOOL OnInitDialog();

	/// <summary>
	/// Извиква се при натиска не бутона 'Ок'.
	/// </summary>
	virtual void OnOK();

	// Members
	// ----------------
private:
	/// <summary>
	/// Референция към подаден запис при извикването на диалога.
	/// </summary>
	CITIES& m_recCity;

	/// <summary>
	/// Мембър отговарящ за входното поле съдържащо името на градът.
	/// </summary>
	CEdit m_edbCityName;

	/// <summary>
	/// Мембър отговарящ за входното поле съдържащо името на областта.
	/// </summary>
	CEdit m_edbCityAreaName;
	
	/// <summary>
	/// Мембър отговарящ за входното поле съдържащо пощенски код.
	/// </summary>
	CEdit m_edbCityPostalCode;

	/// <summary>
	/// Мембър съдържащ типът на текущата операция подаден като аргумент при извикването на диалога.
	/// </summary>
	ContextMenuOperations m_eOperations;


	/// <summary>
	/// Мембър съдържащ методи за валидиране на сойностите в текстовите полета.
	/// </summary>
	DataValidator m_oDataValidator;
private:
	CButton btn_Ok;
};

