#include "pch.h"
#include "PersonsData.h"
#include "PhoneNumbersTable.h"
#include "PhoneTypesTable.h"
#include "CitiesTable.h"

CPersonsData::CPersonsData()
{
};
CPersonsData::~CPersonsData() {};

bool CPersonsData::SelectAllPhoneNumbersByPersonId(long lPersonID, CPhoneNumbersArray& oPhoneNumbersArray)
{
	if (!DataBaseConnector::GetInstance()->OpenSession())
		return false;

	CPhoneNumbersTable oPhoneNumbersTable(DataBaseConnector::GetInstance()->GetSession());

	CString strWhereClause;
	strWhereClause.Format(SqlQueries::WherePersonID, lPersonID);

	if (!oPhoneNumbersTable.SelectBySpecificColumnWhereID(oPhoneNumbersArray, strWhereClause))
	{
		DataBaseConnector::GetInstance()->CloseSession();
		return false;
	}
	DataBaseConnector::GetInstance()->CloseSession();
	return true;
}

bool CPersonsData::SelectAllPhoneTypes(CPhoneTypesArray& oPhoneTypesArray)
{
	if (!DataBaseConnector::GetInstance()->OpenSession())
		return false;

	CPhoneTypesTable oPhoneTypesTable(DataBaseConnector::GetInstance()->GetSession());

	if (!oPhoneTypesTable.SelectAll(oPhoneTypesArray))
	{
		DataBaseConnector::GetInstance()->CloseSession();
		return false;
	}
	DataBaseConnector::GetInstance()->CloseSession();

	return true;
}

bool CPersonsData::SelectAllCities(CCitiesArray& oCitiesArray)
{
	if (!DataBaseConnector::GetInstance()->OpenSession())
		return false;

	CCitiesTable oCitiesTable(DataBaseConnector::GetInstance()->GetSession());

	if (!oCitiesTable.SelectAll(oCitiesArray))
	{
		DataBaseConnector::GetInstance()->CloseSession();
		return false;
	}

	DataBaseConnector::GetInstance()->CloseSession();
	return true;
}

bool CPersonsData::SelectCityWhereID(const long lID, CITIES& recCities)
{
	if (!DataBaseConnector::GetInstance()->OpenSession())
		return false;

	CCitiesTable oCitiesTable(DataBaseConnector::GetInstance()->GetSession());

	if (!oCitiesTable.SelectWhereID(lID, recCities))
	{
		DataBaseConnector::GetInstance()->CloseSession();
		return false;
	}
	DataBaseConnector::GetInstance()->CloseSession();
	return true;
}

bool CPersonsData::SelectAll(CPersonsArray& oPersonsArray)
{
	if (!DataBaseConnector::GetInstance()->OpenSession())
		return false;

	CPersonsTable îPersonsTable(DataBaseConnector::GetInstance()->GetSession());
	if (!îPersonsTable.SelectAll(oPersonsArray))
	{
		DataBaseConnector::GetInstance()->CloseSession();
		return false;
	}

	DataBaseConnector::GetInstance()->CloseSession();
	return true;
}

bool CPersonsData::SelectWhereID(const long lID, PERSONS& recPersons)
{
	if (DataBaseConnector::GetInstance()->OpenSession())
		return false;

	CPersonsTable îPersonsTable(DataBaseConnector::GetInstance()->GetSession());

	if (!îPersonsTable.SelectWhereID(lID, recPersons))
	{
		DataBaseConnector::GetInstance()->CloseSession();
		return false;
	}

	DataBaseConnector::GetInstance()->CloseSession();
	return true;
}

bool CPersonsData::UpdateWhereID(const long lID, const PERSONS& recPersons)
{
	if (DataBaseConnector::GetInstance()->OpenSession())
		return false;

	CSession oSession = DataBaseConnector::GetInstance()->GetSession();
	CPersonsTable îPersonsTable(oSession);

	if (!îPersonsTable.UpdateWhereID(lID, recPersons))
	{
		DataBaseConnector::GetInstance()->CloseSession();
		return false;
	}

	DataBaseConnector::GetInstance()->CloseSession();

	return true;
}

bool CPersonsData::InsertPersonAndPhoneNumbers(PERSONS& recPersons, CPhoneNumbersArray& oPhoneNumbersArray)
{
	if (!DataBaseConnector::GetInstance()->OpenSession())
		return false;

	CSession oSession = DataBaseConnector::GetInstance()->GetSession();
	if (oSession.StartTransaction() != S_OK)
		return false;

	CPersonsTable oPersonsTable(oSession);

	if (!oPersonsTable.InsertRecord(recPersons))
	{
		DataBaseConnector::GetInstance()->AbortTransactionAndCloseSession();
		return false;
	}

	for (INT_PTR i = 0; i < oPhoneNumbersArray.GetCount(); i++)
	{
		PHONE_NUMBERS* pPhoneNumbers = oPhoneNumbersArray.GetAt(i);
		pPhoneNumbers->lPersonId = recPersons.lID;
	}

	if (!InsertPhoneNumbers(oPhoneNumbersArray))
	{
		DataBaseConnector::GetInstance()->AbortTransactionAndCloseSession();
		return false;
	}
	oSession.Commit();
	DataBaseConnector::GetInstance()->CloseSession();
	return true;
}

bool CPersonsData::DeleteWhereID(const long lID)
{
	if (!DataBaseConnector::GetInstance()->OpenSession())
		return false;

	CPersonsTable îPersonsTable(DataBaseConnector::GetInstance()->GetSession());

	if (!îPersonsTable.DeleteWhereID(lID))
	{
		DataBaseConnector::GetInstance()->CloseSession();
		return false;
	}

	DataBaseConnector::GetInstance()->CloseSession();
	return true;
}

