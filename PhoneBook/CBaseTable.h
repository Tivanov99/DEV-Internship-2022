#pragma once
#include <atldbcli.h>
#include <iostream>
#include <afxcontrolbars.h>
#include "CSelfClearingTypedPtrArray.h"

template<class T>
class CBaseTable
{
	// Constants
	// ----------------
private:
	const LPCSTR lpszInvalidRecordVersion = "Invalid version of current record! Please reload the record again.";
	const LPCSTR lpszErrorExecutingQuery = "Error executing query.Query : %s";
	const LPCSTR lpszErrorInvalidQueryAcessor =
		"Invalid query accessor! Use 0 for non-record-changing queries or 1 for record-changing queries";
	const LPCSTR lpszUnableToConnectServer = "Unable to connect to SQL Server database. Error: %d";
	const LPCSTR lpszUnableToOpenSession = "Unable to open session. Error: %d";
	const LPCSTR lpszErrorOpeningRecord = "Error opening record.Query %s";
	const LPCSTR lpszErrorUpdatingRecord = "Error updating record with id: %d";
	const LPCSTR lpszErrorDeletingRecord = "Delete failed.";
	const LPCSTR lpszErrorInsertingRecord = "Insert failed.";

	// Constructor / Destructor
	// ----------------
public:
	CBaseTable();
	~CBaseTable();

private:
	friend class CCitiesTable;
	friend class CPersonsTable;
	friend class CPhoneNumbersTable;


	// Methods
	// ----------------
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
	///  Функция която извежда съобщение при неуспешен опит за прочитане на резултат от заявка.
	/// </summary>
	/// <param name="strErrorMessage">Обект който съдържа подробно разяснение за текущата грешка.</param>
	/// <param name="strQuery">Обект който съдържа текущата заявка.</param>
	void ShowErrorMessage(const LPCSTR strErrorMessage, const CString& strQuery);

	
	// Overrides
	// -------------
public:
	/// <summary>
	///  Функция която чете всики записи от таблица която е подадена като тип при наследяване
	///  на класът и ги добавя в подаден като аргумент масив.
	/// </summary>
	/// <param name="oArray">Масив в който ще бъдат записани всички прочетени данни.</param>
	bool virtual SelectAll(CSelfClearingTypedPtrArray<T>& oArray) = 0;

	/// <summary>
	///  Функция която чете запис от таблицата която е подадена като тип при наследяване
	///  на класът чието ID отговаря на "lID" и го презаписва в "rec" аргумента.
	/// </summary>
	/// <param name="lID">Уникален идентификатор чрез който ще се търси запис в базата.</param>
	/// <param name="rec">Референция която ще присвои резултата от функцията</param>
	bool virtual SelectWhereID(const long lID, T& rec) = 0;

	/// <summary>
	///  Функция която прави промяна на запис от таблицата  която е подадена като тип при наследяване
	///  на класът чието ID отговаря на "lID" аргумента,
	///  и ще приложи промените от аргумента "rec" в записа извлечен от базата.
	/// </summary>
	/// <param name="lID">Уникален идентификатор чрез който ще се търси запис в базата.</param>
	/// <param name="rec">Референция която съдържа вече променените данни.</param>
	bool virtual UpdateWhereID(const long lID, const T& rec) = 0;

	/// <summary>
	///  Функция която добавя запис подаден като аргумент към таблицата която е подадена като тип при наследяване
	///  на класът.
	/// </summary>
	/// <param name="rec">Референция която съдържа новия обект.</param>
	bool virtual Insert(const T& rec) = 0;

	/// <summary>
	///  Функция която изтрива запис от таблицата която е подадена като тип при наследяване
	///  на класът който отговавя на "lID" аргумента.
	/// </summary>
	/// <param name="lID">Уникален идентификатор чрез който ще се търси запис в базата.</param>
	bool virtual DeleteWhereID(const long lID) = 0;

private:
	/// <summary>
	///  Функция която изпълнява дадена заявка към отворена връзка.
	/// </summary>
	/// <param name="strQuery">Обект съдържащ текущата заявка.</param> 
	/// <param name="nQueryAccessor">
		///Целочислено число което определя дали ще
		/// се модифицират данните или не. 0 - не модофицра / 1 модифицира.
	/// </param>  
	bool virtual ExecuteQuery(const CString& strQuery, const int nQueryAccessor) = 0;

	/// <summary>
	///  Функция която затваря връзката към базата.
	/// </summary>
	void virtual  CloseDbConnectionAndSession() = 0;

private:
	// Members
	// -------------
	CDataSource m_oDataSource;
	CSession m_oSession;
};

