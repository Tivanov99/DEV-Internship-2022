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
	/// <summary>��������� ��������, �� ������� ����� � � ��������� ������.</summary>
	const LPCSTR lpszInvalidRecordVersion = "Invalid version of current record! Please reload the record again.";
	/// <summary>��������� ����� ������, �� � ���������� ������ ��� ���������� �� �������� ������.</summary>
	const LPCSTR lpszErrorExecutingQuery = "Error executing query.Query : %s";
	/// <summary>��������� ����� ������, �� ������ � �������� ���� �� 0 � 1.</summary>
	const LPCSTR lpszErrorInvalidQueryAcessor =
		"Invalid query accessor! Use 0 for non-record-changing queries or 1 for record-changing queries";
	/// <summary>��������� ����� ������, �� � ���������� ������ ��� ���� �� ��������� ��� ������.</summary>
	const LPCSTR lpszUnableToConnectServer = "Unable to connect to SQL Server database. Error: %d";
	/// <summary>��������� ����� ������, �� � ���������� ������ ��� ���������� �� ��� ���� ���� ��� � ��� �������� �� ������.</summary>
	const LPCSTR lpszErrorOpeningRecord = "Error opening record.Query %s";
	/// <summary>��������� ����� ������, �� � ���������� ������ ��� ��������������� �� �����.</summary>
	const LPCSTR lpszErrorUpdatingRecord = "Error updating record with id: %d";
	/// <summary>��������� ����� ������, �� � ���������� ������ ��� ����������� �� �����.</summary>
	const LPCSTR lpszErrorDeletingRecord = "Delete failed.";
	/// <summary>��������� ����� ������, �� � ���������� ������ ��� ���������� �� �����.</summary>
	const LPCSTR lpszErrorInsertingRecord = "Insert failed.";
	/// <summary>��������� ����� ������, �� � ���������� ������ ��� ����������� �� �����. ���������� ������� �, �� � �������� ���� ��� ����� �� ��������.</summary>
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
	/// <summary>������� ����� ���������� 'rowset' ����� ��� ��������, ��������� ��� ������������� �� �����./// </summary>
	bool BuildRowSet();
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

	CDBPropSet m_RowSet;
};




template <typename Record_Type, class Table_AcessorType>
bool CBaseTable<Record_Type, Table_AcessorType>::BuildRowSet()
{
	CDBPropSet oUpdateDBPropSet(DBPROPSET_ROWSET);

	if (oUpdateDBPropSet.AddProperty(DBPROP_CANFETCHBACKWARDS, true) == 0)
	{
		AfxMessageBox(_T("Failed to add 'DBPROP_CANFETCHBACKWARDS' property to rowset!"));
		return false;
	}

	if (oUpdateDBPropSet.AddProperty(DBPROP_IRowsetScroll, true) == 0)
	{
		AfxMessageBox(_T("Failed to add 'DBPROP_IRowsetScroll' property to rowset!"));
		return false;
	}

	if (oUpdateDBPropSet.AddProperty(DBPROP_IRowsetChange, true) == 0)
	{
		AfxMessageBox(_T("Failed to add 'DBPROP_IRowsetChange' property to rowset!"));
		return false;
	}

	if (oUpdateDBPropSet.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE) == 0)
	{
		AfxMessageBox(_T("Failed to add 'DBPROP_UPDATABILITY' property to rowset!"));
		return false;
	}

	m_RowSet = oUpdateDBPropSet;
	return true;
}

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
		FAILED(CCommand<CAccessor<Table_AcessorType>>::Open(m_oSession, strQuery, &m_RowSet)) ?
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

	HRESULT hresult = CCommand<CAccessor<Table_AcessorType>>::Insert(ModifyColumnCode);

	if (FAILED(hresult))
	{
		if (hresult == DB_E_INTEGRITYVIOLATION)
		{
			CString strErrorMessage;
			strErrorMessage.Format(_T("Insert failed. Such a record already exists in the %s table."), m_strTableName);
			AfxMessageBox(strErrorMessage);
			CloseRowSet();
			return false;
		}
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