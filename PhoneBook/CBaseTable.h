#pragma once
#include <atldbcli.h>
#include <iostream>
#include "Enumerations.h"
#include <afxcontrolbars.h>
#include "ErrorVisualizator.h"
#include "SqlQueries.h"

#define NoneModifyColumnCode 0
#define ModifyColumnCode 1


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
	const LPCSTR lpszErrorForeignKeyDeletingRecord = "Delete failed.This entry can be used in any of the other entries.";

	// Constructor / Destructor
	// ----------------
public:
	CBaseTable(CSession& oSession, TCHAR* pszTableName)
		:m_oSession(oSession), m_strTableName(pszTableName)
	{
	};

	~CBaseTable()
	{};


	// Methods
	// ----------------
public:
	/// <summary>
	/// ������� ����� ���������� �������� ��� ����� ��� ��������, ��������� ��� ������������� �� �����.
	/// </summary>
	/// <returns>�����</returns>
	CDBPropSet GetModifyDBPropSet() const;
	/// <summary>������� ����� ��������� ������� � ������ �����.</summary>
	/// <param name="strQuery">�������� ��� ������.</param>
	/// <param name="eQueryAccessor">����� �� ������</param>
	bool ExecuteQuery(const CString& strQuery, AccessorTypes eQueryAccessor);
	/// <summary>������� ����� ������ ������ ������ �� ������ � �� ������� � ������ ������� ���� �������� 'oPtrArray'.</summary>
	/// <param name="oPtrArray">����� ������ �� �� ������� ������ ������ �� ������.</param>
	bool SelectAll(CSelfClearingTypedPtrArray<Record_Type>& oPtrArray);
	/// <summary>������� ����� ������ ����� �� ������ ����� ID �������� �� ��������� 'lID' � �� ���������� � 'recTableRecord' ���������.<summary>
	/// <param name="lID">�������� ������������� �� ����� �� �� ������ �����.</param>
	/// <param name="recTableRecord">���������� ��� ����� ������ �� �� ������ ��������� ����� �� ������.</param>
	bool SelectWhereID(const long lID, Record_Type& recTableRecord);
	/// <summary>������� ����� ����������� ����� �� ������ ����� ID �������� �� ��������� 'lID' � ������� �� 'recTableRecord' ���������.</summary>
	/// <param name="lID">�������� ������������� �� ����� �� �� ������ �����.</param>
	/// <param name="recTableRecord">���������� ��� ����� ����� ������� ������ ���������� �� ������ �� ������.</param>
	bool UpdateWhereID(const long lID, const Record_Type& recTableRecord);
	/// <summary>������� ����� ������ ����� � ������.</summary>
	/// <param name="recTableRecord">���������� ��� ����� ����� �� ���� ������� � ������.</param>
	bool InsertRecord(Record_Type& recTableRecord);
	/// <summary>������� ����� ���� ����� �� ������ ����� �������� � �������� 'ID' �������� �� 'lID'.</summary>
	/// <param name="lID">�������� ������������� �� ����� �� �� ������ �����.</param>
	bool DeleteWhereID(const long lID);
	/// <summary>������� ����� ������� �����/� ���� ������������� 'lID' � ������ �������� �� ��� ������ �� ������ ����� � �������� ���� �������� 'strSqlWhereClause'.</summary>
	/// <param name="lID">�������� ������������� �� ����� �� �� ������ �����.</param>
	/// <param name="strSqlWhereClause">������ �������� �� ��� ������ �� ������ ��������.</param>
	bool DeleteBySpecificColumnWhereID(const long lID, CString strSqlWhereClause);
	/// <summary>������� ����� ������ �����/� ������ ������ ����� ������ �� ��� ������ �� ������ ��������, � �� ������� � 'oPtrArray'.</summary>
	/// <param name="oPtrArray">����� ������ �� �������� ������ �������� �� ������ �����/�.</param>
	/// <param name="strSqlWhereClause">������ �������� �� ��� ������ �� ������ ��������.</param>
	bool SelectBySpecificColumnWhereID(CSelfClearingTypedPtrArray<Record_Type>& oPtrArray, CString strSqlWhereClause);
	/// <summary>������� ����� ����������� ����� �� ������� ��� ���������� ������ ������� ���� �������� 'strSqlWhereClause' �������� ���� �������� � ������ 'lID'.</summary>
	/// <param name="lID">�������� ������������� �� ����� �� �� ����������� ������������ �� �����.</param>
	/// <param name="recTableRecord">���������� ��� ����� ����� ������� ���� ������������� ����������.</param>
	/// <param name="strSqlWhereClause">������ �������� �� ��� ������ �� ������ ��������.</param>
	bool UpdateBySpecificColumnWhereID(const long lID, const Record_Type& recTableRecord, CString strSqlWhereClause);
	/// <summary>������� ����� ������� RowSet.</summary>
	void CloseRowSet();
	// Members
	// -------------
