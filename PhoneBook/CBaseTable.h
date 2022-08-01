#pragma once
#include <atldbcli.h>
#include <iostream>
#include "Enumerations.h"
#include <afxcontrolbars.h>
#include "CSelfClearingTypedPtrArray.h"

template<class T>
class CBaseTable
{
	// Constants
	// ----------------
private:
	const LPCSTR lpszInvalidRecordVersion = "Invalid version of current record! Please reload the record again.";
	const LPCSTR lpszErrorExecutingQuery = "Error executing query.Query : %s";
	const LPCSTR lpszErrorInvalidQueryAcessor =
		"Invalid query accessor! Use 0 for non-record-changing queries or 1 for record-changing queries";
	const LPCSTR lpszUnableToConnectServer = "Unable to connect to SQL Server database. Error: %d";
	const LPCSTR lpszErrorOpeningRecord = "Error opening record.Query %s";
	const LPCSTR lpszErrorUpdatingRecord = "Error updating record with id: %d";
	const LPCSTR lpszErrorDeletingRecord = "Delete failed.";
	const LPCSTR lpszErrorInsertingRecord = "Insert failed.";

	// Constructor / Destructor
	// ----------------
public:
	CBaseTable(CSession& oSession);
	~CBaseTable();

private:
	friend class CCitiesTable;
	friend class CPersonsTable;
	friend class CPhoneNumbersTable;


	// Methods
	// ----------------
private:
	/// <summary>
	///  Функция която създава рол-сет предназначен за модифициране на данни.
	/// </summary>
	CDBPropSet GetModifyDBPropSet() const;
	
	// Overrides
	// -------------
public:
	bool virtual SelectAll(CSelfClearingTypedPtrArray<T>& oArray) = 0;

	bool virtual SelectWhereID(const long lID, T& rec) = 0;

	bool virtual UpdateWhereID(const long lID, const T& rec) = 0;

	bool virtual Insert(const T& rec) = 0;

	bool virtual DeleteWhereID(const long lID) = 0;

private:
	
	bool virtual ExecuteQuery(const CString& strQuery, AccessorTypes eQueryAccessor) = 0;
	
	void virtual  CloseDbConnectionAndSession() = 0;

	void virtual CloseRowSet() = 0;

private:
	// Members
	// -------------
	CDataSource m_oDataSource;
	CSession& m_oSession;
};

