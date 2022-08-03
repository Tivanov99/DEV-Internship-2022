#include "Structures.h"
#include "CBaseTable.h"
#include "CTableAccessor.h"

#define NoneModifyColumnCode 0
#define ModifyColumnCode 1
class CPhoneNumberAccessor : public CTableAccessor<PHONE_NUMBERS>
{
protected:
	CPhoneNumberAccessor()
	{};
	~CPhoneNumberAccessor() {
	};

	BEGIN_ACCESSOR_MAP(CPhoneNumberAccessor, 2)
		BEGIN_ACCESSOR(NoneModifyColumnCode, true)
		COLUMN_ENTRY(1, m_recTableRecord.lID)
		END_ACCESSOR()

		BEGIN_ACCESSOR(ModifyColumnCode, true)
		COLUMN_ENTRY(2, m_recTableRecord.lUpdateCounter)
		COLUMN_ENTRY(3, m_recTableRecord.lPHONE_TYPE_ID)
		COLUMN_ENTRY(4, m_recTableRecord.szPHONE_NUMBER)
		END_ACCESSOR()
	END_ACCESSOR_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// CPhoneNumbersTable
#pragma once
class CPhoneNumbersTable :  public CBaseTable<PHONE_NUMBERS, CPhoneNumberAccessor>
{
	// Constructor / Destructor
	// ----------------
public:
	CPhoneNumbersTable(CSession& oSession);
	~CPhoneNumbersTable();

	// Methods
	// ----------------
public:
	bool DeleteWherePersonID(long lID);
	bool SelectAllByPersonId(long lPersonID, CPhoneNumbersArray& oPhoneNumbersArray);
};