public:
	/// <summary>���� ������ ���� ����� �� �������� ��������������.</summary>
	CDataSource m_oDataSource;
	/// <summary>���� ������ ����� ������� ������� ����� �� �������� � ������������ ��� ������.</summary>
	CSession& m_oSession;
private:
	/// <summary>���� ������ �������� ����� �� �������� ������� � ����� �� �������� ��������.</summary>
	CString m_strTableName;
};



template <typename Record_Type, class Table_AcessorType>
CDBPropSet CBaseTable<Record_Type, Table_AcessorType>::GetModifyDBPropSet() const
{
	CDBPropSet oUpdateDBPropSet(DBPROPSET_ROWSET);

	if (oUpdateDBPropSet.AddProperty(DBPROP_CANFETCHBACKWARDS, true) == 0)
		return oUpdateDBPropSet;

	if(oUpdateDBPropSet.AddProperty(DBPROP_IRowsetScroll, true)==0)
		return oUpdateDBPropSet;

	if(oUpdateDBPropSet.AddProperty(DBPROP_IRowsetChange, true)==0)
		return oUpdateDBPropSet;

	if (oUpdateDBPropSet.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE)==0)
		return oUpdateDBPropSet;

	return oUpdateDBPropSet;
};


template <typename Record_Type, class Table_AcessorType>
bool CBaseTable<Record_Type, Table_AcessorType>::ExecuteQuery(const CString& strQuery, AccessorTypes eQueryAccessor)
{
	bool bResult = false;
	switch (eQueryAccessor)
	{
	case AccessorTypes::NoneModifying:
		FAILED(CCommand<CAccessor<Table_AcessorType>>::Open(m_oSession, strQuery)) ?
			ErrorMessageVisualizator::ShowErrorMessage(lpszErrorExecutingQuery, strQuery) :
			bResult = true;
		break;

	case AccessorTypes::Modifying:
		FAILED(CCommand<CAccessor<Table_AcessorType>>::Open(m_oSession, strQuery, &GetModifyDBPropSet())) ?
			ErrorMessageVisualizator::ShowErrorMessage(lpszErrorExecutingQuery, strQuery) :
			bResult = true;
		break;

	default:
		ErrorMessageVisualizator::ShowErrorMessage(lpszErrorInvalidQueryAcessor, strQuery);
		break;
	}
	return bResult;
}


template <typename Record_Type, class Table_AcessorType>
bool CBaseTable<Record_Type, Table_AcessorType>::SelectAll(CSelfClearingTypedPtrArray<Record_Type>& oPtrArray)
{
	CString strQuery;
	strQuery.Format(SqlQueries::SelectAll, m_strTableName);

	if (!ExecuteQuery(strQuery, AccessorTypes::NoneModifying))
	{
		CloseRowSet();
		return false;
	}

	HRESULT hResult = MoveFirst();
	if (FAILED(hResult))
	{
		ErrorMessageVisualizator::ShowErrorMessage(lpszErrorOpeningRecord, NULL);
		CloseRowSet();
		return false;
	}

	while (hResult == S_OK)
	{
		Record_Type* pCurrentRecord = new Record_Type;
		*pCurrentRecord = m_recTableRecord;
		oPtrArray.Add(pCurrentRecord);

		hResult = MoveNext();

		if (FAILED(hResult) && hResult != DB_S_ENDOFROWSET)
		{
			ErrorMessageVisualizator::ShowErrorMessage(lpszErrorOpeningRecord, NULL);
			CloseRowSet();

			return false;
		}
	}
	CloseRowSet();
	return true;
};

