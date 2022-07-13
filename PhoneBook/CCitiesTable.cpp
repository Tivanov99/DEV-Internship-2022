#include "pch.h"
#include "CCitiesTable.h"


const LPCSTR CCitiesTable::lpszSelectAllById = "SELECT * FROM CITIES WHERE ID = %d";
const LPCSTR CCitiesTable::lpszInvalidRecordVersion = "Invalid version of current record! Please reload the record again.";
const LPCSTR CCitiesTable::lpszErrorExecutingQuery = "Error executing query.Error:% d.Query : % s";
const LPCSTR CCitiesTable ::lpszErrorInvalidQueryAcessor  = 
	"Invalid query accessor! Use 0 for non-record-changing queries or 1 for record-changing queries";
const LPCSTR CCitiesTable::lpszSelectAll = "SELECT * FROM CITIES";
const LPCSTR CCitiesTable::lpszEmptySelect = "SELECT TOP 0 * FROM CITIES";
const LPCSTR CCitiesTable::lpszUnableToConnectServer = "Unable to connect to SQL Server database. Error: %d";
const LPCSTR CCitiesTable::lpszUnableToOpenSession = "Unable to open session. Error: %d";
const LPCSTR CCitiesTable::lpszErrorOpeningRecord = "Error opening record.Error:% d";
const LPCSTR CCitiesTable::lpszErrorUpdatingRecord = "Error updating record.Error:% d.Query : % s";
const LPCSTR CCitiesTable::lpszErrorDeletingRecord = "Delete failed: 0x%X\n";
const LPCSTR CCitiesTable::lpszErrorInsertingRecord = "Insert failed: 0x%X\n";
/////////////////////////////////////////////////////////////////////////////
// CCitiesTable

CCitiesTable::CCitiesTable()
{
};
CCitiesTable::~CCitiesTable()
{
};

