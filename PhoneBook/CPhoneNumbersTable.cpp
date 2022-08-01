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

}