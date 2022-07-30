#include "pch.h"
#include "CPersonsTable.h"
#include "CBaseTable.cpp"


const LPCSTR CPersonsTable::lpszSelectAllById = "SELECT * FROM PERSONS WHERE ID = %d";
const LPCSTR CPersonsTable::lpszSelectAll = "SELECT * FROM PERSONS";
const LPCSTR CPersonsTable::lpszEmptySelect = "SELECT TOP 0 * FROM PERSONS";

/////////////////////////////////////////////////////////////////////////////
// CPersonsTable

CPersonsTable::CPersonsTable()
{};
CPersonsTable::~CPersonsTable()
{
};

void CPersonsTable::CloseDbConnectionAndSession()
{
	Close();
	m_oSession.Close();
	m_oDataSource.Close();
};

bool CPersonsTable::ExecuteQuery(const CString& strQuery, const int nQueryAccessor)
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

bool CPersonsTable::SelectAll(CPersonsArray& oPersonsPtrArray)
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
		ShowErrorMessage(lpszErrorOpeningRecord, NULL);
		CloseDbConnectionAndSession();
		return false;
	}

	// Прочитаме всички данни
	while (hResult != DB_S_ENDOFROWSET)
	{
		PERSONS* pCurrentPerson = new PERSONS;
		*pCurrentPerson = m_recPERSON;
		oPersonsPtrArray.Add(pCurrentPerson);

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

bool CPersonsTable::SelectWhereID(const long lID, PERSONS& recPersons)
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
	recPersons = m_recPERSON;

	CloseDbConnectionAndSession();
	return true;
};


bool CPersonsTable::UpdateWhereID(const long lID, const PERSONS& recPersons)
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

	if (recPersons.lUpdateCounter != m_recPERSON.lUpdateCounter)
	{
		ShowErrorMessage(lpszInvalidRecordVersion, NULL);
		return false;
	}

	m_recPERSON.lUpdateCounter++;
	m_recPERSON = recPersons;

	if (FAILED(SetData(ModifyColumnCode)))
	{
		ShowErrorMessage(lpszErrorUpdatingRecord, NULL);
		CloseDbConnectionAndSession();
		return false;
	}

	CloseDbConnectionAndSession();
	return true;
};

bool CPersonsTable::Insert(const PERSONS& recPersons)
{
	if (!OpenDbConnectionAndSession())
		return false;

	if (!ExecuteQuery((CString)lpszEmptySelect, ModifyColumnCode))
	{
		ShowErrorMessage(lpszErrorExecutingQuery, (CString)lpszEmptySelect);
		CloseDbConnectionAndSession();
		return false;
	}

	m_recPERSON = recPersons;

	if (FAILED(__super::Insert(ModifyColumnCode)))
	{
		ShowErrorMessage(lpszErrorInsertingRecord, NULL);
		CloseDbConnectionAndSession();
		return false;
	}

	CloseDbConnectionAndSession();
	return true;
};

bool CPersonsTable::DeleteWhereID(const long lID)
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