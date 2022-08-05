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
		strQuery.Format(SqlQueries::SelectAll, m_strTableName);

		// Изпълняваме командата
		if (!ExecuteQuery(strQuery, AccessorTypes::NoneModifying))
		{
			CloseRowSet();
			return false;

		}

		//TODO: CHECK HERE
		HRESULT hResult = MoveFirst();
		if (FAILED(hResult))
		{
			ErrorMessageVisualizator::ShowErrorMessage(lpszErrorOpeningRecord, NULL);
			CloseRowSet();
			return false;
		}

		// Прочитаме всички данни
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


	bool SelectWhereID(const long lID, Record_Type& recTableRecord)
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


	bool UpdateWhereID(const long lID, const Record_Type& recTableRecord)
	{
		// Конструираме заявката
		CString strQuery;
		strQuery.Format(SqlQueries::SelectWhereID, m_strTableName, lID);

		// Изпълняваме командата
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


	bool InsertRecord(const Record_Type& recTableRecord)
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
		CloseRowSet();

		return true;
	};

	bool DeleteWhereID(const long lID)
	{
		// Конструираме заявката
		CString strQuery;
		strQuery.Format(SqlQueries::SelectWhereID, m_strTableName, lID);

		// Изпълняваме командата
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
		m_oSession.Commit();
		CloseRowSet();
		return true;
	};

	bool DeleteBySpecificColumnWhereID(const long lID, CString strSqlWhereClause)
	{
		// Конструираме заявката
		CString strQuery;
		strQuery.Format(SqlQueries::SelectAll, m_strTableName);
		strQuery.Append(strSqlWhereClause);

		// Изпълняваме командата
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
		m_oSession.Commit();
		CloseRowSet();
		return true;
	};

	bool SelectBySpecificColumnWhereID(CSelfClearingTypedPtrArray<Record_Type>& oPtrArray, CString strSqlWhereClause)
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


	bool UpdateBySpecificColumnWhereID(const long lID, const Record_Type& recTableRecord, CString strSqlWhereClause)
	{
		// Конструираме заявката
		CString strQuery;
		strQuery.Format(SqlQueries::SelectWhereID, m_strTableName, lID);
		strQuery.Append(strSqlWhereClause);

		// Изпълняваме командата
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

