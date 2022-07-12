#include <atldbcli.h>
#include <iostream>
#include <afxcontrolbars.h>
#include <afxcontrolbars.h>
#include "Structures.h"

using namespace std;

#define NoneModifyColumnCode 0
#define ModifyColumnCode 1
class CCityAccessor
{
protected:
	CCityAccessor() {

	};
	~CCityAccessor() {

	};
	CITIES m_recCITY;

	BEGIN_ACCESSOR_MAP(CCityAccessor, 2)
		BEGIN_ACCESSOR(NoneModifyColumnCode, true)
		COLUMN_ENTRY(1, m_recCITY.lID)
		END_ACCESSOR()

		BEGIN_ACCESSOR(ModifyColumnCode, true)
		COLUMN_ENTRY(2, m_recCITY.lUPDATE_COUNTER)
		COLUMN_ENTRY(3, m_recCITY.szCITY_NAME)
		COLUMN_ENTRY(4, m_recCITY.szAREA_NAME)
		COLUMN_ENTRY(5, m_recCITY.lPOSTAL_CODE)
		END_ACCESSOR()
	END_ACCESSOR_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CCitiesTable

/// <summary>Клас за работа с таблица CITIES</summary>
class CCitiesTable : private CCommand<CAccessor<CCityAccessor>>
{
private:
	static const LPCSTR lpszSelectAllById;
	const CString strSelectAll = _T("SELECT * FROM CITIES");
	const CString strEmptySelect = _T("SELECT TOP 0 * FROM CITIES");
	const CString strUnableToConnectServer = _T("Unable to connect to SQL Server database. Error: %d");
	const CString strUnableToOpenSession = _T("Unable to open session. Error: %d");
	const CString strErrorExecutingQuery = _T("Error executing query.Error:% d.Query : % s");
	const CString strErrorOpeningRecord = _T("Error opening record.Error:% d");
	const CString strErrorUpdatingRecord = _T("Error updating record.Error:% d.Query : % s");
	const CString strErrorDeletingRecord = _T("Delete failed: 0x%X\n");
	const CString strErrorInsertingRecord = _T("Insert failed: 0x%X\n");

public:
	CCitiesTable();
	~CCitiesTable();
	
	// Methods
	// -------------
public:
	/// <summary>
	///  Функция която чете всики записи от таблицата "CITIES" и ги добавя в подаден като аргумент масив.
	/// </summary>
	/// <param name="oCitiesArray">Масив в който ще бъдат записани всички прочетени данни.</param>
	bool SelectAll(CCitiesArray& oCitiesArray);

	/// <summary>
	///  Функция която чете запис от таблицата "CITIES" чието ID отговаря на "lID" и го презаписва в "recCities" аргумента.
	/// </summary>
	/// <param name="lID">Уникален идентификатор чрез който ще се търси запис в базата.</param>
	/// <param name="recCities">Референция която ще присвои резултата от функцията</param>
	bool SelectWhereID(const long lID, CITIES& recCities);

	/// <summary>
	///  Функция която прави промяна на запис от таблицата "CITIES" чието ID отговаря на "lID" аргумента,
	///  и ще приложи промените от аргумента "recCities" в записа извлечен от базата.
	/// </summary>
	/// <param name="lID">Уникален идентификатор чрез който ще се търси запис в базата.</param>
	/// <param name="recCities">Референция която съдържа вече променените данни.</param>
	bool UpdateWhereID(const long lID, const CITIES& recCities);

	/// <summary>
	///  Функция която добавя запис подаден като аргумент към таблицата "CITIES".
	/// </summary>
	/// <param name="recCities">Референция която съдържа нов обект.</param>
	bool Insert(const CITIES& recCities);

	/// <summary>
	///  Функция която изтрива запис от таблицата "CITIES" който отговавя на "lID" аргумента.
	/// </summary>
	/// <param name="lID">Уникален идентификатор чрез който ще се търси запис в базата.</param>
	bool DeleteWhereID(const long lID);

private:
	/// <summary>
	///  Функция която отваря сесия и връзка към базата.
	/// </summary>
	/// <param name="oDataSource">Обект служещ за отваряне на връзка.</param> 
	/// <param name="oSession">Обект служещ за отваряне на връзка.</param> 
	bool OpenSessionAndConnectionToDb(CDataSource& oDataSource, CSession& oSession);

	/// <summary>
	///  Функция която създава рол-сет.
	/// </summary>
	CDBPropSet GetDBPropSet() const;

	/// <summary>
	///  Функция която създава рол-сет предназначен за модифициране на данни.
	/// </summary>
	CDBPropSet GetModifyDBPropSet() const;

	/// <summary>
	///  Функция която изпълнява дадена заявка към отворена връзка.
	/// </summary>
	/// <param name="hResult">Обект съдържащ текущото състояние на заявката</param> 
	/// <param name="oSession">Обект чрез който ще изпълни връзката към базата.</param> 
	/// <param name="strQuery">Обект съдържащ текущата заявка.</param> 
	bool ExecuteNoneModifyQuery(HRESULT& hResult, CSession& oSession, const CString& strQuery);

	/// <summary>
	///  Функция която изпълнява дадена заявка към отворена връзка.
	/// </summary>
	/// <param name="hResult">Обект съдържащ текущото състояние на заявката</param> 
	/// <param name="oSession">Обект чрез който ще изпълни връзката към базата.</param> 
	/// <param name="strQuery">Обект съдържащ текущата заявка.</param> 
	bool ExecuteModifyQuery(HRESULT& hResult, CSession& oSession, const CString& strQuery, CDBPropSet oPropSet);

	/// <summary>
	///  Функция която затваря връзката към базата.
	/// </summary>
	/// <param name="oSession">Обект чрез който ще се затвори връзката към базата.</param> 
	/// <param name="oDataSource">Обект чрез който ще се затвори връзката към базата.</param> 
	void CloseSessionAndConnection(CDataSource& oDataSource, CSession& oSession);

	/// <summary>
	///  Функция която извежда съобщение при неуспешен опит за прочитане на резултат от заявка.
	/// </summary>
	/// <param name="hResult">Обект съдържащ съобщението на възникналата грешка.</param> 
	/// <param name="strErrorMessage">Обект който съдържа подробно разяснение за текущата грешка.</param>  
	/// <param name="strQuery">Обект който съдържа текущата заявка.</param> 
	void ShowErrorMessage(const CString& strErrorMessage, const CString& strQuery = NULL);

	// Overrides
	// -------------

	// Members
	// -------------

};
