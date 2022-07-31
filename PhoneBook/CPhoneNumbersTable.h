#include "Structures.h"
#include "CBaseTable.h"


#define NoneModifyColumnCode 0
#define ModifyColumnCode 1
class CPhoneNumberAccessor
{
protected:
	CPhoneNumberAccessor()
	{};
	~CPhoneNumberAccessor() {
	};
	PHONE_NUMBERS m_recPhoneNumber;

	BEGIN_ACCESSOR_MAP(CPhoneNumberAccessor, 2)
		BEGIN_ACCESSOR(NoneModifyColumnCode, true)
		COLUMN_ENTRY(1, m_recPhoneNumber.lID)
		END_ACCESSOR()

		BEGIN_ACCESSOR(ModifyColumnCode, true)
		COLUMN_ENTRY(2, m_recPhoneNumber.lUpdateCounter)
		COLUMN_ENTRY(3, m_recPhoneNumber.lPHONE_TYPE_ID)
		COLUMN_ENTRY(4, m_recPhoneNumber.szPHONE_NUMBER)
		END_ACCESSOR()
	END_ACCESSOR_MAP()
};

#pragma once
class CPhoneNumbersTable : private CCommand<CAccessor<CPhoneNumberAccessor>>, public CBaseTable<PHONE_NUMBERS>
{
	// Constants
	// ----------------
private:
	static const LPCSTR lpszSelectById;
	static const LPCSTR lpszSelectAll;
	static const LPCSTR lpszEmptySelect;

	// Constructor / Destructor
	// ----------------
public:
	CPhoneNumbersTable();
	~CPhoneNumbersTable();


	// Overrides
	// ----------------
public:
	bool SelectAll(CPhoneNumbersArray& oPhoneNumbersArray) override;

	bool SelectWhereID(const long lID, PHONE_NUMBERS& recPhoneNumber) override;

	bool UpdateWhereID(const long lID, const PHONE_NUMBERS& recPhoneNumber) override;

	bool Insert(const PHONE_NUMBERS& recPhoneNumber) override;

	bool DeleteWhereID(const long lID) override;

private:
	bool ExecuteQuery(const CString& strQuery, AccessorTypes eQueryAccessor) override;

	void CloseDbConnectionAndSession() override;
};

