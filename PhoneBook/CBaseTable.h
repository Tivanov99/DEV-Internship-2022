#pragma once
#include <atldbcli.h>
#include <iostream>
#include "Enumerations.h"
#include <afxcontrolbars.h>
#include "CSelfClearingTypedPtrArray.h"

template <typename Record_Type, class Table_AcessorType>
class CBaseTable : public CCommand<CAccessor<Table_AcessorType>>
{
	// Constants
	// ----------------
public:
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
	CBaseTable(CSession& oSession, TCHAR* pszTableName);
	~CBaseTable();


	// Methods
	// ----------------
public:
	/// <summary>
	///  Функция която създава рол-сет предназначен за модифициране на данни.
	/// </summary>
	CDBPropSet GetModifyDBPropSet() const;
	
	// Overrides
	// -------------
public:
	bool  SelectAll(CSelfClearingTypedPtrArray<Record_Type>& oArray);

	bool  SelectWhereID(const long lID, Record_Type& recTableRecord) ;

	bool  UpdateWhereID(const long lID, const Record_Type& recTableRecord) ;

	bool  Insert(const Record_Type& recTableRecord);

	bool  DeleteWhereID(const long lID) ;

public:
	
	bool virtual ExecuteQuery(const CString& strQuery, AccessorTypes eQueryAccessor);
	
	void virtual CloseRowSet();

	// Members
	// -------------
public:
	CDataSource m_oDataSource;
	CSession& m_oSession;

private:
	CString m_strTableName;
};

