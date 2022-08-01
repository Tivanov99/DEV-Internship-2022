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


/////////////////////////////////////////////////////////////////////////////
// CPhoneNumbersTable
#pragma once
class CPhoneNumbersTable : private CCommand<CAccessor<CPhoneNumberAccessor>>, public CBaseTable<PHONE_NUMBERS>
{
	// Constants
	// ----------------
private:
	static const LPCSTR lpszSelectById;
	static const LPCSTR lpszSelectAll;
	static const LPCSTR lpszEmptySelect;
	static const LPCSTR lpszSelectAllByPersonId;

	// Constructor / Destructor
	// ----------------
public:
	CPhoneNumbersTable(CSession& oSession);
	~CPhoneNumbersTable();

	// Methods
	// ----------------
public:
	/// <summary>
	/// Изчита всички записи от таблицата според където колоната 'lPERSON_ID' съдържа стойност равна на аргумента 'lID'.
	/// </summary>
	/// <param name="lID">Стойност според която ще се изчетат всички записи.</param>
	/// <param name="oPhoneNumbersArray">Референция към масив който ще бъде напълнен с всички прочетени записи</param>
	/// <returns>Върща 'true' или 'false' според това дали всичко е успешно</returns>
	bool SelectAllByPersonId(long lID, CPhoneNumbersArray& oPhoneNumbersArray);

	/// <summary>
	/// Изтрива всички записи от таблицата 
	/// </summary>
	/// <param name="lID"></param>
	/// <returns></returns>
	bool DeleteWherePersonID(const long lID);

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

	void CloseRowSet() override;
};

