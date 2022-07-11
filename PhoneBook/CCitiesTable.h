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
public:
	CCitiesTable();
	~CCitiesTable();

public:
	/// <summary>
	///  Функция която чете всики записи от таблицата "CITIES" и ги добавя в подаден като аргумент масив.
	/// </summary>
	/// <param name="oCitiesArray">Масив в който ще бъдат записани всички прочетени данни.</param>
	BOOL SelectAll(CCitiesArray& oCitiesArray);

	/// <summary>
	///  Функция която чете запис от таблицата "CITIES" чието ID отговаря на "lID" и го презаписва в "recCities" аргумента.
	/// </summary>
	/// <param name="lID">Уникален идентификатор чрез който ще се търси запис в базата.</param>
	/// <param name="recCities">Референция която ще присвои резултата от функцията</param>
	BOOL SelectWhereID(const long lID, CITIES& recCities);

	/// <summary>
	///  Функция която прави промяна на запис от таблицата "CITIES" чието ID отговаря на "lID" аргумента,
	///  и ще приложи промените от аргумента "recCities" в записа извлечен от базата.
	/// </summary>
	/// <param name="lID">Уникален идентификатор чрез който ще се търси запис в базата.</param>
	/// <param name="recCities">Референция която съдържа вече променените данни.</param>
	BOOL UpdateWhereID(const long lID, const CITIES& recCities);

	/// <summary>
	///  Функция която добавя запис подаден като аргумент към таблицата "CITIES".
	/// </summary>
	/// <param name="recCities">Референция която съдържа нов обект.</param>
	BOOL Insertt(const CITIES& recCities);

	/// <summary>
	///  Функция която изтрива запис от таблицата "CITIES" който отговавя на "lID" аргумента.
	/// </summary>
	/// <param name="lID">Уникален идентификатор чрез който ще се търси запис в базата.</param>
	BOOL DeleteWhereID(const long lID);

private:
	/// <summary>
	///  Функция която отваря връзка към базата.
	/// </summary>
	/// <param name="oDataSource">Обект служещ за отваряне на връзка.</param> 
	/// <param name="oSession">Обект служещ за отваряне на връзка.</param> 
	BOOL ConnectoToDb(CDataSource& oDataSource, CSession& oSession);

	/// <summary>
	///  Функция която създава рол-сет.
	/// </summary>
	CDBPropSet BuildCDBPropSet();

	/// <summary>
	///  Функция която създава рол-сет предназначен за модифициране на данни.
	/// </summary>
	CDBPropSet BuildUpdateDBPropSet();

	/// <summary>
	///  Функция която изпълнява дадена заявка към отворена връзка.
	/// </summary>
	/// <param name="hResult">Обект съдържащ текущото състояние на заявката</param> 
	/// <param name="oSession">Обект чрез който ще изпълни връзката към базата.</param> 
	/// <param name="oDataSource">Обект чрез който ще се изпълни връзката към базата.</param> 
	/// <param name="strQuery">Обект съдържащ текущата заявка.</param> 
	BOOL ExecuteNoneModifyQuery(HRESULT& hResult, CSession& oSession, CDataSource& oDataSource, const CString& strQuery);

	/// <summary>
	///  Функция която затваря връзката към базата.
	/// </summary>
	/// <param name="oSession">Обект чрез който ще се затвори връзката към базата.</param> 
	/// <param name="oDataSource">Обект чрез който ще се затвори връзката към базата.</param> 
	void CloseConnection(CDataSource& oDataSource, CSession& oSession);

	/// <summary>
	///  Функция която извежда съобщение при неуспешен опит за изпълнение на заявка, и затваря връзката.
	/// </summary>
 	/// <param name="hResult">Обект съдържащ съобщението на възникналата грешка.</param> 
	/// <param name="oSession">Обект чрез който ще се затвори връзката към базата.</param> 
	/// <param name="oDataSource">Обект чрез който ще се затвори връзката към базата.</param> 
	/// <param name="strQuery">Обект който съдържа текущата заявка.</param> 
	void ErrorExecutingQuery(const CString strQuery, const HRESULT& hResult, CDataSource oDataSource, CSession oSession);

	/// <summary>
	///  Функция която извежда съобщение при неуспешен опит за прочитане на резултат от заявка, и затваря връзката.
	/// </summary>
	/// <param name="hResult">Обект съдържащ съобщението на възникналата грешка.</param> 
	/// <param name="oSession">Обект чрез който ще се затвори връзката към базата.</param> 
	/// <param name="oDataSource">Обект чрез който ще се затвори връзката към базата.</param> 
	/// <param name="strQuery">Обект който съдържа текущата заявка.</param> 
	void ErrorOpeningRecord(const CString strQuery, const HRESULT& hResult, CDataSource oDataSource, CSession oSession);
};
