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
	CCityAccessor()
	{

	};
	~CCityAccessor()
	{

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

/// <summary>Клас за работа с таблица CITIES</summary>
class CCitiesTable : private CCommand<CAccessor<CCityAccessor>>
{
public:
	CCitiesTable()
	{

	};
	~CCitiesTable()
	{

	};

public:
	BOOL SelectAll(CCitiesArray& oCitiesArray);
	BOOL SelectWhereID(const long lID, CITIES& recCities);
	BOOL UpdateWhereID(const long lID, const CITIES& recCities);
	BOOL Insert(const CITIES& recCities);
	BOOL DeleteWhereID(const long lID);


private:
	BOOL ConnectoToDb(CDataSource& oDataSource, CSession& oSession);
	CDBPropSet BuildCDBPropSet();
	CDBPropSet BuildUpdateDBPropSet();
	BOOL ExecuteQuery(HRESULT& hResult, CSession& oSession, CDataSource& oDataSource, const CString& strQuery);
	void CloseConnection(CDataSource& oDataSource, CSession& oSession);
};
