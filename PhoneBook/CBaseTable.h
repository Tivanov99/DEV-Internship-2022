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
	/// Функция която конструира пропърти сет нужен при добавяне, изтриване или актуализиране на запис.
	/// </summary>
	/// <returns>Обект</returns>
	CDBPropSet GetModifyDBPropSet() const;
	/// <summary>Функция която изпълнява команда в базата данни.</summary>
	/// <param name="strQuery">Заявката към базата.</param>
	/// <param name="eQueryAccessor">Типът на достъп</param>
	bool ExecuteQuery(const CString& strQuery, AccessorTypes eQueryAccessor);
	/// <summary>Функция която изчита всички записи от базата и ги записва в масива подаден като аргумент 'oPtrArray'.</summary>
	/// <param name="oPtrArray">Масив където ще се запишат всички записи от базата.</param>
	bool SelectAll(CSelfClearingTypedPtrArray<Record_Type>& oPtrArray);
	/// <summary>Функция която изчита запис от базата чието ID отговаря на аргумента 'lID' и го презаписва в 'recTableRecord' аргумента.<summary>
	/// <param name="lID">Уникален идентификатор по който ще се изчете запис.</param>
	/// <param name="recTableRecord">Референция към обект където ще се запише изчетения запис от базата.</param>
	bool SelectWhereID(const long lID, Record_Type& recTableRecord);
	/// <summary>Функция която актуализира запис от базата чието ID отговаря на аргумента 'lID' с данните от 'recTableRecord' аргумента.</summary>
	/// <param name="lID">Уникален идентификатор по който ще се изчете запис.</param>
	/// <param name="recTableRecord">Референция към обект който съдържа новата информация за записа от базата.</param>
	bool UpdateWhereID(const long lID, const Record_Type& recTableRecord);
	/// <summary>Финкция която добавя запис в базата.</summary>
	/// <param name="recTableRecord">Референция към обект който ще бъде добавен в базата.</param>
	bool InsertRecord(Record_Type& recTableRecord);
	/// <summary>Функция която трие запис от базата чиято стойност в колоната 'ID' отговаря на 'lID'.</summary>
	/// <param name="lID">Уникален идентификатор по който ще се изтрие запис.</param>
	bool DeleteWhereID(const long lID);
	/// <summary>Функция която изтрива запис/и чрез идентификатор 'lID' и клауза указваща за коя колона се отнася която е подадена като аргумент 'strSqlWhereClause'.</summary>
	/// <param name="lID">Уникален идентификатор по който ще се изтрие запис.</param>
	/// <param name="strSqlWhereClause">Клауза указваща за коя колона се отнася заявката.</param>
	bool DeleteBySpecificColumnWhereID(const long lID, CString strSqlWhereClause);
	/// <summary>Функция която изчита запис/и според клауза която указва за коя колона се отнася заявката, и ги записва в 'oPtrArray'.</summary>
	/// <param name="oPtrArray">Масив където се записват всички изчетени от базата запис/и.</param>
	/// <param name="strSqlWhereClause">Клауза указваща за коя колона се отнася заявката.</param>
	bool SelectBySpecificColumnWhereID(CSelfClearingTypedPtrArray<Record_Type>& oPtrArray, CString strSqlWhereClause);
	/// <summary>Функция която актуализира запис от таблица със специфична колона указана чрез калузата 'strSqlWhereClause' подадена като аргумент и според 'lID'.</summary>
	/// <param name="lID">Уникален идентификатор по който ще се актуализира информацията за запис.</param>
	/// <param name="recTableRecord">Референция към обект който съдържа вече актуализирана информация.</param>
	/// <param name="strSqlWhereClause">Клауза указваща за коя колона се отнася заявката.</param>
	bool UpdateBySpecificColumnWhereID(const long lID, const Record_Type& recTableRecord, CString strSqlWhereClause);
	/// <summary>Функция която затваря RowSet.</summary>
	void CloseRowSet();
	// Members
	// -------------
public:
	/// <summary>Клас мембър чрез който се достъпва бизнеслогиката.</summary>
	CDataSource m_oDataSource;
	/// <summary>Клас мембър който съдържа сесията нужна за заявките и транзакцийте към базата.</summary>
	CSession& m_oSession;
private:
	/// <summary>Клас мембър съдържащ името на текущата таблица в която се извърват операции.</summary>
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


template <typename Record_Type, class Table_AcessorType>
void CBaseTable<Record_Type, Table_AcessorType>::CloseRowSet()
{
	Close();
}