bool CPersonsData::DeletePersonAndPhoneNumbers(const long lID)
{
	CPhoneNumbersArray oPhoneNumbersArray;
	if (!SelectAllPhoneNumbersByPersonId(lID, oPhoneNumbersArray))
		return false;

	if (!DataBaseConnector::GetInstance()->OpenSession())
		return false;

	CSession oSession = DataBaseConnector::GetInstance()->GetSession();

	if (oSession.StartTransaction() != S_OK)
	{
		DataBaseConnector::GetInstance()->AbortTransactionAndCloseSession();
		return false;
	}

	CPhoneNumbersTable oPhoneNumbersTable(oSession);

	CString strSqlQuery;
	strSqlQuery.Format(SqlQueries::WherePersonID, lID);

	if (oPhoneNumbersArray.GetCount()>0)
		if (!oPhoneNumbersTable.DeleteBySpecificColumnWhereID(lID, strSqlQuery))
		{
			DataBaseConnector::GetInstance()->AbortTransactionAndCloseSession();
			return false;
		}

	CPersonsTable îPersonsTable(oSession);
	if (!îPersonsTable.DeleteWhereID(lID))
	{
		DataBaseConnector::GetInstance()->AbortTransactionAndCloseSession();
		return false;
	}

	oSession.Commit();
	DataBaseConnector::GetInstance()->CloseSession();
	return true;
}

bool CPersonsData::UpdatePersonAndPhoneNumbers(const PERSONS& recPersons, CPhoneNumbersArray& oModifiedPhoneNumbersArray)
{
	CPhoneNumbersArray oPhoneNumbersArray;
	if (!SelectAllPhoneNumbersByPersonId(recPersons.lID, oPhoneNumbersArray))
		return false;

	if (!DataBaseConnector::GetInstance()->OpenSession())
		return false;

	CSession oSession = DataBaseConnector::GetInstance()->GetSession();
	if (oSession.StartTransaction() != S_OK)
		return false;

	CPersonsTable îPersonsTable(oSession);
	if (!îPersonsTable.UpdateWhereID(recPersons.lID, recPersons))
	{
		DataBaseConnector::GetInstance()->AbortTransactionAndCloseSession();
		return false;
	}

	for (INT_PTR i = 0; i < oPhoneNumbersArray.GetCount(); i++)
	{
		PHONE_NUMBERS* pCurrentOriginalPhoneNumber = oPhoneNumbersArray.GetAt(i);
		if (pCurrentOriginalPhoneNumber == NULL)
			continue;
		if (!UpdatePhoneNumbers(*pCurrentOriginalPhoneNumber, oModifiedPhoneNumbersArray))
		{
			DataBaseConnector::GetInstance()->AbortTransactionAndCloseSession();
			return false;
		}
	}
	if (!InsertPhoneNumbers(oModifiedPhoneNumbersArray))
	{
		DataBaseConnector::GetInstance()->AbortTransactionAndCloseSession();
		return false;
	}

	oSession.Commit();
	DataBaseConnector::GetInstance()->CloseSession();
	return true;
}
bool CPersonsData::InsertPhoneNumbers(CPhoneNumbersArray& oPhoneNumbersArray)
{
	CPhoneNumbersTable oPhoneNumbersTable(DataBaseConnector::GetInstance()->GetSession());

	for (INT_PTR i = 0; i < oPhoneNumbersArray.GetCount(); i++)
	{
		PHONE_NUMBERS* pCurrentPhoneNumber = oPhoneNumbersArray.GetAt(i);
		if (pCurrentPhoneNumber != NULL)
			if (!oPhoneNumbersTable.InsertRecord(*pCurrentPhoneNumber))
				return false;
	}
	return true;
}

bool CPersonsData::UpdatePhoneNumbers(PHONE_NUMBERS& pCurrentOriginalPhoneNumber, CPhoneNumbersArray& oModifiedPhoneNumbersArray)
{
	CPhoneNumbersTable oPhoneNumbersTable(DataBaseConnector::GetInstance()->GetSession());

	bool bFound = false;
	for (INT_PTR s = 0; s < oModifiedPhoneNumbersArray.GetCount(); s++)
	{
		PHONE_NUMBERS* pCurrentModifiedPhoneNumber = oModifiedPhoneNumbersArray.GetAt(s);
		if (pCurrentModifiedPhoneNumber == NULL)
			continue;

		if (pCurrentOriginalPhoneNumber.lID == pCurrentModifiedPhoneNumber->lID)
		{
			if (ComparePhoneNumbers(*pCurrentModifiedPhoneNumber, pCurrentOriginalPhoneNumber))
				if (!oPhoneNumbersTable.UpdateWhereID(pCurrentModifiedPhoneNumber->lID, *pCurrentModifiedPhoneNumber))
					return false;
			oModifiedPhoneNumbersArray.RemoveAt(s);
			bFound = true;
			break;
		}
	}
	if (!bFound)
	{
		if (!oPhoneNumbersTable.DeleteWhereID(pCurrentOriginalPhoneNumber.lID))
		{
			return false;
		}
	}
	return true;
}

bool CPersonsData::ComparePhoneNumbers(PHONE_NUMBERS& oComparedPhoneNumber, PHONE_NUMBERS& oPhoneNumberComparator)
{
	if (oPhoneNumberComparator.lPhoneTypeId != oComparedPhoneNumber.lPhoneTypeId)
		return true;

	if (_tcscmp(oPhoneNumberComparator.szPhoneNumber, oComparedPhoneNumber.szPhoneNumber) != 0)
		return true;

	return false;
}
