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

#define NoneModifyColumnCode 0
#define ModifyColumnCode 1
	class CCityAccessor
	{
	protected:
		CCityAccessor()
		{

		};
		~CCityAccessor()
		{

		};
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
		BOOL ConnectoToDb(CDataSource& oDataSource, CSession& oSession);
		CDBPropSet BuildCDBPropSet();
		CDBPropSet BuildUpdateDBPropSet();
		BOOL ExecuteQuery(HRESULT& hResult, CSession& oSession, CDataSource& oDataSource, const CString& strQuery);
		void CloseConnection(CDataSource& oDataSource, CSession& oSession);
	public:
		CCitiesTable()
		{

		};
		~CCitiesTable()
		{

		};
		BOOL SelectAll(CCitiesArray& oCitiesArray);
		BOOL SelectWhereID(const long lID, CITIES& recCities);
		BOOL UpdateWhereID(const long lID, const CITIES& recCities);
		BOOL Insert(const CITIES& recCities);
		BOOL DeleteWhereID(const long lID);


	};
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
			CITIES* pCurrentCity= new CITIES;
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


		// ������: ����� ������ ������ �� �������� ����� �� �������������� m_lUpdateCounter?

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
		HRESULT oHresult;
		CDataSource oDataSource;

		if (!ConnectoToDb(oDataSource, oSession, oHresult))
			return FALSE;

		CString strQuery;
		strQuery.Format(_T("INSERT INTO CITIES (%s[CITY_NAME],%s[AREA_NAME],%d[POSTAL_CODE], %d[UPDATE_COUNTER])"),
			"Smolqn", "Smolqn", 3333, 0);

		CDBPropSet oUpdatePropSet = BuildUpdateDBPropSet();

		oHresult = Open(oSession, strQuery, &oUpdatePropSet);

		if (FAILED(oHresult))
		{
			wprintf(_T("Error executing query. Error: %d. Query: %s"), oHresult, strQuery);

			oSession.Close();
			oDataSource.Close();

			return FALSE;
		}

		return FALSE;
	};
	BOOL CCitiesTable::DeleteWhereID(const long lID)
	{
		return false;

	};

}
