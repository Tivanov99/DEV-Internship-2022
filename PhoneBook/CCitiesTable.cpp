﻿#include "pch.h"
#include "CCitiesTable.h"


const LPCSTR CCitiesTable::lpszSelectAllById = "SELECT * FROM CITIES WHERE ID = %d";
const LPCSTR CCitiesTable::lpszInvalidRecordVersion = "Invalid version of current record! Please reload the record again.";
const LPCSTR CCitiesTable::lpszErrorExecutingQuery = "Error executing query.Error:% d.Query : % s";
const LPCSTR CCitiesTable ::lpszErrorInvalidQueryAcessor  = 
	"Invalid query accessor! Use 0 for non-record-changing queries or 1 for record-changing queries";
/////////////////////////////////////////////////////////////////////////////
// CCitiesTable

CCitiesTable::CCitiesTable()
{
};
CCitiesTable::~CCitiesTable()
{
};

void CCitiesTable::CloseSessionAndConnection(CDataSource& oDataSource, CSession& oSession)
{
	Close();
	oSession.Close();
	oDataSource.Close();
};

void CCitiesTable::ShowErrorMessage(const LPCSTR strErrorMessage, const CString& strQuery)
{
	CString strError;
	if (strQuery.GetString() != NULL)
	{
		strError.Format((CString)strErrorMessage, strQuery.GetString());
	}
	else
	{
		strError.Format((CString)strErrorMessage);
	}
	AfxMessageBox(strError);
}

CDBPropSet CCitiesTable::GetDBPropSet()const
{
	CDBPropSet oDBPropSet(DBPROPSET_DBINIT);
	oDBPropSet.AddProperty(DBPROP_INIT_DATASOURCE, _T("DESKTOP-6RL5K65"));	// сървър
	oDBPropSet.AddProperty(DBPROP_AUTH_INTEGRATED, _T("SSPI"));
	oDBPropSet.AddProperty(DBPROP_INIT_CATALOG, _T("PhoneBook"));	// база данни
	oDBPropSet.AddProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO, false);
	oDBPropSet.AddProperty(DBPROP_INIT_LCID, 1033L);
	oDBPropSet.AddProperty(DBPROP_INIT_PROMPT, static_cast<short>(4));

	return oDBPropSet;
}

CDBPropSet CCitiesTable::GetModifyDBPropSet() const
{
	CDBPropSet oUpdateDBPropSet(DBPROPSET_ROWSET);
	oUpdateDBPropSet.AddProperty(DBPROP_CANFETCHBACKWARDS, true);
	oUpdateDBPropSet.AddProperty(DBPROP_IRowsetScroll, true);
	oUpdateDBPropSet.AddProperty(DBPROP_IRowsetChange, true);
	oUpdateDBPropSet.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE);
	return oUpdateDBPropSet;
}

bool CCitiesTable::OpenSessionAndConnectionToDb(CDataSource& oDataSource, CSession& oSession)
{
	CDBPropSet& oDBPropSet = GetDBPropSet();

	// Свързваме се към базата данни
	HRESULT hResult = oDataSource.Open(_T("SQLOLEDB"), &oDBPropSet);

	if (FAILED(hResult))
	{
		AfxMessageBox(strUnableToConnectServer, hResult);
		return false;
	}

	// Отваряме сесия
	hResult = oSession.Open(oDataSource);
	if (FAILED(hResult))
	{
		AfxMessageBox(strUnableToOpenSession, hResult);
		oDataSource.Close();
		return false;
	}
	return true;
};

bool CCitiesTable::ExecuteQuery(CSession& oSession, const CString& strQuery, const int nQueryAccessor)
{
	if (nQueryAccessor == NoneModifyColumnCode)
	{
		if (FAILED(Open(oSession, strQuery)))
		{
			ShowErrorMessage(lpszErrorExecutingQuery, strQuery);
			return false;
		}
		return true;
	}
	else if (nQueryAccessor == ModifyColumnCode)
	{
		CDBPropSet oUpdateDBPropSet = GetModifyDBPropSet();
		if (FAILED(Open(oSession, strQuery,&oUpdateDBPropSet)))
		{
			ShowErrorMessage(lpszErrorExecutingQuery, strQuery);
			return false;
		}
		return true;
	}
	ShowErrorMessage(lpszErrorInvalidQueryAcessor, strQuery);
	return false;
}

