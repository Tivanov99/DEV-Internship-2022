#include <atldbcli.h>
#include <iostream>
#include <afxcontrolbars.h>
#include <afxcontrolbars.h>

using namespace std;
namespace
{

#define CITY_NAME_SIZE	32
#define AREA_NAME_SIZE	32

	/// <summary>
	///  ������� ��������� CITIES ������������� �� ��������� 'CITIES'
	/// </summary>
	struct CITIES
	{
		/// <summary>���������� ��������� �������� ���� �� �������� 'ID' � ��������� 'CITIES'</summary>
		long lID;
		/// <summary>?</summary>
		long lUPDATE_COUNTER;
		/// <summary>���������� ��������� ���������� �� ������ 'CITY_NAME' � ��������� 'CITIES'</summary>
		TCHAR szCITY_NAME[CITY_NAME_SIZE];
		/// <summary>���������� ��������� ���������� �� ������ 'AREA_NAME' � ��������� 'CITIES'</summary>
		TCHAR szAREA_NAME[AREA_NAME_SIZE];
		/// <summary>���������� ��������� ���������� �� ������ 'POSTAL_CODE' � ��������� 'CITIES'</summary>
		long lPOSTAL_CODE;

		CITIES()
		{
			SecureZeroMemory(this, sizeof(*this));
		}
	};

	// <summary>type-def ����������� CTypedPtrArray ����� �������� CPtrArray ��������� � ��������� CITIES< / summary >
	typedef CTypedPtrArray < CPtrArray, CITIES*> CCitiesArray;

	class CCityAccessor
	{
	protected:
		CITIES m_recCITY;

		BEGIN_ACCESSOR_MAP(CCityAccessor, 2)
			BEGIN_ACCESSOR(0, true)
			COLUMN_ENTRY(1, m_recCITY.lID)
			END_ACCESSOR()

			BEGIN_ACCESSOR(1, true)
			COLUMN_ENTRY(2, m_recCITY.lUPDATE_COUNTER)
			COLUMN_ENTRY(3, m_recCITY.szCITY_NAME)
			COLUMN_ENTRY(4, m_recCITY.szAREA_NAME)
			COLUMN_ENTRY(5, m_recCITY.lPOSTAL_CODE)
			END_ACCESSOR()
		END_ACCESSOR_MAP()
	};

	/// <summary>���� �� ������ � ������� CITIES</summary>
	class CCitiesTable : private CCommand<CAccessor<CCityAccessor>>
	{
	private:
		BOOL ConnectoToDb(CDataSource& oDataSource, CSession& oSession, HRESULT& hResult);
		CDBPropSet BuildCDBPropSet();
		BOOL ExecuteQuery(HRESULT& hResult, CSession& oSession, CDataSource& oDataSource, CString& strQuery);
	public:
		BOOL SelectAll(CCitiesArray& oCitiesArray);
		BOOL SelectWhereID(const long lID, CITIES& recCities);
		BOOL UpdateWhereID(const long lID, const CITIES& recCities);
		BOOL Insert(const CITIES& recCities);
		BOOL DeleteWhereID(const long lID);

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
	BOOL CCitiesTable::ConnectoToDb(CDataSource& oDataSource, CSession& oSession, HRESULT& hResult)
	{
		CDBPropSet& oDBPropSet = BuildCDBPropSet();

		// ��������� �� ��� ������ �����
		hResult = oDataSource.Open(_T("SQLOLEDB"), &oDBPropSet);

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

	BOOL CCitiesTable::ExecuteQuery(HRESULT& hResult, CSession& oSession, CDataSource& oDataSource, CString& strQuery)
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

		BOOL bIsDbConnected = ConnectoToDb(oDataSource, oSession, hResult);
		if (!bIsDbConnected)
		{
			return FALSE;
		}

		// ������������ ��������
		CString strQuery = _T("SELECT * FROM CITIES");
		// ����������� ���������

		BOOL bIsQueryExecutedCorrectly = ExecuteQuery(hResult, oSession, oDataSource, strQuery);
		if (!bIsQueryExecutedCorrectly)
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
			// Logic with the result
		}

		// ��������� ���������, ������� � �������� � ������ �����. 
		Close();
		oSession.Close();
		oDataSource.Close();

		return TRUE;
	};

	BOOL CCitiesTable::SelectWhereID(const long lID, CITIES& recCities)
	{
		CDataSource oDataSource;
		CSession oSession;
		HRESULT hResult;

		BOOL bIsConnectedCorrectly = ConnectoToDb(oDataSource, oSession, hResult);
		if (!bIsConnectedCorrectly)
		{
			return FALSE;
		}

		CString strQuery;
		strQuery.Format(_T("SELECT * FROM CITIES WHERE ID = %d"), lID);

		BOOL bIsExecutedQueryCorrectly = ExecuteQuery(hResult, oSession, oDataSource, strQuery);
		if (!bIsExecutedQueryCorrectly)
		{
			return FALSE;
		}

		while (MoveNext()==S_OK())
		{
			CString strCustomerData;
			strCustomerData.Format(_T("ID: %d, City Name: %s, Area Name: %s, Postal Code: %d"),
				m_recCITY.lID,
				m_recCITY.szCITY_NAME,
				m_recCITY.szAREA_NAME,
				m_recCITY.lPOSTAL_CODE);

			recCities = m_recCITY;
		}
		Close();
		oSession.Close();
		oDataSource.Close();
		return TRUE;
	};

	BOOL CCitiesTable::UpdateWhereID(const long lID, const CITIES& recCities)
	{
		CDataSource oDataSource;
		CSession oSession;
		HRESULT hResult;

		BOOL IsCorrectlyConnectedToDb = ConnectoToDb(oDataSource,oSession,hResult);
		if (!IsCorrectlyConnectedToDb)
		{
			return FALSE;
		}
		

		// ������������ ��������
		CString strQuery;
		strQuery.Format(_T("SELECT * FROM CUSTOMERS WHERE ID = %d"), 1);

		// ��������� �� ���� �� Rowset-�
		CDBPropSet oUpdateDBPropSet(DBPROPSET_ROWSET);
		oUpdateDBPropSet.AddProperty(DBPROP_CANFETCHBACKWARDS, true);
		oUpdateDBPropSet.AddProperty(DBPROP_IRowsetScroll, true);
		oUpdateDBPropSet.AddProperty(DBPROP_IRowsetChange, true);
		oUpdateDBPropSet.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE);

		// ����������� ���������
		HRESULT hResult = Open(oSession, strQuery, oUpdateDBPropSet);
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

			Close();
			oSession.Close();
			oDataSource.Close();

			return FALSE;
		}

		// ������: ����� ������ ������ �� �������� ����� �� �������������� m_lUpdateCounter?

		m_recCITY.lUPDATE_COUNTER++;

		hResult = SetData(1);
		if (FAILED(hResult))
		{
			wprintf(_T("Error updating record. Error: %d. Query: %s"), hResult, strQuery);

			Close();
			oSession.Close();
			oDataSource.Close();

			return FALSE;
		}

		Close();
		oSession.Close();
		oDataSource.Close();

		return TRUE;
	};

	BOOL CCitiesTable::Insert(const CITIES& recCities)
	{
		return false;

	};
	BOOL CCitiesTable::DeleteWhereID(const long lID)
	{
		return false;

	};

}
