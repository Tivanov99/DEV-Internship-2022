#include "pch.h"
#include "CPersonsData.h"
#include "CPhoneNumbersTable.h"
#include "CPhoneTypesTable.h"

CPersonsData::CPersonsData()
{
};
CPersonsData::~CPersonsData() {};

bool CPersonsData::SelectAllPhoneNumbersByPersonId(long lPersonID, CPhoneNumbersArray& oPhoneNumbersArray)
{
	DataBaseConnector* pDatabaseConnector = DataBaseConnector::GetInstance();

	if (!pDatabaseConnector->OpenSession())
		return false;

	CPhoneNumbersTable oPhoneNumbersTable(pDatabaseConnector->GetSession());

	CString strWhereClause;
	strWhereClause.Format(SqlQueries::WherePersonID, lPersonID);

	if (!oPhoneNumbersTable.SelectBySpecificColumnWhereID(oPhoneNumbersArray, strWhereClause))
	{
		pDatabaseConnector->CloseSession();
		return false;
	}

	pDatabaseConnector->CloseSession();

	return true;
}

bool CPersonsData::SelectAllPhoneTypes(CPhoneTypesArray& oPhoneTypesArray)
{
	DataBaseConnector* pDatabaseConnector = DataBaseConnector::GetInstance();

	if (!pDatabaseConnector->OpenSession())
		return false;

	CPhoneTypesTable oPhoneTypesTable(pDatabaseConnector->GetSession());

	if (!oPhoneTypesTable.SelectAll(oPhoneTypesArray))
	{
		pDatabaseConnector->CloseSession();
		return false;
	}
	pDatabaseConnector->CloseSession();

	return true;
}

bool CPersonsData::SelectAllCities(CCitiesArray& oCitiesArray)
{
	DataBaseConnector* pDatabaseConnector = DataBaseConnector::GetInstance();

	if (!pDatabaseConnector->OpenSession())
		return false;

	CCitiesTable oCitiesTable(pDatabaseConnector->GetSession());

	if (!oCitiesTable.SelectAll(oCitiesArray))
	{
		pDatabaseConnector->CloseSession();
		return false;
	}

	pDatabaseConnector->CloseSession();
	return true;
}
bool CPersonsData::SelectAll(CPersonsArray& oPersonsArray)
{
	DataBaseConnector* pDatabaseConnector = DataBaseConnector::GetInstance();

	if (!pDatabaseConnector->OpenSession())
		return false;

	CPersonsTable îPersonsTable(pDatabaseConnector->GetSession());
	if (!îPersonsTable.SelectAll(oPersonsArray))
	{
		pDatabaseConnector->CloseSession();
		return false;
	}

	pDatabaseConnector->CloseSession();
	return true;
}

bool CPersonsData::SelectWhereID(const long lID, PERSONS& recPersons)
{
	DataBaseConnector* pDatabaseConnector = DataBaseConnector::GetInstance();

	if (pDatabaseConnector->OpenSession())
		return false;

	CPersonsTable îPersonsTable(pDatabaseConnector->GetSession());

	if (!îPersonsTable.SelectWhereID(lID, recPersons))
	{
		pDatabaseConnector->CloseSession();
		return false;
	}

	pDatabaseConnector->CloseSession();
	return true;
}

bool CPersonsData::UpdateWhereID(const long lID, const PERSONS& recPersons)
{
	DataBaseConnector* pDatabaseConnector = DataBaseConnector::GetInstance();

	if (pDatabaseConnector->OpenSession())
		return false;

	CSession oSession = pDatabaseConnector->GetSession();
	CPersonsTable îPersonsTable(oSession);

	if (!îPersonsTable.UpdateWhereID(lID, recPersons))
	{
		pDatabaseConnector->CloseSession();
		return false;
	}

	pDatabaseConnector->CloseSession();

	return true;
}

bool CPersonsData::InsertRecord(const PERSONS& recPersons)
{
	DataBaseConnector* pDatabaseConnector = DataBaseConnector::GetInstance();

	if (!pDatabaseConnector->OpenSession())
		return false;

	CPersonsTable îPersonsTable(pDatabaseConnector->GetSession());

	if (!îPersonsTable.InsertRecord(recPersons))
	{
		pDatabaseConnector->CloseSession();
		return false;
	}

	pDatabaseConnector->CloseSession();

	return true;
}

