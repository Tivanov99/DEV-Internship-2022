#pragma once
#include "afxdialogex.h"
#include "Structures.h"


// CCitiesDialog dialog

class CCitiesDialog : public CDialog
{
	//Constants
	// ----------------
	int nMaxCityNameLenght = 32;
	int nMinCityNameLenght = 4;

	int nMaxCityAreaNameLenght = 32;
	int nMinCityAreaNameLenght = 4;

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
	void SetDialogWindowAndOkButtonText();

	/// <summary>
	/// Валидира текстови данни идващи от променлива на входно поле подадена като аргумент, и при възникване на грешка конструира и връща поянително съобщение.
	/// </summary>
	/// <param name="oEdit">Референция на променлива презентираща входно поле.</param>
	/// <param name="nMinLenght">Константна минимална дължина на текстовото поле.</param>
	/// <param name="nMaxLenght">Константна максимална дължина на текстовото поле.</param>
	/// <returns>Съобщение съдържащо допуснатите грешки, ако има такива.</returns>
	CString ValidateTextData(const CEdit& oEdit, const int nMinLenght, const int nMaxLenght);

	/// <summary>
	/// Валидира 'пощенски код' при обработка на запис.
	/// </summary>
	/// <returns>Въща 'true' или 'false' според това дали всико е валидно.</returns>
	bool ValidatePostalCode();
	bool CheckForNotAllowedChars(const CString& strValue);
	long GetPostalCodeFromInputFiled();
	void SetDataToRecord();
	// Overrides
	// ----------------
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
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
	CEdit StrCitiesName;

	/// <summary>
	/// Мембър отговарящ за входното поле съдържащо името на областта.
	/// </summary>
	CEdit StrAreaName;
	
	/// <summary>
	/// Мембър отговарящ за входното поле съдържащо пощенски код.
	/// </summary>
	CEdit StrPostalCode;

	/// <summary>
	/// Мембър съдържащ типът на текущата операция подаден като аргумент при извикването на диалога.
	/// </summary>
	ContextMenuOperations m_eOperations;
public:
	CButton btn_Ok;
};

