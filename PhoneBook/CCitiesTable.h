#pragma once
	
#include <atldbcli.h>
#include <iostream>
#include <afxcontrolbars.h>
#include <afxcontrolbars.h>
#include "Structures.h"
#include "CBaseTable.h"


using namespace std;

//TODO: USE ENUMERATION
#define NoneModifyColumnCode 0
#define ModifyColumnCode 1
class CCityAccessor
{
protected:
	CCityAccessor()
	{};
	~CCityAccessor() {
	};
	CITIES m_recCITY;

	BEGIN_ACCESSOR_MAP(CCityAccessor, 2)
		BEGIN_ACCESSOR(NoneModifyColumnCode, true)
		COLUMN_ENTRY(1, m_recCITY.lID)
		END_ACCESSOR()

		BEGIN_ACCESSOR(ModifyColumnCode, true)
		COLUMN_ENTRY(2, m_recCITY.lUpdateCounter)
		COLUMN_ENTRY(3, m_recCITY.szCITY_NAME)
		COLUMN_ENTRY(4, m_recCITY.szAREA_NAME)
		COLUMN_ENTRY(5, m_recCITY.lPOSTAL_CODE)
		END_ACCESSOR()
	END_ACCESSOR_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CCitiesTable

/// <summary>Клас за работа с таблица CITIES</summary>
class CCitiesTable : private CCommand<CAccessor<CCityAccessor>>, public CBaseTable<CITIES>
{
	// Constants
	// ----------------
private:
	static const LPCSTR lpszSelectAllById;
	static const LPCSTR lpszSelectLastById;
	static const LPCSTR lpszSelectAll;   
	static const LPCSTR lpszEmptySelect;
	

	// Constructor / Destructor
	// ----------------
public:
	CCitiesTable();
	~CCitiesTable();
	
	// Methods
	// -------------
public:
	bool SelectAll(CSelfClearingTypedPtrArray<CITIES>& oCitiesArray) override;
	
	bool SelectWhereID(const long lID, CITIES& recCities) override;
	
	bool UpdateWhereID(const long lID, const CITIES& recCities) override;

	bool Insert(const CITIES& recCities) override;
	
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
	bool ExecuteQuery(const CString& strQuery,const int nQueryAccessor) override;

	/// <summary>
	///  Функция която затваря връзката към базата.
	/// </summary>
	void CloseDbConnectionAndSession() override;
};