bool CPersonsData::DeleteWhereID(const long lID)
{
	DataBaseConnector* pDatabaseConnector = DataBaseConnector::GetInstance();

	if (!pDatabaseConnector->OpenSession())
		return false;

	CPersonsTable îPersonsTable(pDatabaseConnector->GetSession());

	if (!îPersonsTable.DeleteWhereID(lID))
	{
		pDatabaseConnector->CloseSession();
		return false;
	}

	pDatabaseConnector->CloseSession();

	return true;
}

bool CPersonsData::DeletePersonAndPhoneNumbers(const long lID)
{
	DataBaseConnector* pDatabaseConnector = DataBaseConnector::GetInstance();

	if (!pDatabaseConnector->OpenSession())
		return false;

	CSession oSession = pDatabaseConnector->GetSession();

	if (oSession.StartTransaction() != S_OK)
	{
		oSession.Abort();
		pDatabaseConnector->CloseSession();
		return false;
	}

	CPhoneNumbersTable oPhoneNumbersTable(oSession);

	CString strSqlQuery;
	strSqlQuery.Format(SqlQueries::WherePersonID, lID);

	if (!oPhoneNumbersTable.DeleteBySpecificColumnWhereID(lID, strSqlQuery))
	{
		oSession.Abort();
		pDatabaseConnector->CloseSession();
		return false;
	}

	CPersonsTable îPersonsTable(oSession);
	if (!îPersonsTable.DeleteWhereID(lID))
	{
		oSession.Abort();
		pDatabaseConnector->CloseSession();
		return false;
	}

	oSession.Commit();
	pDatabaseConnector->CloseSession();
	return true;
}

bool CPersonsData::UpdatePersonAndPhoneNumbers(const PERSONS& recPersons, CPhoneNumbersMap& oModifiedPhoneNumbersMap)
{
	CPhoneNumbersArray oPhoneNumbersArray;

	if (!SelectAllPhoneNumbersByPersonId(recPersons.lID, oPhoneNumbersArray))
		return false;

	DataBaseConnector* pDatabaseConnector = DataBaseConnector::GetInstance();

	if (!pDatabaseConnector->OpenSession())
		return false;

	CSession oSession = pDatabaseConnector->GetSession();

	if (oSession.StartTransaction() != S_OK)
		return false;

	CPersonsTable îPersonsTable(oSession);

	if (!îPersonsTable.UpdateWhereID(recPersons.lID, recPersons))
	{
		pDatabaseConnector->CloseSession();
		return false;
	}

	CPhoneNumbersTable oPhoneNumbersTable(oSession);

	for (INT_PTR i = 0; i < oPhoneNumbersArray.GetCount(); i++)
	{
		PHONE_NUMBERS* pCurrentOriginalPhoneNumber = oPhoneNumbersArray.GetAt(i);
		if (pCurrentOriginalPhoneNumber == NULL)
			continue;

		PHONE_NUMBERS* pPhoneNumbersFromModifiedMap;

		if (!oModifiedPhoneNumbersMap.Lookup(pCurrentOriginalPhoneNumber->lID, pPhoneNumbersFromModifiedMap))
		{
			if (pPhoneNumbersFromModifiedMap == NULL)
				continue;

			if (oPhoneNumbersTable.DeleteWhereID(pCurrentOriginalPhoneNumber->lID))
			{
				oSession.Abort();
				return false;
			}
			continue;
		}
		if (ComparePhoneNumbers(*pPhoneNumbersFromModifiedMap, *pCurrentOriginalPhoneNumber))
		{
			if (!oPhoneNumbersTable.UpdateWhereID(pPhoneNumbersFromModifiedMap->lID, *pPhoneNumbersFromModifiedMap))
			{
				oSession.Abort();
				return false;
			}
		}
			oModifiedPhoneNumbersMap.RemoveKey(pPhoneNumbersFromModifiedMap->lID);
	}

	//Insert
	POSITION posModifiedMap = oModifiedPhoneNumbersMap.GetStartPosition();

	while (posModifiedMap)
	{
		if (posModifiedMap == NULL)
			break;
		PHONE_NUMBERS* pCurrentOriginalPhoneNumber;
		long lCurrentId;
		oModifiedPhoneNumbersMap.GetNextAssoc(posModifiedMap, lCurrentId, pCurrentOriginalPhoneNumber);

		if (pCurrentOriginalPhoneNumber != NULL)
			if (!oPhoneNumbersTable.InsertRecord(*pCurrentOriginalPhoneNumber))
			{
				oSession.Abort();
				return false;
			}
	}
	oSession.Commit();
	pDatabaseConnector->CloseSession();
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
