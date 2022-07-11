#include "pch.h"
#include "CCitiesTable.h"


/////////////////////////////////////////////////////////////////////////////
// CCitiesTable
const CString strSelectAllById = _T("SELECT * FROM CITIES WHERE ID = %d");
const CString strSelectAll = _T("SELECT * FROM CITIES");
const CString strUnableToConnectServer = _T("Unable to connect to SQL Server database. Error: %d");
const CString strUnableToOpenSession = _T("Unable to open session. Error: %d");
const CString strErrorExecutingQuery = _T("Error executing query.Error:% d.Query : % s");
const CString strErrorOpeningRecord = _T("Error opening record.Error:% d.Query : % s");
const CString strErrorUpdatingRecord = _T("Error updating record.Error:% d.Query : % s");
const CString strErrorDeletingRecord = _T("Error deleting record.Error:% d.Query : % s");



CCitiesTable::CCitiesTable()
{
};
CCitiesTable::~CCitiesTable()
{
};

void CCitiesTable::CloseConnection(CDataSource& oDataSource, CSession& oSession)
{
	Close();
	oSession.Close();
	oDataSource.Close();
};

void CCitiesTable::ShowErrorMessage(const HRESULT& hResult, const CString& strErrorMessage, const CString& strQuery )
{
	CString strError;
	strError.Format(strErrorMessage, hResult, strQuery.GetString());
	AfxMessageBox(strError);
	CloseConnection(oDataSource, oSession);
}

CDBPropSet CCitiesTable::BuildCDBPropSet()
{
	CDBPropSet oDBPropSet(DBPROPSET_DBINIT);
	oDBPropSet.AddProperty(DBPROP_INIT_DATASOURCE, _T("DESKTOP-6RL5K65"));	// сървър
	oDBPropSet.AddProperty(DBPROP_AUTH_INTEGRATED, _T("SSPI"));
	oDBPropSet.AddProperty(DBPROP_INIT_CATALOG, _T("PhoneBook"));	// база данни
	oDBPropSet.AddProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO, false);
	oDBPropSet.AddProperty(DBPROP_INIT_LCID, 1033L);
	oDBPropSet.AddProperty(DBPROP_INIT_PROMPT, static_cast<short>(4));

	return oDBPropSet;
};

CDBPropSet CCitiesTable::BuildUpdateDBPropSet()
{
	CDBPropSet oUpdateDBPropSet(DBPROPSET_ROWSET);
	oUpdateDBPropSet.AddProperty(DBPROP_CANFETCHBACKWARDS, true);
	oUpdateDBPropSet.AddProperty(DBPROP_IRowsetScroll, true);
	oUpdateDBPropSet.AddProperty(DBPROP_IRowsetChange, true);
	oUpdateDBPropSet.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE);
	return oUpdateDBPropSet;
}

BOOL CCitiesTable::ConnectoToDb(CDataSource& oDataSource, CSession& oSession)
{
	CDBPropSet& oDBPropSet = BuildCDBPropSet();

	// Свързваме се към базата данни
	HRESULT hResult = oDataSource.Open(_T("SQLOLEDB"), &oDBPropSet);

	if (FAILED(hResult))
	{
		AfxMessageBox(strUnableToConnectServer, hResult);
		return FALSE;
	}

	// Отваряме сесия
	hResult = oSession.Open(oDataSource);
	if (FAILED(hResult))
	{
		AfxMessageBox(strUnableToOpenSession, hResult);
		oDataSource.Close();
		return FALSE;
	}
	return TRUE;
};

BOOL CCitiesTable::ExecuteNoneModifyQuery(HRESULT& hResult, CSession& oSession, CDataSource& oDataSource, const CString& strQuery)
{
	hResult = Open(oSession, strQuery);
	if (FAILED(hResult))
	{
		ShowErrorMessage(hResult,strErrorExecutingQuery,strQuery);
		return FALSE;
	}
	return TRUE;
}

BOOL CCitiesTable::SelectAll(CCitiesArray& oCitiesArray)
{
	CDataSource oDataSource;
	CSession oSession;
	HRESULT hResult;

	if (!ConnectoToDb(oDataSource, oSession))
		return FALSE;

	// Изпълняваме командата
	if (!ExecuteNoneModifyQuery(hResult, oSession, oDataSource, strSelectAll))
		return FALSE;

	// Прочитаме всички данни
	while (MoveNext() != DB_S_ENDOFROWSET)
	{
		// Logic with the result
		CITIES* pCurrentCity = new CITIES;
		*pCurrentCity = m_recCITY;
		oCitiesArray.Add(pCurrentCity);
	}

	// Затваряме командата, сесията и връзката с базата данни. 
	CloseConnection(oDataSource, oSession);

	return TRUE;
};

