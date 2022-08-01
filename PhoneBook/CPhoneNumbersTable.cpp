#include "pch.h"
#include "CPhoneNumbersTable.h"
#include "CBaseTable.cpp"
#include "ErrorVisualizator.h"

//const LPCSTR CPhoneNumbersTable::lpszSelectById = "SELECT * FROM PHONE_NUMBERS WHERE ID = %d";
//const LPCSTR CPhoneNumbersTable::lpszSelectAllByPersonId = "SELECT * FROM PHONE_NUMBERS WHERE PERSON_ID = %d";
//const LPCSTR CPhoneNumbersTable::lpszSelectAll = "SELECT * FROM PHONE_NUMBERS";
//const LPCSTR CPhoneNumbersTable::lpszEmptySelect = "SELECT TOP 0 * FROM PHONE_NUMBERS";


CPhoneNumbersTable::CPhoneNumbersTable(CSession& oSession)
	:CBaseTable(oSession,_T("PHONE_NUMBERS"))
{
};
CPhoneNumbersTable::~CPhoneNumbersTable() {};

//bool CPhoneNumbersTable::SelectAllByPersonId(long lID, CPhoneNumbersArray& oPhoneNumbersArray)
//{
//	CString strQuery;
//	strQuery.Format((CString)lpszSelectAllByPersonId, lID);
//
//	if (!ExecuteQuery(strQuery, AccessorTypes::NoneModifying))
//		return false;
//
//	HRESULT hResult = MoveFirst();
//	if (FAILED(hResult))
//	{
//		ErrorMessageVisualizator::ShowErrorMessage(lpszErrorOpeningRecord, NULL);
//		return false;
//	}
//
//	while (hResult != DB_S_ENDOFROWSET)
//	{
//		PHONE_NUMBERS* pCurrentPhoneNumber = new PHONE_NUMBERS;
//		*pCurrentPhoneNumber = m_recPhoneNumber;
//		oPhoneNumbersArray.Add(pCurrentPhoneNumber);
//
//		hResult = MoveNext();
//
//		if (FAILED(hResult) && hResult != DB_S_ENDOFROWSET)
//		{
//			ErrorMessageVisualizator::ShowErrorMessage(lpszErrorOpeningRecord, NULL);
//			return false;
//		}
//		// Logic with the result
//	}
//
//	return true;
//}
//
//bool CPhoneNumbersTable::SelectAll(CPhoneNumbersArray& oPhoneNumbersArray)
//{
//	// Изпълняваме командата
//	if (!ExecuteQuery((CString)lpszSelectAll, AccessorTypes::NoneModifying))
//		return false;
//
//	//TODO: CHECK HERE
//	HRESULT hResult = MoveFirst();
//	if (FAILED(hResult))
//	{
//		ErrorMessageVisualizator::ShowErrorMessage(lpszErrorOpeningRecord, NULL);
//		return false;
//	}
//
//	// Прочитаме всички данни
//	while (hResult != DB_S_ENDOFROWSET)
//	{
//		PHONE_NUMBERS* pCurrentPhoneNumber = new PHONE_NUMBERS;
//		*pCurrentPhoneNumber = m_recPhoneNumber;
//		oPhoneNumbersArray.Add(pCurrentPhoneNumber);
//
//		hResult = MoveNext();
//
//		if (FAILED(hResult) && hResult != DB_S_ENDOFROWSET)
//		{
//			ErrorMessageVisualizator::ShowErrorMessage(lpszErrorOpeningRecord, NULL);
//			return false;
//		}
//		// Logic with the result
//	}
//
//	return true;
//}
//
//bool CPhoneNumbersTable::SelectWhereID(const long lID, PHONE_NUMBERS& recPhoneNumber)
//{
//	CString strQuery;
//	strQuery.Format((CString)lpszSelectById, lID);
//
//	if (!ExecuteQuery(strQuery, AccessorTypes::NoneModifying))
//		return false;
//
//	if (FAILED(MoveFirst()))
//	{
//		ErrorMessageVisualizator ::ShowErrorMessage(lpszErrorOpeningRecord, NULL);
//		return false;
//	}
//	recPhoneNumber = m_recPhoneNumber;
//
//	return true;
//};
//
//bool CPhoneNumbersTable::UpdateWhereID(const long lID, const PHONE_NUMBERS& recPhoneNumber)
//{
//	// Конструираме заявката
//	CString strQuery;
//	strQuery.Format((CString)lpszSelectById, lID);
//
//	// Изпълняваме командата
//	if (!ExecuteQuery(strQuery, AccessorTypes::Modifying))
//		return false;
//
//	if (FAILED(MoveFirst()))
//	{
//		ErrorMessageVisualizator::ShowErrorMessage(lpszErrorOpeningRecord, strQuery);
//		return false;
//	}
//
//	if (recPhoneNumber.lUpdateCounter != m_recPhoneNumber.lUpdateCounter)
//	{
//		ErrorMessageVisualizator::ShowErrorMessage(lpszInvalidRecordVersion, NULL);
//		return false;
//	}
//
//	m_recPhoneNumber.lUpdateCounter++;
//	m_recPhoneNumber = recPhoneNumber;
//
//	if (FAILED(SetData(ModifyColumnCode)))
//	{
//		ErrorMessageVisualizator::ShowErrorMessage(lpszErrorUpdatingRecord, NULL);
//		return false;
//	}
//
//	return true;
//};
//
//bool CPhoneNumbersTable::InsertRecord(const PHONE_NUMBERS& recPhoneNumber)
//{
//	if (!ExecuteQuery((CString)lpszEmptySelect, AccessorTypes::Modifying))
//	{
//		ErrorMessageVisualizator::ShowErrorMessage(lpszErrorExecutingQuery, (CString)lpszEmptySelect);
//		return false;
//	}
//
//	m_recPhoneNumber = recPhoneNumber;
//
//	if (FAILED(__super::InsertRecord(ModifyColumnCode)))
//	{
//		ErrorMessageVisualizator::ShowErrorMessage(lpszErrorInsertingRecord, NULL);
//		return false;
//	}
//
//	return true;
//};
//
//bool CPhoneNumbersTable::DeleteWhereID(const long lID)
//{
//	// Конструираме заявката
//	CString strQuery;
//	strQuery.Format((CString)lpszSelectById, lID);
//
//	// Изпълняваме командата
//	if (!ExecuteQuery(strQuery, AccessorTypes::Modifying))
//	{
//		ErrorMessageVisualizator::ShowErrorMessage(lpszErrorExecutingQuery, strQuery);
//		return false;
//	}
//
//	if (MoveFirst() != S_OK)
//	{
//		ErrorMessageVisualizator ::ShowErrorMessage(lpszErrorOpeningRecord, strQuery);
//		return false;
//	}
//
//	if (FAILED(Delete()))
//	{
//		ErrorMessageVisualizator::ShowErrorMessage(lpszErrorDeletingRecord, NULL);
//		return false;
//	}
//
//	return true;
//};


//bool CPhoneNumbersTable::DeleteWherePersonID(const long lID)
//{
//	// Конструираме заявката
//	CString strQuery;
//	strQuery.Format((CString)lpszSelectAllByPersonId, lID);
//
//	// Изпълняваме командата
//	if (!ExecuteQuery(strQuery, AccessorTypes::Modifying))
//	{
//		ErrorMessageVisualizator::ShowErrorMessage(lpszErrorExecutingQuery, strQuery);
//		return false;
//	}
//
//	if (MoveFirst() != S_OK)
//	{
//		ErrorMessageVisualizator ::ShowErrorMessage(lpszErrorOpeningRecord, strQuery);
//		return false;
//	}
//
//	if (FAILED(Delete()))
//	{
//		ErrorMessageVisualizator :: ShowErrorMessage(lpszErrorDeletingRecord, NULL);
//		return false;
//	}
//	return true;
//}


//
//void CPhoneNumbersTable::CloseRowSet()
//{
//	Close();
//}