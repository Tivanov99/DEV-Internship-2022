#include "pch.h"
#include "CCitiesTable.h"
#include "ErrorVisualizator.h"


//const LPCSTR CCitiesTable::lpszSelectAllById = "SELECT * FROM CITIES WHERE ID = %d";
//const LPCSTR CCitiesTable::lpszSelectAll = "SELECT * FROM CITIES";
//const LPCSTR CCitiesTable::lpszEmptySelect = "SELECT TOP 0 * FROM CITIES";

/////////////////////////////////////////////////////////////////////////////
// CCitiesTable

CCitiesTable::CCitiesTable(CSession& oSession)
	:CBaseTable(oSession,_T("CITIES"))
{};
CCitiesTable::~CCitiesTable()
{
};

//void CCitiesTable::CloseRowSet()
//{
//	Close();
//}
//
//bool CCitiesTable::ExecuteQuery(const CString& strQuery, AccessorTypes eQueryAccessor)
//{
//	bool bResult = false;
//	switch (eQueryAccessor)
//	{
//	case AccessorTypes::NoneModifying:
//		FAILED(Open(m_oSession, strQuery)) ?
//			ErrorMessageVisualizator ::ShowErrorMessage(lpszErrorExecutingQuery, strQuery) : 
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
//bool CCitiesTable::SelectAll(CCitiesArray& oCitiesPtrArray)
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
//		CITIES* pCurrentCity = new CITIES;
//		*pCurrentCity = m_recCITY;
//		oCitiesPtrArray.Add(pCurrentCity);
//
//		hResult = MoveNext();
//
//		if (FAILED(hResult) && hResult != DB_S_ENDOFROWSET)
//		{
//			ErrorMessageVisualizator::ShowErrorMessage(lpszErrorOpeningRecord, NULL);
//			
//			return false;
//		}
//		// Logic with the result
//	}
//
//	return true;
//};
//
//bool CCitiesTable::SelectWhereID(const long lID, CITIES& recCities)
//{
//	CString strQuery;
//	strQuery.Format((CString)lpszSelectAllById, lID);
//
//	if (!ExecuteQuery(strQuery, AccessorTypes::NoneModifying))
//		return false;
//
//	if (FAILED(MoveFirst()))
//	{
//		ErrorMessageVisualizator::ShowErrorMessage(lpszErrorOpeningRecord, NULL);
//		return false;
//	}
//	recCities = m_recCITY;
//
//	return true;
//};
//
//bool CCitiesTable::UpdateWhereID(const long lID, const CITIES& recCities)
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
//	if (recCities.lUpdateCounter != m_recCITY.lUpdateCounter)
//	{
//		ErrorMessageVisualizator::ShowErrorMessage(lpszInvalidRecordVersion, NULL);
//		return false;
//	}
//
//	m_recCITY.lUpdateCounter++;
//	m_recCITY = recCities;
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
//bool CCitiesTable::InsertRecord(const CITIES& recCities)
//{
//	if (!ExecuteQuery((CString)lpszEmptySelect, AccessorTypes::Modifying))
//	{
//		ErrorMessageVisualizator::ShowErrorMessage(lpszErrorExecutingQuery, (CString)lpszEmptySelect);
//		return false;
//	}
//
//	m_recCITY = recCities;
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
//bool CCitiesTable::DeleteWhereID(const long lID)
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
//
//	return true;
//};

