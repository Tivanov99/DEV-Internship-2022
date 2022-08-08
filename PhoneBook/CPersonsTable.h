#pragma once

#include <atldbcli.h>
#include <iostream>
#include <afxcontrolbars.h>
#include "Structures.h"
#include "CSelfClearingTypedPtrArray.h"
#include "CBaseTable.h"
#include "CTableAccessor.h"


using namespace std;

//TODO: USE ENUMERATION
#define NoneModifyColumnCode 0
#define ModifyColumnCode 1

class CPersonAccessor : public CTableAccessor<PERSONS>
{
public:
	CPersonAccessor()
	{

	};
	~CPersonAccessor()
	{};

protected:
	BEGIN_ACCESSOR_MAP(CPersonAccessor, 2)
		BEGIN_ACCESSOR(NoneModifyColumnCode, true)
		COLUMN_ENTRY(1, m_recTableRecord.lID)
		END_ACCESSOR()

		BEGIN_ACCESSOR(ModifyColumnCode, true)
		COLUMN_ENTRY(2, m_recTableRecord.lUpdateCounter)
		COLUMN_ENTRY(3, m_recTableRecord.szFirstName)
		COLUMN_ENTRY(4, m_recTableRecord.szSECOND_NAME)
		COLUMN_ENTRY(5, m_recTableRecord.szLAST_NAME)
		COLUMN_ENTRY(6, m_recTableRecord.szUCN)
		COLUMN_ENTRY(7, m_recTableRecord.lCITY_ID)
		COLUMN_ENTRY(8, m_recTableRecord.szADDRESS)
		END_ACCESSOR()
	END_ACCESSOR_MAP()
};

class CPersonsTable : public CBaseTable<PERSONS, CPersonAccessor>
{
	// Constructor / Destructor
	// ----------------
public:
	CPersonsTable(CSession& oSession);
	~CPersonsTable();
};

