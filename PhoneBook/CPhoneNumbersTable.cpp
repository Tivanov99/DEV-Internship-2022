#include "pch.h"
#include "CPhoneNumbersTable.h"
#include "ErrorVisualizator.h"


CPhoneNumbersTable::CPhoneNumbersTable(CSession& oSession)
	:CBaseTable(oSession,_T("PHONE_NUMBERS"))
{
};
CPhoneNumbersTable::~CPhoneNumbersTable() {};

bool CPhoneNumbersTable::DeleteWherePersonID(long lID)
{
	CString strQuery;
	strQuery.Format(_T("SELECT * FROM PHONE_NUMBERS WHERE PERSON_ID = %d"),lID);

	if (!ExecuteQuery(strQuery, AccessorTypes::Modifying))
	{
		ErrorMessageVisualizator::ShowErrorMessage(lpszErrorExecutingQuery, strQuery);
		return false;
	}

	if (MoveFirst() != S_OK)
	{
		ErrorMessageVisualizator::ShowErrorMessage(lpszErrorOpeningRecord, strQuery);
		return false;
	}

	if (FAILED(Delete()))
	{
		ErrorMessageVisualizator::ShowErrorMessage(lpszErrorDeletingRecord, NULL);
		return false;
	}

	return true;
}

bool CPhoneNumbersTable::SelectAllByPersonId(long lPersonID, CPhoneNumbersArray& oPhoneNumbersArray)
{
	CString strQuery;
	strQuery.Format(_T("SELECT * FROM PHONE_NUMBERS WHERE  PERSON_ID = %i"), lPersonID);
	// Изпълняваме командата
	if (!ExecuteQuery(strQuery, AccessorTypes::NoneModifying))
		return false;

	//TODO: CHECK HERE
	HRESULT hResult = MoveFirst();
	if (FAILED(hResult))
	{
		ErrorMessageVisualizator::ShowErrorMessage(lpszErrorOpeningRecord, NULL);
		return false;
	}

	// Прочитаме всички данни
	while (hResult != DB_S_ENDOFROWSET)
	{
		PHONE_NUMBERS* pCurrentPhoneNumber = new PHONE_NUMBERS;
		*pCurrentPhoneNumber = m_recTableRecord;
		oPhoneNumbersArray.Add(pCurrentPhoneNumber);

		hResult = MoveNext();

		if (FAILED(hResult) && hResult != DB_S_ENDOFROWSET)
		{
			ErrorMessageVisualizator::ShowErrorMessage(lpszErrorOpeningRecord, NULL);
			return false;
		}
		// Logic with the result
	}

	return true;
}