#include "pch.h"
#include "CCitiesTable.h"


const LPCSTR CCitiesTable::lpszSelectAllById = "SELECT * FROM CITIES WHERE ID = %d";
const LPCSTR CCitiesTable::lpszSelectAll = "SELECT * FROM CITIES";
const LPCSTR CCitiesTable::lpszEmptySelect = "SELECT TOP 0 * FROM CITIES";

/////////////////////////////////////////////////////////////////////////////
// CCitiesTable

CCitiesTable::CCitiesTable()
{};
CCitiesTable::~CCitiesTable()
{
};

void CCitiesTable::CloseDbConnectionAndSession()
{
	Close();
	m_oSession.Close();
	m_oDataSource.Close();
};

bool CCitiesTable::ExecuteQuery(const CString& strQuery, const int nQueryAccessor)
{
	if (nQueryAccessor != NoneModifyColumnCode && nQueryAccessor != ModifyColumnCode)
	{
		ShowErrorMessage(lpszErrorInvalidQueryAcessor, strQuery);
		return false;
	}
	if (nQueryAccessor == NoneModifyColumnCode)
	{
		//изпълняваме команда
		if (FAILED(Open(m_oSession, strQuery)))
		{
			ShowErrorMessage(lpszErrorExecutingQuery, strQuery);
			return false;
		}
	}
	else if (nQueryAccessor == ModifyColumnCode)
	{
		//настройваме row-set
		CDBPropSet oUpdateDBPropSet = GetModifyDBPropSet();
		//изпълняваме команда
		if (FAILED(Open(m_oSession, strQuery, &oUpdateDBPropSet)))
		{
			ShowErrorMessage(lpszErrorExecutingQuery, strQuery);
			return false;
		}
	}
	return true;
}

bool CCitiesTable::SelectAll(CSelfClearingTypedPtrArray<CITIES>& oCitiesPtrArray)
{
	if (!OpenDbConnectionAndSession())
		return false;

	// Изпълняваме командата
	if (!ExecuteQuery((CString)lpszSelectAll, NoneModifyColumnCode))
	{
		CloseDbConnectionAndSession();
		return false;
	}

	//TODO: CHECK HERE
	HRESULT hResult = MoveFirst();
	if (FAILED(hResult))
	{
		ShowErrorMessage(lpszErrorOpeningRecord,NULL);
		CloseDbConnectionAndSession();
		return false;
	}

	// Прочитаме всички данни
	while (hResult != DB_S_ENDOFROWSET)
	{
		CITIES* pCurrentCity = new CITIES;
		*pCurrentCity = m_recCITY;
		oCitiesPtrArray.Add(pCurrentCity);

		hResult = MoveNext();

		if (FAILED(hResult) && hResult != DB_S_ENDOFROWSET)
		{
			ShowErrorMessage(lpszErrorOpeningRecord, NULL);
			CloseDbConnectionAndSession();
			return false;
		}
		// Logic with the result
	}

	// Затваряме командата, сесията и връзката с базата данни. 
	CloseDbConnectionAndSession();

	return true;
};

bool CCitiesTable::SelectWhereID(const long lID, CITIES& recCities)
{
	if (!OpenDbConnectionAndSession())
		return false;

	CString strQuery;
	strQuery.Format((CString)lpszSelectAllById, lID);

	if (!ExecuteQuery(strQuery, NoneModifyColumnCode))
	{
		CloseDbConnectionAndSession();
		return false;
	}

	if (FAILED(MoveFirst()))
	{
		ShowErrorMessage(lpszErrorOpeningRecord, NULL);
		CloseDbConnectionAndSession();
		return false;
	}
	recCities = m_recCITY;

	CloseDbConnectionAndSession();
	return true;
};

bool CCitiesTable::UpdateWhereID(const long lID, const CITIES& recCities)
{
	if (!OpenDbConnectionAndSession())
		return false;

	// Конструираме заявката
	CString strQuery;
	strQuery.Format((CString)lpszSelectAllById, lID);

	// Изпълняваме командата
	if (!ExecuteQuery(strQuery, ModifyColumnCode))
	{
		CloseDbConnectionAndSession();
		return false;
	}

	if (FAILED(MoveFirst()))
	{
		ShowErrorMessage(lpszErrorOpeningRecord, strQuery);
		CloseDbConnectionAndSession();
		return false;
	}

	if (recCities.lUpdateCounter != m_recCITY.lUpdateCounter)
	{
		ShowErrorMessage(lpszInvalidRecordVersion, NULL);
		return false;
	}

	m_recCITY.lUpdateCounter++;
	m_recCITY = recCities;

	if (FAILED(SetData(ModifyColumnCode)))
	{
		ShowErrorMessage(lpszErrorUpdatingRecord, NULL);
		CloseDbConnectionAndSession();
		return false;
	}

	CloseDbConnectionAndSession();
	return true;
};

bool CCitiesTable::Insert(const CITIES& recCities)
{
	if (!OpenDbConnectionAndSession())
		return false;

	if (!ExecuteQuery((CString)lpszEmptySelect, ModifyColumnCode))
	{
		ShowErrorMessage(lpszErrorExecutingQuery, (CString)lpszEmptySelect);
		CloseDbConnectionAndSession();
		return false;
	}

	m_recCITY = recCities;

	if (FAILED(__super::Insert(ModifyColumnCode)))
	{
		ShowErrorMessage(lpszErrorInsertingRecord, NULL);
		CloseDbConnectionAndSession();
		return false;
	}

	CloseDbConnectionAndSession();
	return true;
};

bool CCitiesTable::DeleteWhereID(const long lID)
{
	if (!OpenDbConnectionAndSession())
		return false;

	// Конструираме заявката
	CString strQuery;
	strQuery.Format((CString)lpszSelectAllById, lID);

	// Изпълняваме командата
	if (!ExecuteQuery(strQuery, ModifyColumnCode))
	{
		ShowErrorMessage(lpszErrorExecutingQuery, strQuery);
		CloseDbConnectionAndSession();
		return false;
	}

	if (MoveFirst() != S_OK)
	{
		ShowErrorMessage(lpszErrorOpeningRecord, strQuery);
		CloseDbConnectionAndSession();
		return false;
	}

	if (FAILED(Delete()))
	{
		ShowErrorMessage(lpszErrorDeletingRecord, NULL);
		CloseDbConnectionAndSession();
		return false;
	}
	CloseDbConnectionAndSession();

	return true;
};

