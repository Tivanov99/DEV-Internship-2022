#pragma once
#include "pch.h"
#include "CBaseTable.h"
#include "ErrorVisualizator.h"

#define NoneModifyColumnCode 0
#define ModifyColumnCode 1

template <typename Record_Type, class Table_AcessorType>
CBaseTable< Record_Type, Table_AcessorType>::CBaseTable(CSession& oSession, TCHAR* pszTableName)
	:m_oSession(oSession), m_strTableName(pszTableName)
{
};

template <typename Record_Type, class Table_AcessorType>
CBaseTable<Record_Type, Table_AcessorType>::~CBaseTable()
{};


template <typename Record_Type, class Table_AcessorType>
CDBPropSet CBaseTable< Record_Type, Table_AcessorType>::GetModifyDBPropSet() const
{
	CDBPropSet oUpdateDBPropSet(DBPROPSET_ROWSET);
	oUpdateDBPropSet.AddProperty(DBPROP_CANFETCHBACKWARDS, true);
	oUpdateDBPropSet.AddProperty(DBPROP_IRowsetScroll, true);
	oUpdateDBPropSet.AddProperty(DBPROP_IRowsetChange, true);
	oUpdateDBPropSet.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE);
	return oUpdateDBPropSet;
};

template <typename Record_Type, class Table_AcessorType>
bool CBaseTable< Record_Type, Table_AcessorType>::ExecuteQuery(const CString& strQuery, AccessorTypes eQueryAccessor)
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
bool CBaseTable< Record_Type, Table_AcessorType>::SelectAll(CSelfClearingTypedPtrArray<Record_Type>& oPtrArray)
{
	CString strQuery;
	strQuery.Format(_T("SELECT * FROM %s"), m_strTableName);
	// Изпълняваме командата
	if (!ExecuteQuery(strQuery, AccessorTypes::NoneModifying))
		return false;

	//TODO: CHECK HERE
	HRESULT hResult = MoveFirst();
	if (FAILED(hResult))
	{
		ErrorMessageVisualizator::ShowErrorMessage(lpszErrorOpeningRecord, NULL);
		return false;
	}

	// Прочитаме всички данни
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


template <typename Record_Type, class Table_AcessorType>
bool CBaseTable< Record_Type, Table_AcessorType>::SelectWhereID(const long lID, Record_Type& recTableRecord)
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


template <typename Record_Type, class Table_AcessorType>
bool CBaseTable< Record_Type, Table_AcessorType>::UpdateWhereID(const long lID, const Record_Type& recTableRecord)
{
	// Конструираме заявката
	CString strQuery;
	strQuery.Format(_T("SELECT * FROM %s WHERE ID = %d"), m_strTableName, lID);

	// Изпълняваме командата
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


template <typename Record_Type, class Table_AcessorType>
bool CBaseTable< Record_Type, Table_AcessorType>::InsertRecord(const Record_Type& recTableRecord)
{
	CString strQuery;
	strQuery.Format(_T("SELECT TOP 0 * FROM %s"), m_strTableName);

	if (!ExecuteQuery(strQuery, AccessorTypes::Modifying))
	{
		ErrorMessageVisualizator::ShowErrorMessage(lpszErrorExecutingQuery,NULL);
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

template <typename Record_Type, class Table_AcessorType>
bool CBaseTable< Record_Type, Table_AcessorType>::DeleteWhereID(const long lID)
{
	// Конструираме заявката
	CString strQuery;
	strQuery.Format(_T("SELECT * FROM %s WHERE ID = %d"), m_strTableName, lID);

	// Изпълняваме командата
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

template <typename Record_Type, class Table_AcessorType>
void CBaseTable< Record_Type, Table_AcessorType>::CloseRowSet()
{
	Close();
}