template <typename Record_Type, class Table_AcessorType>
bool CBaseTable<Record_Type, Table_AcessorType>::SelectWhereID(const long lID, Record_Type& recTableRecord)
{
	CString strQuery;
	strQuery.Format(SqlQueries::SelectWhereID, m_strTableName, lID);

	if (!ExecuteQuery(strQuery, AccessorTypes::NoneModifying))
	{
		CloseRowSet();
		ErrorMessageVisualizator::ShowErrorMessage(lpszErrorExecutingQuery, strQuery);
		return false;
	}

	if (FAILED(MoveFirst()))
	{
		ErrorMessageVisualizator::ShowErrorMessage(lpszErrorOpeningRecord, NULL);
		CloseRowSet();
		return false;
	}
	recTableRecord = m_recTableRecord;
	CloseRowSet();
	return true;
};

template <typename Record_Type, class Table_AcessorType>
bool CBaseTable<Record_Type, Table_AcessorType>::UpdateWhereID(const long lID, const Record_Type& recTableRecord)
{
	// ������������ ��������
	CString strQuery;
	strQuery.Format(SqlQueries::SelectWhereID, m_strTableName, lID);

	// ����������� ���������
	if (!ExecuteQuery(strQuery, AccessorTypes::Modifying))
	{
		CloseRowSet();
		return false;
	}

	if (FAILED(MoveFirst()))
	{
		ErrorMessageVisualizator::ShowErrorMessage(lpszErrorOpeningRecord, strQuery);
		CloseRowSet();
		return false;
	}

	if (recTableRecord.lUpdateCounter != m_recTableRecord.lUpdateCounter)
	{
		ErrorMessageVisualizator::ShowErrorMessage(lpszInvalidRecordVersion, NULL);
		CloseRowSet();
		return false;
	}

	m_recTableRecord.lUpdateCounter++;
	m_recTableRecord = recTableRecord;

	if (FAILED(SetData(ModifyColumnCode)))
	{
		ErrorMessageVisualizator::ShowErrorMessage(lpszErrorUpdatingRecord, NULL);
		CloseRowSet();
		return false;
	}
	CloseRowSet();
	return true;
};

template <typename Record_Type, class Table_AcessorType>
bool CBaseTable<Record_Type, Table_AcessorType>::InsertRecord(Record_Type& recTableRecord)
{
	CString strQuery;
	strQuery.Format(SqlQueries::EmptySelect, m_strTableName);

	if (!ExecuteQuery(strQuery, AccessorTypes::Modifying))
	{
		ErrorMessageVisualizator::ShowErrorMessage(lpszErrorExecutingQuery, NULL);
		CloseRowSet();
		return false;
	}

	m_recTableRecord = recTableRecord;

	if (FAILED(CCommand<CAccessor<Table_AcessorType>>::Insert(ModifyColumnCode)))
	{
		ErrorMessageVisualizator::ShowErrorMessage(lpszErrorInsertingRecord, NULL);
		CloseRowSet();
		return false;
	}

	if (MoveLast() != S_OK)
		return false;

	recTableRecord = m_recTableRecord;

	CloseRowSet();
	return true;
};

template <typename Record_Type, class Table_AcessorType>
bool CBaseTable<Record_Type, Table_AcessorType>::DeleteWhereID(const long lID)
{
	// ������������ ��������
	CString strQuery;
	strQuery.Format(SqlQueries::SelectWhereID, m_strTableName, lID);

	// ����������� ���������
	if (!ExecuteQuery(strQuery, AccessorTypes::Modifying))
	{
		ErrorMessageVisualizator::ShowErrorMessage(lpszErrorExecutingQuery, strQuery);
		CloseRowSet();
		return false;
	}

	if (MoveFirst() != S_OK)
	{
		ErrorMessageVisualizator::ShowErrorMessage(lpszErrorOpeningRecord, strQuery);
		CloseRowSet();
		return false;
	}

	if (FAILED(Delete()))
	{
		ErrorMessageVisualizator::ShowErrorMessage(lpszErrorForeignKeyDeletingRecord, NULL);
		CloseRowSet();
		return false;
	}
	CloseRowSet();
	return true;
};

