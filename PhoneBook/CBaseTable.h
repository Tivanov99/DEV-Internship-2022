#pragma once
#include <atldbcli.h>
#include <iostream>
#include <afxcontrolbars.h>
#include "CSelfClearingTypedPtrArray.h"

template<class T>
class CBaseTable
{
public:
	CBaseTable();
	~CBaseTable();

private:
	friend class CCitiesTable;
	friend class CPersonsTable;

	// Methods
// -------------
private:
	const LPCSTR lpszInvalidRecordVersion = "Invalid version of current record! Please reload the record again.";
	const LPCSTR lpszErrorExecutingQuery = "Error executing query.Query : %s";
	const LPCSTR lpszErrorInvalidQueryAcessor =
		"Invalid query accessor! Use 0 for non-record-changing queries or 1 for record-changing queries";
	const LPCSTR lpszUnableToConnectServer = "Unable to connect to SQL Server database. Error: %d";
	const LPCSTR lpszUnableToOpenSession = "Unable to open session. Error: %d";
	const LPCSTR lpszErrorOpeningRecord = "Error opening record.Query %s";
	const LPCSTR lpszErrorUpdatingRecord = "Error updating record with id: %d";
	const LPCSTR lpszErrorDeletingRecord = "Delete failed.";
	const LPCSTR lpszErrorInsertingRecord = "Insert failed.";
public:
	bool virtual SelectAll(CSelfClearingTypedPtrArray<T>& oArray) = 0;

	bool virtual SelectWhereID(const long lID, T& rec) = 0;

	bool virtual UpdateWhereID(const long lID, const T& rec) = 0;

	bool virtual Insert(const T& rec) = 0;

	bool virtual DeleteWhereID(const long lID) = 0;

private:
	/// <summary>
	///  ������� ����� ������ ����� � ������ ��� ������.
	/// </summary>
	bool OpenDbConnectionAndSession();

	/// <summary>
	///  ������� ����� ������� ���-���.
	/// </summary>
	CDBPropSet GetDBPropSet() const;

	/// <summary>
	///  ������� ����� ������� ���-��� ������������ �� ������������ �� �����.
	/// </summary>
	CDBPropSet GetModifyDBPropSet() const;

	/// <summary>
	///  ������� ����� ������� ��������� ��� ��������� ���� �� ��������� �� �������� �� ������.
	/// </summary>
	/// <param name="strErrorMessage">����� ����� ������� �������� ���������� �� �������� ������.</param>
	/// <param name="strQuery">����� ����� ������� �������� ������.</param>
	void ShowErrorMessage(const LPCSTR strErrorMessage, const CString& strQuery);

	/// <summary>
	///  ������� ����� ��������� ������ ������ ��� �������� ������.
	/// </summary>
	/// <param name="strQuery">����� �������� �������� ������.</param> 
	/// <param name="nQueryAccessor">
		///����������� ����� ����� �������� ���� ��
		/// �� ����������� ������� ��� ��. 0 - �� ��������� / 1 ����������.
	/// </param>  
	bool virtual ExecuteQuery(const CString& strQuery, const int nQueryAccessor) = 0;

	/// <summary>
	///  ������� ����� ������� �������� ��� ������.
	/// </summary>
	void virtual  CloseDbConnectionAndSession() = 0;

	// Overrides
	// -------------

	// Members
	// -------------
	CDataSource m_oDataSource;
	CSession m_oSession;
};

