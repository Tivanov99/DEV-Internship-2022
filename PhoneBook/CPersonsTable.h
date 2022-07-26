#pragma once

#include <atldbcli.h>
#include <iostream>
#include <afxcontrolbars.h>
#include <afxcontrolbars.h>
#include "Structures.h"
#include "CSelfClearingTypedPtrArray.h"
#include "CBaseTable.h"


using namespace std;

//TODO: USE ENUMERATION
#define NoneModifyColumnCode 0
#define ModifyColumnCode 1

class CPersonAccessor
{
protected:
	CPersonAccessor()
	{
	};
	~CPersonAccessor() {

	};
	PERSONS m_recPERSON;

	BEGIN_ACCESSOR_MAP(CPersonAccessor, 2)
		BEGIN_ACCESSOR(NoneModifyColumnCode, true)
		COLUMN_ENTRY(1, m_recPERSON.lID)
		END_ACCESSOR()

		BEGIN_ACCESSOR(ModifyColumnCode, true)
		COLUMN_ENTRY(2, m_recPERSON.lUpdateCounter)
		COLUMN_ENTRY(3, m_recPERSON.szFIRST_NAME)
		COLUMN_ENTRY(4, m_recPERSON.szSECOND_NAME)
		COLUMN_ENTRY(5, m_recPERSON.szLAST_NAME)
		END_ACCESSOR(6, m_recPERSON.szADDRESS)
	END_ACCESSOR_MAP()
};
class CPersonsTable : private CCommand<CAccessor<CPersonAccessor>>, public CBaseTable<PERSONS>
{
	// Constants
	// ----------------
private:
	static const LPCSTR lpszSelectAllById;
	static const LPCSTR lpszSelectAll;
	static const LPCSTR lpszEmptySelect;

protected:
	CPersonsTable();
	~CPersonsTable();
	
public:
	/// <summary>
	///  Функция която чете всики записи от таблицата "PERSONS" и ги добавя в подаден като аргумент масив.
	/// </summary>
	/// <param name="oPersonsArray">Масив в който ще бъдат записани всички прочетени данни.</param>
	bool SelectAll(CSelfClearingTypedPtrArray<PERSONS>& oArray) override;

	/// <summary>
	///  Функция която чете запис от таблицата "PERSONS" чието ID отговаря на "lID" и го презаписва в "recPersons" аргумента.
	/// </summary>
	/// <param name="lID">Уникален идентификатор чрез който ще се търси запис в базата.</param>
	/// <param name="recPersons">Референция която ще присвои резултата от функцията</param>
	bool SelectWhereID(const long lID, PERSONS& recPersons) override;

	/// <summary>
	///  Функция която прави промяна на запис от таблицата "PERSONS" чието ID отговаря на "lID" аргумента,
	///  и ще приложи промените от аргумента "recPersons" в записа извлечен от базата.
	/// </summary>
	/// <param name="lID">Уникален идентификатор чрез който ще се търси запис в базата.</param>
	/// <param name="recPersons">Референция която съдържа вече променените данни.</param>
	bool UpdateWhereID(const long lID, const PERSONS& recPersons) override;

	/// <summary>
	///  Функция която добавя запис подаден като аргумент към таблицата "PERSONS".
	/// </summary>
	/// <param name="recPersons">Референция която съдържа нов обект.</param>
	bool Insert(const PERSONS& recPersons) override;

	/// <summary>
	///  Функция която изтрива запис от таблицата "PERSONS" който отговавя на "lID" аргумента.
	/// </summary>
	/// <param name="lID">Уникален идентификатор чрез който ще се търси запис в базата.</param>
	bool DeleteWhereID(const long lID) override;

private:
	/// <summary>
	///  Функция която изпълнява дадена заявка към отворена връзка.
	/// </summary>
	/// <param name="strQuery">Обект съдържащ текущата заявка.</param> 
	/// <param name="nQueryAccessor">
		///Целочислено число което определя дали ще
		/// се модифицират данните или не. 0 - не модофицра / 1 модифицира.
	/// </param>  
	bool ExecuteQuery(const CString& strQuery, const int nQueryAccessor) override;

	/// <summary>
	///  Функция която затваря връзката към базата.
	/// </summary>
	void CloseDbConnectionAndSession() override;
};

