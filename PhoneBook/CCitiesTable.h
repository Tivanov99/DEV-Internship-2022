#pragma once
	
#include <atldbcli.h>
#include <iostream>
#include <afxcontrolbars.h>
#include <afxcontrolbars.h>
#include "Structures.h"
#include "CBaseTable.h"
#include "CBaseTable.cpp"
#include "CTableAccessor.h"


using namespace std;

//TODO: USE ENUMERATION

#define NoneModifyColumnCode 0
#define ModifyColumnCode 1

class CCityAccessor : public CTableAccessor<CITIES>
{
protected:
	CCityAccessor()
	{};
	~CCityAccessor() {
	};

	BEGIN_ACCESSOR_MAP(CCityAccessor, 2)
		BEGIN_ACCESSOR(NoneModifyColumnCode, true)
		COLUMN_ENTRY(1, m_recTableRecord.lID)
		END_ACCESSOR()

		BEGIN_ACCESSOR(ModifyColumnCode, true)
		COLUMN_ENTRY(2, m_recTableRecord.lUpdateCounter)
		COLUMN_ENTRY(3, m_recTableRecord.szCITY_NAME)
		COLUMN_ENTRY(4, m_recTableRecord.szAREA_NAME)
		COLUMN_ENTRY(5, m_recTableRecord.lPOSTAL_CODE)
		END_ACCESSOR()
	END_ACCESSOR_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CCitiesTable

/// <summary>Клас за работа с таблица CITIES</summary>
class CCitiesTable : public CBaseTable<CITIES, CCityAccessor>
{
	// Constructor / Destructor
	// ----------------
public:
	CCitiesTable(CSession& oSession);
	~CCitiesTable();
};
