#include <atldbcli.h>
#include <iostream>
#include <afxcontrolbars.h>
#include <afxcontrolbars.h>
#include "Structures.h"
#include "CSelfClearingTypedPtrArray.h"


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
	static const LPCSTR lpszSelectAll;   
	static const LPCSTR lpszEmptySelect;
	static const LPCSTR lpszUnableToConnectServer;
	static const LPCSTR lpszUnableToOpenSession ;
	static const LPCSTR lpszErrorExecutingQuery;
	static const LPCSTR lpszErrorInvalidQueryAcessor;
	static const LPCSTR lpszErrorOpeningRecord;
	static const LPCSTR lpszErrorUpdatingRecord;
	static const LPCSTR lpszErrorDeletingRecord;
	static const LPCSTR lpszErrorInsertingRecord;
	static const LPCSTR lpszInvalidRecordVersion;

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
	bool SelectAll(CSelfClearingTypedPtrArray<CITIES>& oCitiesArray);

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
	bool OpenDbConnectionAndSession();

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
	/// <param name="strQuery">����� �������� �������� ������.</param> 
	/// <param name="nQueryAccessor">
		///����������� ����� ����� �������� ���� ��
		/// �� ����������� ������� ��� ��. 0 - �� ��������� / 1 ����������.
	/// </param>  
	bool ExecuteQuery(const CString& strQuery,const int nQueryAccessor);

	/// <summary>
	///  ������� ����� ������� �������� ��� ������.
	/// </summary>
	void CloseDbConnectionAndSession();

	/// <summary>
	///  ������� ����� ������� ��������� ��� ��������� ���� �� ��������� �� �������� �� ������.
	/// </summary>
	/// <param name="hResult">����� �������� ����������� �� ������������ ������.</param> 
	/// <param name="strErrorMessage">����� ����� ������� �������� ���������� �� �������� ������.</param>  
	/// <param name="strQuery">����� ����� ������� �������� ������.</param> 
	void ShowErrorMessage(const LPCSTR strErrorMessage, const CString& strQuery = NULL);

	// Overrides
	// -------------

	// Members
	// -------------
	CDataSource m_oDataSource;
	CSession m_oSession;
};
