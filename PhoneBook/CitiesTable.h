#pragma once

#include <atldbcli.h>
#include <iostream>
#include <afxcontrolbars.h>
#include <afxcontrolbars.h>
#include "Structures.h"
#include "BaseTable.h"
#include "TableAccessor.h"

using namespace std;

class CCityAccessor : public CTableAccessor<CITIES>
{
protected:
	CCityAccessor()
	{};
	~CCityAccessor() {
	};

	BEGIN_ACCESSOR_MAP(CCityAccessor, 2)
		BEGIN_ACCESSOR(AccessorTypes::NoneModifying, true)
		COLUMN_ENTRY(1, m_recTableRecord.lID)
		END_ACCESSOR()

		BEGIN_ACCESSOR(AccessorTypes::Modifying, true)
		COLUMN_ENTRY(2, m_recTableRecord.lUpdateCounter)
		COLUMN_ENTRY(3, m_recTableRecord.szCityName)
		COLUMN_ENTRY(4, m_recTableRecord.szAreaName)
		COLUMN_ENTRY(5, m_recTableRecord.lPostalCode)
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
