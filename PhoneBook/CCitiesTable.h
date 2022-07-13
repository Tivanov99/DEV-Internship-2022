#include <atldbcli.h>
#include <iostream>
#include <afxcontrolbars.h>
#include <afxcontrolbars.h>
#include "Structures.h"
#include "CSelfClearingTypedPtrArray.h"


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
	static const LPCSTR lpszSelectAll;   
	static const LPCSTR lpszEmptySelect;
	static const LPCSTR lpszUnableToConnectServer;
	static const LPCSTR lpszUnableToOpenSession ;
	static const LPCSTR lpszErrorExecutingQuery;
	static const LPCSTR lpszErrorInvalidQueryAcessor;
	static const LPCSTR lpszErrorOpeningRecord;
	static const LPCSTR lpszErrorUpdatingRecord;
	static const LPCSTR lpszErrorDeletingRecord;
	static const LPCSTR lpszErrorInsertingRecord;
	static const LPCSTR lpszInvalidRecordVersion;

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
	bool SelectAll(CSelfClearingTypedPtrArray<CITIES>& oCitiesArray);

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
	bool OpenDbConnectionAndSession();

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
	/// <param name="strQuery">Обект съдържащ текущата заявка.</param> 
	/// <param name="nQueryAccessor">
		///Целочислено число което определя дали ще
		/// се модифицират данните или не. 0 - не модофицра / 1 модифицира.
	/// </param>  
	bool ExecuteQuery(const CString& strQuery,const int nQueryAccessor);

	/// <summary>
	///  Функция която затваря връзката към базата.
	/// </summary>
	void CloseDbConnectionAndSession();

	/// <summary>
	///  Функция която извежда съобщение при неуспешен опит за прочитане на резултат от заявка.
	/// </summary>
	/// <param name="hResult">Обект съдържащ съобщението на възникналата грешка.</param> 
	/// <param name="strErrorMessage">Обект който съдържа подробно разяснение за текущата грешка.</param>  
	/// <param name="strQuery">Обект който съдържа текущата заявка.</param> 
	void ShowErrorMessage(const LPCSTR strErrorMessage, const CString& strQuery = NULL);

	// Overrides
	// -------------

	// Members
	// -------------
	CDataSource m_oDataSource;
	CSession m_oSession;
};
