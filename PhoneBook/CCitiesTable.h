#include <atldbcli.h>
#include <iostream>
#include <afxcontrolbars.h>
#include <afxcontrolbars.h>
#include "Structures.h"

using namespace std;

#define NoneModifyColumnCode 0
#define ModifyColumnCode 1
class CCityAccessor
{
protected:
	CCityAccessor() {

	};
	~CCityAccessor() {

	};
	CITIES m_recCITY;

	BEGIN_ACCESSOR_MAP(CCityAccessor, 2)
		BEGIN_ACCESSOR(NoneModifyColumnCode, true)
		COLUMN_ENTRY(1, m_recCITY.lID)
		END_ACCESSOR()

		BEGIN_ACCESSOR(ModifyColumnCode, true)
		COLUMN_ENTRY(2, m_recCITY.lUPDATE_COUNTER)
		COLUMN_ENTRY(3, m_recCITY.szCITY_NAME)
		COLUMN_ENTRY(4, m_recCITY.szAREA_NAME)
		COLUMN_ENTRY(5, m_recCITY.lPOSTAL_CODE)
		END_ACCESSOR()
	END_ACCESSOR_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CCitiesTable

/// <summary>���� �� ������ � ������� CITIES</summary>
class CCitiesTable : private CCommand<CAccessor<CCityAccessor>>
{
private:
	static const LPCSTR lpszSelectAllById;
	const CString strSelectAll = _T("SELECT * FROM CITIES");
	const CString strEmptySelect = _T("SELECT TOP 0 * FROM CITIES");
	const CString strUnableToConnectServer = _T("Unable to connect to SQL Server database. Error: %d");
	const CString strUnableToOpenSession = _T("Unable to open session. Error: %d");
	const CString strErrorExecutingQuery = _T("Error executing query.Error:% d.Query : % s");
	const CString strErrorOpeningRecord = _T("Error opening record.Error:% d");
	const CString strErrorUpdatingRecord = _T("Error updating record.Error:% d.Query : % s");
	const CString strErrorDeletingRecord = _T("Delete failed: 0x%X\n");
	const CString strErrorInsertingRecord = _T("Insert failed: 0x%X\n");

public:
	CCitiesTable();
	~CCitiesTable();
	
	// Methods
	// -------------
public:
	/// <summary>
	///  ������� ����� ���� ����� ������ �� ��������� "CITIES" � �� ������ � ������� ���� �������� �����.
	/// </summary>
	/// <param name="oCitiesArray">����� � ����� �� ����� �������� ������ ��������� �����.</param>
	bool SelectAll(CCitiesArray& oCitiesArray);

	/// <summary>
	///  ������� ����� ���� ����� �� ��������� "CITIES" ����� ID �������� �� "lID" � �� ���������� � "recCities" ���������.
	/// </summary>
	/// <param name="lID">�������� ������������� ���� ����� �� �� ����� ����� � ������.</param>
	/// <param name="recCities">���������� ����� �� ������� ��������� �� ���������</param>
	bool SelectWhereID(const long lID, CITIES& recCities);

	/// <summary>
	///  ������� ����� ����� ������� �� ����� �� ��������� "CITIES" ����� ID �������� �� "lID" ���������,
	///  � �� ������� ��������� �� ��������� "recCities" � ������ �������� �� ������.
	/// </summary>
	/// <param name="lID">�������� ������������� ���� ����� �� �� ����� ����� � ������.</param>
	/// <param name="recCities">���������� ����� ������� ���� ����������� �����.</param>
	bool UpdateWhereID(const long lID, const CITIES& recCities);

	/// <summary>
	///  ������� ����� ������ ����� ������� ���� �������� ��� ��������� "CITIES".
	/// </summary>
	/// <param name="recCities">���������� ����� ������� ��� �����.</param>
	bool Insert(const CITIES& recCities);

	/// <summary>
	///  ������� ����� ������� ����� �� ��������� "CITIES" ����� �������� �� "lID" ���������.
	/// </summary>
	/// <param name="lID">�������� ������������� ���� ����� �� �� ����� ����� � ������.</param>
	bool DeleteWhereID(const long lID);

private:
	/// <summary>
	///  ������� ����� ������ ����� � ������ ��� ������.
	/// </summary>
	/// <param name="oDataSource">����� ������ �� �������� �� ������.</param> 
	/// <param name="oSession">����� ������ �� �������� �� ������.</param> 
	bool OpenSessionAndConnectionToDb(CDataSource& oDataSource, CSession& oSession);

	/// <summary>
	///  ������� ����� ������� ���-���.
	/// </summary>
	CDBPropSet GetDBPropSet() const;

	/// <summary>
	///  ������� ����� ������� ���-��� ������������ �� ������������ �� �����.
	/// </summary>
	CDBPropSet GetModifyDBPropSet() const;

	/// <summary>
	///  ������� ����� ��������� ������ ������ ��� �������� ������.
	/// </summary>
	/// <param name="hResult">����� �������� �������� ��������� �� ��������</param> 
	/// <param name="oSession">����� ���� ����� �� ������� �������� ��� ������.</param> 
	/// <param name="strQuery">����� �������� �������� ������.</param> 
	bool ExecuteNoneModifyQuery(HRESULT& hResult, CSession& oSession, const CString& strQuery);

	/// <summary>
	///  ������� ����� ��������� ������ ������ ��� �������� ������.
	/// </summary>
	/// <param name="hResult">����� �������� �������� ��������� �� ��������</param> 
	/// <param name="oSession">����� ���� ����� �� ������� �������� ��� ������.</param> 
	/// <param name="strQuery">����� �������� �������� ������.</param> 
	bool ExecuteModifyQuery(HRESULT& hResult, CSession& oSession, const CString& strQuery, CDBPropSet oPropSet);

	/// <summary>
	///  ������� ����� ������� �������� ��� ������.
	/// </summary>
	/// <param name="oSession">����� ���� ����� �� �� ������� �������� ��� ������.</param> 
	/// <param name="oDataSource">����� ���� ����� �� �� ������� �������� ��� ������.</param> 
	void CloseSessionAndConnection(CDataSource& oDataSource, CSession& oSession);

	/// <summary>
	///  ������� ����� ������� ��������� ��� ��������� ���� �� ��������� �� �������� �� ������.
	/// </summary>
	/// <param name="hResult">����� �������� ����������� �� ������������ ������.</param> 
	/// <param name="strErrorMessage">����� ����� ������� �������� ���������� �� �������� ������.</param>  
	/// <param name="strQuery">����� ����� ������� �������� ������.</param> 
	void ShowErrorMessage(const CString& strErrorMessage, const CString& strQuery = NULL);

	// Overrides
	// -------------

	// Members
	// -------------

};