void CCitiesTable::CloseSessionAndConnection()
{
	Close();
	m_oSession.Close();
	m_oDataSource.Close();
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

bool CCitiesTable::OpenSessionAndConnectionToDb()
{
	CDBPropSet& oDBPropSet = GetDBPropSet();

	// Свързваме се към базата данни
	HRESULT hResult = m_oDataSource.Open(_T("SQLOLEDB"), &oDBPropSet);

	if (FAILED(hResult))
	{
		AfxMessageBox((CString)lpszUnableToConnectServer, hResult);
		return false;
	}

	// Отваряме сесия
	hResult = m_oSession.Open(m_oDataSource);
	if (FAILED(hResult))
	{
		AfxMessageBox((CString)lpszUnableToOpenSession, hResult);
		m_oDataSource.Close();
		return false;
	}
	return true;
};

bool CCitiesTable::ExecuteQuery(const CString& strQuery, const int nQueryAccessor)
{
	if (nQueryAccessor == NoneModifyColumnCode)
	{
		if (FAILED(Open(m_oSession, strQuery)))
		{
			ShowErrorMessage(lpszErrorExecutingQuery, strQuery);
			return false;
		}
		return true;
	}
	else if (nQueryAccessor == ModifyColumnCode)
	{
		CDBPropSet oUpdateDBPropSet = GetModifyDBPropSet();
		if (FAILED(Open(m_oSession, strQuery,&oUpdateDBPropSet)))
		{
			ShowErrorMessage(lpszErrorExecutingQuery, strQuery);
			return false;
		}
		return true;
	}
	ShowErrorMessage(lpszErrorInvalidQueryAcessor, strQuery);
	return false;
}

bool CCitiesTable::SelectAll(CSelfClearingTypedPtrArray<CITIES>& oCitiesPtrArray)
{
	if (!OpenSessionAndConnectionToDb())
		return false;

	// Изпълняваме командата
	if (!ExecuteQuery((CString)lpszSelectAll,NoneModifyColumnCode))
	{
		CloseSessionAndConnection();
		return false;
	}

	//TODO: CHECK HERE
	HRESULT hResult = MoveFirst();
	if (FAILED(hResult))
	{
		ShowErrorMessage(lpszErrorOpeningRecord);
		CloseSessionAndConnection();
		return false;
	}

	// Прочитаме всички данни
	while (hResult != DB_S_ENDOFROWSET)
	{
		CITIES* pCurrentCity = new CITIES;
		*pCurrentCity = m_recCITY;
		oCitiesPtrArray.Add(pCurrentCity);

		hResult = MoveNext();

		if (FAILED(hResult) && hResult!= DB_S_ENDOFROWSET)
		{
			ShowErrorMessage(lpszErrorOpeningRecord);
			CloseSessionAndConnection();
			return false;
		}
		// Logic with the result
	}

	// Затваряме командата, сесията и връзката с базата данни. 
	CloseSessionAndConnection();

	return true;
};

bool CCitiesTable::SelectWhereID(const long lID, CITIES& recCities)
{
	if (!OpenSessionAndConnectionToDb())
		return false;

	CString strQuery;
	strQuery.Format((CString)lpszSelectAllById, lID);

	if (!ExecuteQuery(strQuery,NoneModifyColumnCode))
	{
		CloseSessionAndConnection();
		return false;
	}

	if (FAILED(MoveFirst()))
	{
		ShowErrorMessage(lpszErrorOpeningRecord);
		CloseSessionAndConnection();
		return false;
	}
		recCities = m_recCITY;

	CloseSessionAndConnection();
	return true;
};

bool CCitiesTable::UpdateWhereID(const long lID, const CITIES& recCities)
{
	if (!OpenSessionAndConnectionToDb())
		return false;

	// Конструираме заявката
	CString strQuery;
	strQuery.Format((CString)lpszSelectAllById, lID);

	// Изпълняваме командата
	if (!ExecuteQuery(strQuery,ModifyColumnCode))
	{
		CloseSessionAndConnection();
		return false;
	}

	if (FAILED(MoveFirst()))
	{
		ShowErrorMessage(lpszErrorOpeningRecord, strQuery);
		CloseSessionAndConnection();
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
		ShowErrorMessage(lpszErrorUpdatingRecord);
		CloseSessionAndConnection();
		return false;
	}

		CloseSessionAndConnection();


	return true;
};

bool CCitiesTable::Insert(const CITIES& recCities)
{
	if (!OpenSessionAndConnectionToDb())
		return false;

	if (!ExecuteQuery((CString)lpszEmptySelect, ModifyColumnCode))
	{
		ShowErrorMessage(lpszErrorExecutingQuery, (CString)lpszEmptySelect);
		CloseSessionAndConnection();
		return false;
	} 

	m_recCITY = recCities;

	if (FAILED(__super::Insert(ModifyColumnCode)))
	{
		ShowErrorMessage(lpszErrorInsertingRecord);
		CloseSessionAndConnection();
		return false;
	}

	CloseSessionAndConnection();
	return true;
};

bool CCitiesTable::DeleteWhereID(const long lID)
{
	if (!OpenSessionAndConnectionToDb())
		return false;

	// Конструираме заявката
	CString strQuery;
	strQuery.Format((CString)lpszSelectAllById, lID);

	// Изпълняваме командата
	if (!ExecuteQuery(strQuery, ModifyColumnCode))
	{
		ShowErrorMessage(lpszErrorExecutingQuery, strQuery);
		CloseSessionAndConnection();
		return false;
	}

	if (MoveFirst() != S_OK)
	{
		ShowErrorMessage(lpszErrorOpeningRecord, strQuery);
		CloseSessionAndConnection();
		return false;
	}

	if (FAILED(Delete()))
	{
		ShowErrorMessage(lpszErrorDeletingRecord);
		CloseSessionAndConnection();
		return false;
	}
	CloseSessionAndConnection();

	return true;
};