bool CCitiesTable::SelectAll(CCitiesArray& oCitiesArray)
{
	CDataSource oDataSource;
	CSession oSession;

	if (!OpenSessionAndConnectionToDb(oDataSource, oSession))
		return false;

	// Изпълняваме командата
	if (!ExecuteQuery(oSession, strSelectAll,NoneModifyColumnCode))
	{
		CloseSessionAndConnection(oDataSource, oSession);
		return false;
	}


	//TODO: CHECK HERE
	HRESULT hResult = MoveFirst();
	if (FAILED(hResult))
	{
		ShowErrorMessage(strErrorOpeningRecord);
	}
	// Прочитаме всички данни
		while (MoveNext() != DB_S_ENDOFROWSET)
		{
			// Logic with the result
			CITIES* pCurrentCity = new CITIES;
			*pCurrentCity = m_recCITY;
			oCitiesArray.Add(pCurrentCity);
		}

	// Затваряме командата, сесията и връзката с базата данни. 
	CloseSessionAndConnection(oDataSource, oSession);

	return true;
};

bool CCitiesTable::SelectWhereID(const long lID, CITIES& recCities)
{
	CDataSource oDataSource;
	CSession oSession;

	if (!OpenSessionAndConnectionToDb(oDataSource, oSession))
		return false;

	CString strQuery;
	strQuery.Format((CString)lpszSelectAllById, lID);

	if (!ExecuteQuery(oSession, strQuery,NoneModifyColumnCode))
	{
		CloseSessionAndConnection(oDataSource, oSession);
		return false;
	}


	//TODO: CHECH HERE
	while (MoveNext() != DB_S_ENDOFROWSET)
	{
		recCities = m_recCITY;
	}

	CloseSessionAndConnection(oDataSource, oSession);
	return true;
};

bool CCitiesTable::UpdateWhereID(const long lID, const CITIES& recCities)
{
	CDataSource oDataSource;
	CSession oSession;

	if (!OpenSessionAndConnectionToDb(oDataSource, oSession))
		return false;

	// Конструираме заявката
	CString strQuery;
	strQuery.Format((CString)lpszSelectAllById, lID);

	// Изпълняваме командата
	if (!ExecuteQuery(oSession, strQuery,ModifyColumnCode))
	{
		CloseSessionAndConnection(oDataSource, oSession);
		return false;
	}

	if (FAILED(MoveFirst()))
	{
		ShowErrorMessage(strErrorOpeningRecord, strQuery);
		CloseSessionAndConnection(oDataSource, oSession);
		return false;
	}

	if (recCities.lUPDATE_COUNTER != m_recCITY.lUPDATE_COUNTER)
	{
		ShowErrorMessage(lpszInvalidRecordVersion);
		return false;
	}

	m_recCITY.lUPDATE_COUNTER++;
	m_recCITY = recCities;

	if (FAILED(SetData(ModifyColumnCode)))
	{
		ShowErrorMessage(strErrorUpdatingRecord);
		CloseSessionAndConnection(oDataSource, oSession);
		return false;
	}

	CloseSessionAndConnection(oDataSource, oSession);

	return true;
};

bool CCitiesTable::Insert(const CITIES& recCities)
{
	CSession oSession;
	CDataSource oDataSource;

	if (!OpenSessionAndConnectionToDb(oDataSource, oSession))
		return false;

	if (!ExecuteQuery(oSession, strEmptySelect, ModifyColumnCode))
	{
		ShowErrorMessage(lpszErrorExecutingQuery, strEmptySelect);
		CloseSessionAndConnection(oDataSource, oSession);
		return false;
	}

	m_recCITY = recCities;

	if (FAILED(__super::Insert(ModifyColumnCode)))
	{
		ShowErrorMessage(strErrorInsertingRecord);
		CloseSessionAndConnection(oDataSource, oSession);
		return false;
	}

	CloseSessionAndConnection(oDataSource, oSession);
	return true;
};

bool CCitiesTable::DeleteWhereID(const long lID)
{
	CDataSource oDataSource;
	CSession oSession;

	if (!OpenSessionAndConnectionToDb(oDataSource, oSession))
		return false;

	// Конструираме заявката
	CString strQuery;
	strQuery.Format((CString)lpszSelectAllById, lID);

	// Изпълняваме командата
	if (!ExecuteQuery(oSession, strEmptySelect, ModifyColumnCode))
	{
		ShowErrorMessage(lpszErrorExecutingQuery, strQuery);
		CloseSessionAndConnection(oDataSource, oSession);
		return false;
	}

	if (MoveFirst() != S_OK)
	{
		ShowErrorMessage(strErrorOpeningRecord, strQuery);
		CloseSessionAndConnection(oDataSource, oSession);
		return false;
	}

	if (FAILED(Delete()))
	{
		ShowErrorMessage(strErrorDeletingRecord);
		CloseSessionAndConnection(oDataSource, oSession);
		return false;
	}
	CloseSessionAndConnection(oDataSource, oSession);

	return true;
};

