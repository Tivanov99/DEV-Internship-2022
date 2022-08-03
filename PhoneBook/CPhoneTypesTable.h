#pragma once
#include <atldbcli.h>
#include <iostream>
#include <afxcontrolbars.h>
#include <afxcontrolbars.h>
#include "Structures.h"
#include "CBaseTable.h"
#include "CTableAccessor.h"


#define NoneModifyColumnCode 0
#define ModifyColumnCode 1

class CPhoneTypesAccessor : public CTableAccessor<PHONE_TYPES>
{
protected:
	CPhoneTypesAccessor()
	{};
	~CPhoneTypesAccessor() {
	};

	BEGIN_ACCESSOR_MAP(CPhoneTypesAccessor, 2)
		BEGIN_ACCESSOR(NoneModifyColumnCode, true)
		COLUMN_ENTRY(1, m_recTableRecord.lID)
		END_ACCESSOR()

		BEGIN_ACCESSOR(ModifyColumnCode, true)
		COLUMN_ENTRY(2, m_recTableRecord.lUpdateCounter)
		COLUMN_ENTRY(3, m_recTableRecord.szPHONE_TYPE)
	
		END_ACCESSOR()
	END_ACCESSOR_MAP()
};

class CPhoneTypesTable:public CBaseTable< PHONE_TYPES, CPhoneTypesAccessor>
{
public:
	CPhoneTypesTable(CSession& oSession);
	~CPhoneTypesTable();
};

