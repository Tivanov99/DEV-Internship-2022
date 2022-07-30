#include "Structures.h"
#include "CBaseTable.h"


#pragma once
class CPhoneNumbersTable : public CBaseTable<PHONE_NUMBERS>
{

	// Constructor / Destructor
	// ----------------
public:
	CPhoneNumbersTable();
	~CPhoneNumbersTable();


	// Overrides
	// ----------------
public:
	bool SelectAll(CPhoneNumbersArray& oArray) override;

	bool SelectWhereID(const long lID, PHONE_NUMBERS& rec) override;

	bool UpdateWhereID(const long lID, const PHONE_NUMBERS& rec) override;

	bool Insert(const PHONE_NUMBERS& rec) override;

	bool DeleteWhereID(const long lID) override;

private:
	bool ExecuteQuery(const CString& strQuery, const int nQueryAccessor) override;

	void CloseDbConnectionAndSession() override;
};

