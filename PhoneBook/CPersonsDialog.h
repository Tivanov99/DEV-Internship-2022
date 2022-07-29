#pragma once
#include "DialogWindowEnumeration.h"
#include "Structures.h"
#include "DataValidator.h"
class CPersonsDialog : public CDialog
{
	//Constants
	// ----------------
	DECLARE_DYNAMIC(CPersonsDialog)

public:
	CPersonsDialog(DialogWindowActions eOperations, PERSONS& recPerson, CWnd* pParent = nullptr);   // standard constructor
	virtual ~CPersonsDialog();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PERSONS_DIALOG };
#endif
	DECLARE_MESSAGE_MAP()

private:
	/// <summary>
	/// Попълва всички входни полета с данните идващи от 'm_recCity'.
	/// </summary>
	void FillingInputFields();

	/// <summary>
	/// Според командата в 'm_eOperation' задава име на прозореца и на бутона за потвърждаване на операцията.
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
	PERSONS& m_recPerson;

	/// <summary>
	/// Мембър съдържащ типът на текущата операция подаден като аргумент при извикването на диалога.
	/// </summary>
	DialogWindowActions m_eOperation;

	/// <summary>
	/// Мембър съдържащ методи за валидиране на сойностите в текстовите полета.
	/// </summary>
	DataValidator m_oDataValidator;
};

