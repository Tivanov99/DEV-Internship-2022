#include "pch.h"
#include "CPersonsTable.h"
#include "CBaseTable.cpp"
#include "ErrorVisualizator.h"


//const LPCSTR CPersonsTable::lpszSelectAllById = "SELECT * FROM PERSONS WHERE ID = %d";
//const LPCSTR CPersonsTable::lpszSelectAll = "SELECT * FROM PERSONS";
//const LPCSTR CPersonsTable::lpszEmptySelect = "SELECT TOP 0 * FROM PERSONS";

/////////////////////////////////////////////////////////////////////////////
// CPersonsTable

CPersonsTable::CPersonsTable(CSession& oSession)
	:CBaseTable(oSession,_T("PERSONS"))
{
};
CPersonsTable::~CPersonsTable()
{
};

//bool CPersonsTable::ExecuteQuery(const CString& strQuery, AccessorTypes eQueryAccessor)
//{
//	bool bResult = false;
//	switch (eQueryAccessor)
//	{
//	case AccessorTypes::NoneModifying:
//		FAILED(Open(m_oSession, strQuery)) ?
//			ErrorMessageVisualizator::ShowErrorMessage(lpszErrorExecutingQuery, strQuery) :
//			bResult = true;
//		break;
//
//	case AccessorTypes::Modifying:
//		FAILED(Open(m_oSession, strQuery, &GetModifyDBPropSet())) ?
//			ErrorMessageVisualizator::ShowErrorMessage(lpszErrorExecutingQuery, strQuery) :
//			bResult = true;
//		break;
//
//	default:
//		ErrorMessageVisualizator::ShowErrorMessage(lpszErrorInvalidQueryAcessor, strQuery);
//		break;
//	}
//	return bResult;
//}
//
//bool CPersonsTable::SelectAll(CPersonsArray& oPersonsPtrArray)
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
//		PERSONS* pCurrentPerson = new PERSONS;
//		*pCurrentPerson = m_recTableRecord;
//		oPersonsPtrArray.Add(pCurrentPerson);
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
//};
//
//bool CPersonsTable::SelectWhereID(const long lID, PERSONS& recPersons)
//{
//	CString strQuery;
//	strQuery.Format((CString)lpszSelectAllById, lID);
//
//	if (!ExecuteQuery(strQuery, AccessorTypes::NoneModifying))
//	{
//		return false;
//	}
//
//	if (FAILED(MoveFirst()))
//	{
//		ErrorMessageVisualizator::ShowErrorMessage(lpszErrorOpeningRecord, NULL);
//		return false;
//	}
//	recPersons = m_recTableRecord;
//
//	return true;
//};
//
//
//bool CPersonsTable::UpdateWhereID(const long lID, const PERSONS& recPersons)
//{
//	// Конструираме заявката
//	CString strQuery;
//	strQuery.Format((CString)lpszSelectAllById, lID);
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
//	if (recPersons.lUpdateCounter != m_recTableRecord.lUpdateCounter)
//	{
//		ErrorMessageVisualizator::ShowErrorMessage(lpszInvalidRecordVersion, NULL);
//		return false;
//	}
//
//	m_recTableRecord.lUpdateCounter++;
//	m_recTableRecord = recPersons;
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
//bool CPersonsTable::InsertRecord(const PERSONS& recPersons)
//{
//	if (!ExecuteQuery((CString)lpszEmptySelect, AccessorTypes::Modifying))
//	{
//		ErrorMessageVisualizator::ShowErrorMessage(lpszErrorExecutingQuery, (CString)lpszEmptySelect);
//		return false;
//	}
//
//	m_recTableRecord = recPersons;
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
//bool CPersonsTable::DeleteWhereID(const long lID)
//{
//	// Конструираме заявката
//	CString strQuery;
//	strQuery.Format((CString)lpszSelectAllById, lID);
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
//		ErrorMessageVisualizator::ShowErrorMessage(lpszErrorOpeningRecord, strQuery);
//		return false;
//	}
//
//	if (FAILED(Delete()))
//	{
//		ErrorMessageVisualizator::ShowErrorMessage(lpszErrorDeletingRecord, NULL);
//		return false;
//	}
//	m_oSession.Commit();
//	return true;
//};
//
//void CPersonsTable::CloseRowSet()
//{
//	Close();
//}