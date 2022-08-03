#pragma once
#include <atldbcli.h>
#include <iostream>
#include "Enumerations.h"
#include <afxcontrolbars.h>
#include "ErrorVisualizator.h"


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

	CDBPropSet GetModifyDBPropSet() const
	{
		CDBPropSet oUpdateDBPropSet(DBPROPSET_ROWSET);
		oUpdateDBPropSet.AddProperty(DBPROP_CANFETCHBACKWARDS, true);
		oUpdateDBPropSet.AddProperty(DBPROP_IRowsetScroll, true);
		oUpdateDBPropSet.AddProperty(DBPROP_IRowsetChange, true);
		oUpdateDBPropSet.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE);
		return oUpdateDBPropSet;
	};

	bool ExecuteQuery(const CString& strQuery, AccessorTypes eQueryAccessor)
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

	bool SelectAll(CSelfClearingTypedPtrArray<Record_Type>& oPtrArray)
	{
		CString strQuery;
		strQuery.Format(_T("SELECT * FROM %s"), m_strTableName);
		// ����������� ���������
		if (!ExecuteQuery(strQuery, AccessorTypes::NoneModifying))
			return false;

		//TODO: CHECK HERE
		HRESULT hResult = MoveFirst();
		if (FAILED(hResult))
		{
			ErrorMessageVisualizator::ShowErrorMessage(lpszErrorOpeningRecord, NULL);
			return false;
		}

		// ��������� ������ �����
		while (hResult != DB_S_ENDOFROWSET)
		{
			Record_Type* pCurrentRecord = new Record_Type;
			*pCurrentRecord = m_recTableRecord;
			oPtrArray.Add(pCurrentRecord);

			hResult = MoveNext();

			if (FAILED(hResult) && hResult != DB_S_ENDOFROWSET)
			{
				ErrorMessageVisualizator::ShowErrorMessage(lpszErrorOpeningRecord, NULL);
				return false;
			}
			// Logic with the result
		}

		return true;
	};


	bool SelectWhereID(const long lID, Record_Type& recTableRecord)
	{

		CString strQuery;
		strQuery.Format(_T("SELECT * FROM %s WHERE ID = %d"), m_strTableName, lID);

		if (!ExecuteQuery(strQuery, AccessorTypes::NoneModifying))
		{
			return false;
		}

		if (FAILED(MoveFirst()))
		{
			ErrorMessageVisualizator::ShowErrorMessage(lpszErrorOpeningRecord, NULL);
			return false;
		}
		recTableRecord = m_recTableRecord;

		return true;
	};


	bool UpdateWhereID(const long lID, const Record_Type& recTableRecord)
	{
		// ������������ ��������
		CString strQuery;
		strQuery.Format(_T("SELECT * FROM %s WHERE ID = %d"), m_strTableName, lID);

		// ����������� ���������
		if (!ExecuteQuery(strQuery, AccessorTypes::Modifying))
			return false;

		if (FAILED(MoveFirst()))
		{
			ErrorMessageVisualizator::ShowErrorMessage(lpszErrorOpeningRecord, strQuery);
			return false;
		}

		if (recTableRecord.lUpdateCounter != m_recTableRecord.lUpdateCounter)
		{
			ErrorMessageVisualizator::ShowErrorMessage(lpszInvalidRecordVersion, NULL);
			return false;
		}

		m_recTableRecord.lUpdateCounter++;
		m_recTableRecord = recTableRecord;

		if (FAILED(SetData(ModifyColumnCode)))
		{
			ErrorMessageVisualizator::ShowErrorMessage(lpszErrorUpdatingRecord, NULL);
			return false;
		}

		return true;
	};


	bool InsertRecord(const Record_Type& recTableRecord)
	{
		CString strQuery;
		strQuery.Format(_T("SELECT TOP 0 * FROM %s"), m_strTableName);

		if (!ExecuteQuery(strQuery, AccessorTypes::Modifying))
		{
			ErrorMessageVisualizator::ShowErrorMessage(lpszErrorExecutingQuery, NULL);
			return false;
		}

		m_recTableRecord = recTableRecord;

		if (FAILED(CCommand<CAccessor<Table_AcessorType>>::Insert(ModifyColumnCode)))
		{
			ErrorMessageVisualizator::ShowErrorMessage(lpszErrorInsertingRecord, NULL);
			return false;
		}

		return true;
	};

	bool DeleteWhereID(const long lID)
	{
		// ������������ ��������
		CString strQuery;
		strQuery.Format(_T("SELECT * FROM %s WHERE ID = %d"), m_strTableName, lID);

		// ����������� ���������
		if (!ExecuteQuery(strQuery, AccessorTypes::Modifying))
		{
			ErrorMessageVisualizator::ShowErrorMessage(lpszErrorExecutingQuery, strQuery);
			return false;
		}

		if (MoveFirst() != S_OK)
		{
			ErrorMessageVisualizator::ShowErrorMessage(lpszErrorOpeningRecord, strQuery);
			return false;
		}

		if (FAILED(Delete()))
		{
			ErrorMessageVisualizator::ShowErrorMessage(lpszErrorDeletingRecord, NULL);
			return false;
		}
		m_oSession.Commit();
		return true;
	};

	void CloseRowSet()
	{
		Close();
	}

	// Members
	// -------------
public:
	CDataSource m_oDataSource;
	CSession& m_oSession;

private:
	CString m_strTableName;
};

