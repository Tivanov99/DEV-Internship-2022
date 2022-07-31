#include "pch.h"
#include "CPhoneNumbersTable.h"
#include "CBaseTable.cpp"

const LPCSTR CPhoneNumbersTable::lpszSelectById = "SELECT * FROM PHONE_NUMBERS WHERE ID = %d";
const LPCSTR CPhoneNumbersTable::lpszSelectAllByPersonId = "SELECT * FROM PHONE_NUMBERS WHERE PERSON_ID = %d";
const LPCSTR CPhoneNumbersTable::lpszSelectAll = "SELECT * FROM PHONE_NUMBERS";
const LPCSTR CPhoneNumbersTable::lpszEmptySelect = "SELECT TOP 0 * FROM PHONE_NUMBERS";


CPhoneNumbersTable::CPhoneNumbersTable() {};
CPhoneNumbersTable::~CPhoneNumbersTable() {};

bool CPhoneNumbersTable::SelectAllByPersonId(long lID, CPhoneNumbersArray& oPhoneNumbersArray)
{
	if (!OpenDbConnectionAndSession())
		return false;

	CString strQuery;
	strQuery.Format((CString)lpszSelectAllByPersonId, lID);

	if (!ExecuteQuery(strQuery, AccessorTypes::NoneModifying))
	{
		CloseDbConnectionAndSession();
		return false;
	}

	HRESULT hResult = MoveFirst();
	if (FAILED(hResult))
	{
		ShowErrorMessage(lpszErrorOpeningRecord, NULL);
		CloseDbConnectionAndSession();
		return false;
	}

	while (hResult != DB_S_ENDOFROWSET)
	{
		PHONE_NUMBERS* pCurrentPhoneNumber = new PHONE_NUMBERS;
		*pCurrentPhoneNumber = m_recPhoneNumber;
		oPhoneNumbersArray.Add(pCurrentPhoneNumber);

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
}

bool CPhoneNumbersTable::SelectAll(CPhoneNumbersArray& oPhoneNumbersArray)
{
	if (!OpenDbConnectionAndSession())
		return false;

	// Изпълняваме командата
	if (!ExecuteQuery((CString)lpszSelectAll, AccessorTypes::NoneModifying))
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
		PHONE_NUMBERS* pCurrentPhoneNumber = new PHONE_NUMBERS;
		*pCurrentPhoneNumber = m_recPhoneNumber;
		oPhoneNumbersArray.Add(pCurrentPhoneNumber);

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
}

bool CPhoneNumbersTable::SelectWhereID(const long lID, PHONE_NUMBERS& recPhoneNumber)
{
	if (!OpenDbConnectionAndSession())
		return false;

	CString strQuery;
	strQuery.Format((CString)lpszSelectById, lID);

	if (!ExecuteQuery(strQuery, AccessorTypes::NoneModifying))
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
	recPhoneNumber = m_recPhoneNumber;

	CloseDbConnectionAndSession();
	return true;
};

bool CPhoneNumbersTable::UpdateWhereID(const long lID, const PHONE_NUMBERS& recPhoneNumber)
{
	if (!OpenDbConnectionAndSession())
		return false;

	// Конструираме заявката
	CString strQuery;
	strQuery.Format((CString)lpszSelectById, lID);

	// Изпълняваме командата
	if (!ExecuteQuery(strQuery, AccessorTypes::Modifying))
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

	if (recPhoneNumber.lUpdateCounter != m_recPhoneNumber.lUpdateCounter)
	{
		ShowErrorMessage(lpszInvalidRecordVersion, NULL);
		return false;
	}

	m_recPhoneNumber.lUpdateCounter++;
	m_recPhoneNumber = recPhoneNumber;

	if (FAILED(SetData(ModifyColumnCode)))
	{
		ShowErrorMessage(lpszErrorUpdatingRecord, NULL);
		CloseDbConnectionAndSession();
		return false;
	}

	CloseDbConnectionAndSession();
	return true;
};

bool CPhoneNumbersTable::Insert(const PHONE_NUMBERS& recPhoneNumber)
{
	if (!OpenDbConnectionAndSession())
		return false;

	if (!ExecuteQuery((CString)lpszEmptySelect, AccessorTypes::Modifying))
	{
		ShowErrorMessage(lpszErrorExecutingQuery, (CString)lpszEmptySelect);
		CloseDbConnectionAndSession();
		return false;
	}

	m_recPhoneNumber = recPhoneNumber;

	if (FAILED(__super::Insert(ModifyColumnCode)))
	{
		ShowErrorMessage(lpszErrorInsertingRecord, NULL);
		CloseDbConnectionAndSession();
		return false;
	}

	CloseDbConnectionAndSession();
	return true;
};

bool CPhoneNumbersTable::DeleteWhereID(const long lID)
{
	if (!OpenDbConnectionAndSession())
		return false;

	// Конструираме заявката
	CString strQuery;
	strQuery.Format((CString)lpszSelectById, lID);

	// Изпълняваме командата
	if (!ExecuteQuery(strQuery, AccessorTypes::Modifying))
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


bool CPhoneNumbersTable::DeleteWherePersonID(const long lID)
{
	if (!OpenDbConnectionAndSession())
		return false;

	// Конструираме заявката
	CString strQuery;
	strQuery.Format((CString)lpszSelectAllByPersonId, lID);

	// Изпълняваме командата
	if (!ExecuteQuery(strQuery, AccessorTypes::Modifying))
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
}

void CPhoneNumbersTable::CloseDbConnectionAndSession()
{
	Close();
	m_oSession.Close();
	m_oDataSource.Close();
};

bool CPhoneNumbersTable::ExecuteQuery(const CString& strQuery, AccessorTypes eQueryAccessor)
{
	bool bResult = false;
	switch (eQueryAccessor)
	{
	case AccessorTypes::NoneModifying:
		FAILED(Open(m_oSession, strQuery)) ?
			ShowErrorMessage(lpszErrorExecutingQuery, strQuery) :
			bResult = true;
		break;

	case AccessorTypes::Modifying:
		FAILED(Open(m_oSession, strQuery, &GetModifyDBPropSet())) ?
			ShowErrorMessage(lpszErrorExecutingQuery, strQuery) :
			bResult = true;
		break;

	default:
		ShowErrorMessage(lpszErrorInvalidQueryAcessor, strQuery);
		break;
	}
	return bResult;
}