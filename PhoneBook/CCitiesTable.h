#include <atldbcli.h>
#include <iostream>

using namespace std;

#define CITY_NAME_SIZE	32
#define AREA_NAME_SIZE	32

/// <summary>
///  Дискова структура CITIES предназначена за таблицата 'CITIES'
/// </summary>
struct CITIES
{
	/// <summary>Променлива съдържаща първичен ключ от колоната 'ID' в таблицата 'CITIES'</summary>
	long lID;
	/// <summary>?</summary>
	long lUPDATE_COUNTER;
	/// <summary>Променлива съдържаща стойността от колона 'CITY_NAME' в таблицата 'CITIES'</summary>
	TCHAR szCITY_NAME[CITY_NAME_SIZE];
	/// <summary>Променлива съдържаща стойността от колона 'AREA_NAME' в таблицата 'CITIES'</summary>
	TCHAR szAREA_NAME[AREA_NAME_SIZE];
	/// <summary>Променлива съдържаща стойността от колона 'POSTAL_CODE' в таблицата 'CITIES'</summary>
	long lPOSTAL_CODE;

	CITIES()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};

class CCustomersAccessor
{
protected:
	CITIES m_recCustomer;

	BEGIN_ACCESSOR_MAP(CCustomersAccessor, 2)
		BEGIN_ACCESSOR(0, true)
		COLUMN_ENTRY(1, m_recCustomer.lID)
		END_ACCESSOR()

		BEGIN_ACCESSOR(1, true)
		COLUMN_ENTRY(2, m_recCustomer.lUpdateCounter)
		COLUMN_ENTRY(3, m_recCustomer.szCompanyName)
		COLUMN_ENTRY(4, m_recCustomer.szName)
		COLUMN_ENTRY(5, m_recCustomer.szAddress)
		COLUMN_ENTRY(6, m_recCustomer.szCountry)
		END_ACCESSOR()
	END_ACCESSOR_MAP()
};

/// <summary>Клас за работа с таблица CUSTOMERS</summary>
class CCustomersTable : private CCommand<CAccessor<CCustomersAccessor>>
{
public:
	BOOL LoadCustomers();
	BOOL UpdateCustomer();
};

BOOL CCustomersTable::LoadCustomers()
{
	CDataSource oDataSource;
	CSession oSession;

	CDBPropSet oDBPropSet(DBPROPSET_DBINIT);
	oDBPropSet.AddProperty(DBPROP_INIT_DATASOURCE, _T("SQLSERVER"));	// сървър
	oDBPropSet.AddProperty(DBPROP_AUTH_USERID, _T("sa"));			// потребител
	oDBPropSet.AddProperty(DBPROP_AUTH_PASSWORD, _T("sa"));			// парола
	oDBPropSet.AddProperty(DBPROP_INIT_CATALOG, _T("Northwind"));	// база данни
	oDBPropSet.AddProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO, false);
	oDBPropSet.AddProperty(DBPROP_INIT_LCID, 1033L);
	oDBPropSet.AddProperty(DBPROP_INIT_PROMPT, static_cast<short>(4));

	// Свързваме се към базата данни
	hResult = oDataSource.Open(_T("SQLOLEDB.1"), &oDBPropSet);
	if (FAILED(hResult))
	{
		Message(_T("Unable to connect to SQL Server database. Error: %d"), hResult);
		return FALSE;
	}

	// Отваряме сесия
	hResult = oSession.Open(oDataSource);
	if (FAILED(hResult))
	{
		Message(_T("Unable to open session. Error: %d"), hResult);
		oDataSource.Close();

		return FALSE;
	}

	// Конструираме заявката
	CString strQuery = _T("SELECT * FROM CUSTOMERS");

	// Изпълняваме командата
	hResult = Open(oSession, strQuery);
	if (FAILED(hResult))
	{
		Message(_T("Error executing query. Error: %d. Query: %s"), hResult, strQuery);

		oSession.Close();
		oDataSource.Close();

		return FALSE;
	}

	// Прочитаме всички данни
	while (MoveNext() == S_OK)
	{
		CString strCustomerData;
		strCustomerData.Format(_T("ID: %d, Company: %s, Contact Name: %s"),
			m_recCustomer.m_lID,
			m_recCustomer.m_szCompanyName,
			m_recCustomer.m_szName);

		// Logic with the result
	}

	// Затваряме командата, сесията и връзката с базата данни. 
	Close();
	oSession.Close();
	oDataSource.Close();

	return TRUE;
}

BOOL CCustomersTable::UpdateCustomer()
{
	CDataSource oDataSource;
	CSession oSession;

	CDBPropSet oDBPropSet(DBPROPSET_oDBPropSet);
	oDBPropSet.AddProperty(DBPROP_INIT_DATASOURCE, _T("SQLSERVER"));	// сървър
	oDBPropSet.AddProperty(DBPROP_AUTH_USERID, _T("sa"));			// потребител
	oDBPropSet.AddProperty(DBPROP_AUTH_PASSWORD, _T("sa"));			// парола
	oDBPropSet.AddProperty(DBPROP_INIT_CATALOG, _T("Northwind"));	// база данни
	oDBPropSet.AddProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO, false);
	oDBPropSet.AddProperty(DBPROP_INIT_LCID, 1033L);
	oDBPropSet.AddProperty(DBPROP_INIT_PROMPT, static_cast<short>(4));

	// Свързваме се към базата данни
	hResult = oDataSource.Open(_T("SQLOLEDB.1"), &oDBPropSet);
	if (FAILED(hResult))
	{
		Message(_T("Unable to connect to SQL Server database. Error: %d"), hResult);
		return FALSE;
	}

	// Отваряме сесия
	hResult = oSession.Open(oDataSource);
	if (FAILED(hResult))
	{
		Message(_T("Unable to open session. Error: %d"), hResult);
		oDataSource.Close();

		return FALSE;
	}

	// Конструираме заявката
	CString strQuery;
	strQuery.Format(_T("SELECT * FROM CUSTOMERS WHERE ID = %d"), 1);

	// Настройка на типа на Rowset-а
	CDBPropSet oUpdateDBPropSet(DBPROPSET_ROWSET);
	oUpdateDBPropSet.AddProperty(DBPROP_CANFETCHBACKWARDS, true);
	oUpdateDBPropSet.AddProperty(DBPROP_IRowsetScroll, true);
	oUpdateDBPropSet.AddProperty(DBPROP_IRowsetChange, true);
	oUpdateDBPropSet.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE);

	// Изпълняваме командата
	hResult = Open(oSession, strQuery, oUpdateDBPropSet);
	if (FAILED(hResult))
	{
		Message(_T("Error executing query. Error: %d. Query: %s"), hResult, strQuery);

		oSession.Close();
		oDataSource.Close();

		return FALSE;
	}

	hResult = MoveFirst();
	if (FAILED(hResult))
	{
		Message(_T("Error opening record. Error: %d. Query: %s"), hResult, strQuery);

		Close();
		oSession.Close();
		oDataSource.Close();

		return FALSE;
	}

	// ВЪПРОС: Какво стъпки следва да извършим преди да инкрементираме m_lUpdateCounter?

	m_recCustomer.m_lUpdateCounter++;

	hResult = SetData(1);
	if (FAILED(hResult))
	{
		Message(_T("Error updating record. Error: %d. Query: %s"), hResult, strQuery);

		Close();
		oSession.Close();
		oDataSource.Close();

		return FALSE;
	}

	Close();
	oSession.Close();
	oDataSource.Close();

	return TRUE;
}