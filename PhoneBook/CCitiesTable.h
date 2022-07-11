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
public:
	CCitiesTable();
	~CCitiesTable();

public:
	/// <summary>
	///  ������� ����� ���� ����� ������ �� ��������� "CITIES" � �� ������ � ������� ���� �������� �����.
	/// </summary>
	/// <param name="oCitiesArray">����� � ����� �� ����� �������� ������ ��������� �����.</param>
	BOOL SelectAll(CCitiesArray& oCitiesArray);

	/// <summary>
	///  ������� ����� ���� ����� �� ��������� "CITIES" ����� ID �������� �� "lID" � �� ���������� � "recCities" ���������.
	/// </summary>
	/// <param name="lID">�������� ������������� ���� ����� �� �� ����� ����� � ������.</param>
	/// <param name="recCities">���������� ����� �� ������� ��������� �� ���������</param>
	BOOL SelectWhereID(const long lID, CITIES& recCities);

	/// <summary>
	///  ������� ����� ����� ������� �� ����� �� ��������� "CITIES" ����� ID �������� �� "lID" ���������,
	///  � �� ������� ��������� �� ��������� "recCities" � ������ �������� �� ������.
	/// </summary>
	/// <param name="lID">�������� ������������� ���� ����� �� �� ����� ����� � ������.</param>
	/// <param name="recCities">���������� ����� ������� ���� ����������� �����.</param>
	BOOL UpdateWhereID(const long lID, const CITIES& recCities);

	/// <summary>
	///  ������� ����� ������ ����� ������� ���� �������� ��� ��������� "CITIES".
	/// </summary>
	/// <param name="recCities">���������� ����� ������� ��� �����.</param>
	BOOL Insertt(const CITIES& recCities);

	/// <summary>
	///  ������� ����� ������� ����� �� ��������� "CITIES" ����� �������� �� "lID" ���������.
	/// </summary>
	/// <param name="lID">�������� ������������� ���� ����� �� �� ����� ����� � ������.</param>
	BOOL DeleteWhereID(const long lID);

private:
	/// <summary>
	///  ������� ����� ������ ������ ��� ������.
	/// </summary>
	/// <param name="oDataSource">����� ������ �� �������� �� ������.</param> 
	/// <param name="oSession">����� ������ �� �������� �� ������.</param> 
	BOOL ConnectoToDb(CDataSource& oDataSource, CSession& oSession);

	/// <summary>
	///  ������� ����� ������� ���-���.
	/// </summary>
	CDBPropSet BuildCDBPropSet();

	/// <summary>
	///  ������� ����� ������� ���-��� ������������ �� ������������ �� �����.
	/// </summary>
	CDBPropSet BuildUpdateDBPropSet();

	/// <summary>
	///  ������� ����� ��������� ������ ������ ��� �������� ������.
	/// </summary>
	/// <param name="hResult">����� �������� �������� ��������� �� ��������</param> 
	/// <param name="oSession">����� ���� ����� �� ������� �������� ��� ������.</param> 
	/// <param name="oDataSource">����� ���� ����� �� �� ������� �������� ��� ������.</param> 
	/// <param name="strQuery">����� �������� �������� ������.</param> 
	BOOL ExecuteNoneModifyQuery(HRESULT& hResult, CSession& oSession, CDataSource& oDataSource, const CString& strQuery);

	/// <summary>
	///  ������� ����� ������� �������� ��� ������.
	/// </summary>
	/// <param name="oSession">����� ���� ����� �� �� ������� �������� ��� ������.</param> 
	/// <param name="oDataSource">����� ���� ����� �� �� ������� �������� ��� ������.</param> 
	void CloseConnection(CDataSource& oDataSource, CSession& oSession);

	/// <summary>
	///  ������� ����� ������� ��������� ��� ��������� ���� �� ���������� �� ������, � ������� ��������.
	/// </summary>
 	/// <param name="hResult">����� �������� ����������� �� ������������ ������.</param> 
	/// <param name="oSession">����� ���� ����� �� �� ������� �������� ��� ������.</param> 
	/// <param name="oDataSource">����� ���� ����� �� �� ������� �������� ��� ������.</param> 
	/// <param name="strQuery">����� ����� ������� �������� ������.</param> 
	void ErrorExecutingQuery(const CString strQuery, const HRESULT& hResult, CDataSource oDataSource, CSession oSession);

	/// <summary>
	///  ������� ����� ������� ��������� ��� ��������� ���� �� ��������� �� �������� �� ������, � ������� ��������.
	/// </summary>
	/// <param name="hResult">����� �������� ����������� �� ������������ ������.</param> 
	/// <param name="oSession">����� ���� ����� �� �� ������� �������� ��� ������.</param> 
	/// <param name="oDataSource">����� ���� ����� �� �� ������� �������� ��� ������.</param> 
	/// <param name="strQuery">����� ����� ������� �������� ������.</param> 
	void ErrorOpeningRecord(const CString strQuery, const HRESULT& hResult, CDataSource oDataSource, CSession oSession);
};