template <typename Record_Type, class Table_AcessorType>
bool CBaseTable<Record_Type, Table_AcessorType>::DeleteBySpecificColumnWhereID(const long lID, CString strSqlWhereClause)
{
	// ������������ ��������
	CString strQuery;
	strQuery.Format(SqlQueries::SelectAll, m_strTableName);
	strQuery.Append(strSqlWhereClause);

	// ����������� ���������
	if (!ExecuteQuery(strQuery, AccessorTypes::Modifying))
	{
		ErrorMessageVisualizator::ShowErrorMessage(lpszErrorExecutingQuery, strQuery);
		CloseRowSet();
		return false;
	}
	if (MoveFirst() != S_OK)
	{
		ErrorMessageVisualizator::ShowErrorMessage(lpszErrorOpeningRecord, strQuery);
		CloseRowSet();
		return false;
	}

	if (FAILED(Delete()))
	{
		ErrorMessageVisualizator::ShowErrorMessage(lpszErrorDeletingRecord, NULL);
		CloseRowSet();
		return false;
	}
	CloseRowSet();
	return true;
};

template <typename Record_Type, class Table_AcessorType>
bool CBaseTable<Record_Type, Table_AcessorType>::SelectBySpecificColumnWhereID(CSelfClearingTypedPtrArray<Record_Type>& oPtrArray, CString strSqlWhereClause)
{
	CString strQuery;
	strQuery.Format(SqlQueries::SelectAll, m_strTableName);
	strQuery.Append(strSqlWhereClause);

	if (!ExecuteQuery(strQuery, AccessorTypes::NoneModifying))
	{
		CloseRowSet();
		ErrorMessageVisualizator::ShowErrorMessage(lpszErrorExecutingQuery, strQuery);
		return false;
	}

	HRESULT hResult = MoveFirst();
	if (FAILED(hResult))
	{
		ErrorMessageVisualizator::ShowErrorMessage(lpszErrorOpeningRecord, NULL);
		CloseRowSet();
		return false;
	}

	while (hResult == S_OK)
	{
		Record_Type* pCurrentRecord = new Record_Type;
		*pCurrentRecord = m_recTableRecord;
		oPtrArray.Add(pCurrentRecord);

		hResult = MoveNext();

		if (FAILED(hResult) && hResult != DB_S_ENDOFROWSET)
		{
			ErrorMessageVisualizator::ShowErrorMessage(lpszErrorOpeningRecord, NULL);
			CloseRowSet();

			return false;
		}
		// Logic with the result
	}
	CloseRowSet();
	return true;
};


template <typename Record_Type, class Table_AcessorType>
bool CBaseTable<Record_Type, Table_AcessorType>::UpdateBySpecificColumnWhereID(const long lID, const Record_Type& recTableRecord, CString strSqlWhereClause)
{
	// ������������ ��������
	CString strQuery;
	strQuery.Format(SqlQueries::SelectWhereID, m_strTableName, lID);
	strQuery.Append(strSqlWhereClause);

	// ����������� ���������
	if (!ExecuteQuery(strQuery, AccessorTypes::Modifying))
	{
		CloseRowSet();
		return false;
	}

	if (FAILED(MoveFirst()))
	{
		ErrorMessageVisualizator::ShowErrorMessage(lpszErrorOpeningRecord, strQuery);
		CloseRowSet();

		return false;
	}

	if (recTableRecord.lUpdateCounter != m_recTableRecord.lUpdateCounter)
	{
		ErrorMessageVisualizator::ShowErrorMessage(lpszInvalidRecordVersion, NULL);
		CloseRowSet();

		return false;
	}

	m_recTableRecord.lUpdateCounter++;
	m_recTableRecord = recTableRecord;

	if (FAILED(SetData(ModifyColumnCode)))
	{
		ErrorMessageVisualizator::ShowErrorMessage(lpszErrorUpdatingRecord, NULL);
		CloseRowSet();

		return false;
	}
	CloseRowSet();

	return true;
};


template <typename Record_Type, class Table_AcessorType>
void CBaseTable<Record_Type, Table_AcessorType>::CloseRowSet()
{
	Close();
}