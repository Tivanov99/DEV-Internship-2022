#include "pch.h"
#include "CCitiesTable.h"

void CCitiesTable::CloseConnection(CDataSource& oDataSource, CSession& oSession)
{
	Close();
	oSession.Close();
	oDataSource.Close();
};

CDBPropSet CCitiesTable::BuildCDBPropSet()
{
	CDBPropSet oDBPropSet(DBPROPSET_DBINIT);
	oDBPropSet.AddProperty(DBPROP_INIT_DATASOURCE, _T("DESKTOP-6RL5K65"));	// ������
	oDBPropSet.AddProperty(DBPROP_AUTH_INTEGRATED, _T("SSPI"));
	oDBPropSet.AddProperty(DBPROP_INIT_CATALOG, _T("PhoneBook"));	// ���� �����
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

	// ��������� �� ��� ������ �����
	HRESULT hResult = oDataSource.Open(_T("SQLOLEDB"), &oDBPropSet);

	if (FAILED(hResult))
	{
		AfxMessageBox(_T("Unable to connect to SQL Server database. Error: %d"), hResult);
		return FALSE;
	}

	// �������� �����
	hResult = oSession.Open(oDataSource);
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("Unable to open session. Error: %d"), hResult);
		oDataSource.Close();

		return FALSE;
	}
	return TRUE;
};

BOOL CCitiesTable::ExecuteQuery(HRESULT& hResult, CSession& oSession, CDataSource& oDataSource, const CString& strQuery)
{
	hResult = Open(oSession, strQuery);
	if (FAILED(hResult))
	{
		wprintf(_T("Error executing query. Error: %d. Query: %s"), hResult, strQuery);

		oSession.Close();
		oDataSource.Close();

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

	// ������������ ��������
	const CString strQuery = _T("SELECT * FROM CITIES");
	// ����������� ���������

	if (!ExecuteQuery(hResult, oSession, oDataSource, strQuery))
	{
		return FALSE;
	}

	// ��������� ������ �����
	while (MoveNext() == S_OK)
	{
		CString strCustomerData;
		strCustomerData.Format(_T("ID: %d, City Name: %s, Area Name: %s, Postal Code: %d"),
			m_recCITY.lID,
			m_recCITY.szCITY_NAME,
			m_recCITY.szAREA_NAME,
			m_recCITY.lPOSTAL_CODE);
		CITIES* pCurrentCity = new CITIES;
		*pCurrentCity = m_recCITY;
		oCitiesArray.Add(pCurrentCity);

		//check last result from MoveNext()!
		// Logic with the result
	}

	// ��������� ���������, ������� � �������� � ������ �����. 
	CloseConnection(oDataSource, oSession);

	return TRUE;
};

BOOL CCitiesTable::SelectWhereID(const long lID, CITIES& recCities)
{
	CDataSource oDataSource;
	CSession oSession;
	HRESULT hResult;

	if (!ConnectoToDb(oDataSource, oSession))
	{
		return FALSE;
	}

	CString strQuery;
	strQuery.Format(_T("SELECT * FROM CITIES WHERE ID = %d"), lID);

	if (!ExecuteQuery(hResult, oSession, oDataSource, strQuery))
	{
		return FALSE;
	}

	while (MoveNext() == S_OK())
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

	// ������������ ��������
	CString strQuery;
	strQuery.Format(_T("SELECT * FROM CITIES WHERE ID = %d"), lID);

	// ��������� �� ���� �� Rowset-�
	CDBPropSet oUpdateDBPropSet = BuildUpdateDBPropSet();

	HRESULT hResult;

	// ����������� ���������
	hResult = Open(oSession, strQuery, &oUpdateDBPropSet);

	if (FAILED(hResult))
	{
		wprintf(_T("Error executing query. Error: %d. Query: %s"), hResult, strQuery);

		oSession.Close();
		oDataSource.Close();

		return FALSE;
	}

	hResult = MoveFirst();

	if (FAILED(hResult))
	{
		wprintf(_T("Error opening record. Error: %d. Query: %s"), hResult, strQuery);

		CloseConnection(oDataSource, oSession);
		return FALSE;
	}

	if (recCities.lUPDATE_COUNTER != m_recCITY.lUPDATE_COUNTER)
		return FALSE;


	m_recCITY.lUPDATE_COUNTER++;



	hResult = SetData(ModifyColumnCode);

	if (FAILED(hResult))
	{
		wprintf(_T("Error updating record. Error: %d. Query: %s"), hResult, strQuery);
		CloseConnection(oDataSource, oSession);
		return FALSE;
	}

	CloseConnection(oDataSource, oSession);

	return TRUE;
};

BOOL CCitiesTable::Insert(const CITIES& recCities)
{
	CSession oSession;
	CDataSource oDataSource;

	if (!ConnectoToDb(oDataSource, oSession))
		return FALSE;

	CDBPropSet oUpdatePropSet = BuildUpdateDBPropSet();

	HRESULT hResult = S_FALSE;

	if (FAILED(hResult))
	{
		ATLTRACE(_T("Insert failed: 0x%X\n"), hResult);
	}

	return FALSE;
};

BOOL CCitiesTable::DeleteWhereID(const long lID)
{
	return false;
};
