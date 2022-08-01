#pragma once

#include <atldbcli.h>
#include <iostream>
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
	~CPersonAccessor() {};
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
		COLUMN_ENTRY(6, m_recPERSON.szUCN)
		COLUMN_ENTRY(7, m_recPERSON.lCITY_ID)
		COLUMN_ENTRY(8, m_recPERSON.szADDRESS)
		END_ACCESSOR()
	END_ACCESSOR_MAP()
};

class CPersonsTable : private CCommand<CAccessor<CPersonAccessor>>, public CBaseTable<PERSONS, CPersonAccessor>
{
	// Constants
	// ----------------
private:
	static const LPCSTR lpszSelectAllById;
	static const LPCSTR lpszSelectAll;
	static const LPCSTR lpszEmptySelect;

	// Constructor / Destructor
	// ----------------
public:
	CPersonsTable(CSession& oSession);
	~CPersonsTable();
};