BOOL CCitiesTable::SelectWhereID(const long lID, CITIES& recCities)
{
	CDataSource oDataSource;
	CSession oSession;

	if (!ConnectoToDb(oDataSource, oSession))
		return FALSE;

	CString strQuery;
	strQuery.Format(strSelectAllById.GetString(), lID);

	HRESULT hResult;

	if (!ExecuteNoneModifyQuery(hResult, oSession, oDataSource, strQuery))
		return FALSE;

	while (MoveNext() != DB_S_ENDOFROWSET)
	{
		recCities = m_recCITY;
	}

	CloseConnection(oDataSource, oSession);
	return TRUE;
};

BOOL CCitiesTable::UpdateWhereID(const long lID, const CITIES& recCities)
{
	CDataSource oDataSource;
	CSession oSession;

	if (!ConnectoToDb(oDataSource, oSession))
		return FALSE;

	// Конструираме заявката
	CString strQuery;
	strQuery.Format(strSelectAllById.GetString(), lID);

	// Настройка на типа на Rowset-а
	CDBPropSet oUpdateDBPropSet = BuildUpdateDBPropSet();

	HRESULT hResult;

	// Изпълняваме командата
	hResult = Open(oSession, strQuery, &oUpdateDBPropSet);
	if (FAILED(hResult))
	{
		ShowErrorMessage(oDataSource,oSession,hResult,strSelectAllById,strQuery);
		return FALSE;
	}

	hResult = MoveFirst();

	if (FAILED(hResult) || hResult== DB_S_ENDOFROWSET)
	{
		ShowErrorMessage(oDataSource, oSession, hResult, strQuery);
		return FALSE;
	}

	if (recCities.lUPDATE_COUNTER != m_recCITY.lUPDATE_COUNTER)
		return FALSE;

	m_recCITY.lUPDATE_COUNTER++;
	m_recCITY = recCities;

	hResult = SetData(ModifyColumnCode);

	if (FAILED(hResult))
	{
		ShowErrorMessage(oDataSource, oSession, hResult, strQuery);

		CString strErrorMessage;
		strErrorMessage.Format(_T("Error updating record. Error: %d. Query: %s"), hResult, strQuery.GetString());
		AfxMessageBox(strErrorMessage);
		CloseConnection(oDataSource, oSession);
		return FALSE;
	}

	CloseConnection(oDataSource, oSession);

	return TRUE;
};

BOOL CCitiesTable::Insertt(const CITIES& recCities)
{
	CSession oSession;
	CDataSource oDataSource;

	if (!ConnectoToDb(oDataSource, oSession))
		return FALSE;

	CDBPropSet oUpdatePropSet = BuildUpdateDBPropSet();

	CString strQuery = _T("SELECT TOP 0 * FROM CITIES");

	HRESULT hResult = S_FALSE;

	hResult = Open(oSession, strQuery, &oUpdatePropSet);
	if (FAILED(hResult))
	{
		ShowErrorMessage(oDataSource, oSession, hResult, strErrorExecutingQuery, strQuery);
		return FALSE;
	}

	hResult = MoveFirst();
	if (FAILED(hResult))
	{
		ShowErrorMessage(oDataSource, oSession, hResult, strErrorOpeningRecord, strQuery);
		return FALSE;
	}

	m_recCITY = recCities;

	hResult = Insert(ModifyColumnCode);
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("Insert failed: 0x%X\n"), hResult);
		CloseConnection(oDataSource, oSession);
		return FALSE;
	}

	CloseConnection(oDataSource, oSession);
	return TRUE;
};

BOOL CCitiesTable::DeleteWhereID(const long lID)
{
	CDataSource oDataSource;
	CSession oSession;

	if (!ConnectoToDb(oDataSource, oSession))
		return FALSE;

	// Конструираме заявката
	CString strQuery;
	strQuery.Format(_T("SELECT * FROM CITIES WHERE ID = %d"), lID);

	// Настройка на типа на Rowset-а
	CDBPropSet oUpdateDBPropSet = BuildUpdateDBPropSet();

	HRESULT hResult;

	// Изпълняваме командата
	hResult = Open(oSession, strQuery, &oUpdateDBPropSet);

	if (FAILED(hResult))
	{
		ShowErrorMessage(oDataSource, oSession, hResult, strErrorExecutingQuery, strQuery);
		return FALSE;
	}

	hResult = MoveFirst();

	if (FAILED(hResult) || hResult == DB_S_ENDOFROWSET)
	{
		ShowErrorMessage(oDataSource, oSession, hResult, strErrorOpeningRecord, strQuery);

		return FALSE;
	}

	hResult = Delete();

	if (FAILED(hResult))
	{
		ATLTRACE(_T("Delete failed: 0x%X\n"), hResult);
		CloseConnection(oDataSource, oSession);
		return FALSE;
	}
	CloseConnection(oDataSource, oSession);

	return TRUE;
};

