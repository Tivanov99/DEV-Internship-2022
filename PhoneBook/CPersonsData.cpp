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

	//if (pDatabaseConnector->OpenDbConnection())
	//	return false;

	CPhoneNumbersTable oPhoneNumbersTable(pDatabaseConnector->GetSession());

	CString strWhereClause;
	strWhereClause.Format(SqlQueries::WherePersonID, lPersonID);

	if (!oPhoneNumbersTable.SelectBySpecificColumnWhereID(oPhoneNumbersArray, strWhereClause))
	{
		pDatabaseConnector->CloseDbConnectionAndSession();
		return false;
	}

	pDatabaseConnector->CloseDbConnectionAndSession();

	return true;
}

bool CPersonsData::SelectAllPhoneTypes(CPhoneTypesArray& oPhoneTypesArray)
{
	DataBaseConnector* pDatabaseConnector = DataBaseConnector::GetInstance();

	if (!pDatabaseConnector->OpenDbConnection())
	{
		pDatabaseConnector->CloseDbConnectionAndSession();
		return false;
	}

	CPhoneTypesTable oPhoneTypesTable(pDatabaseConnector->GetSession());

	if (!oPhoneTypesTable.SelectAll(oPhoneTypesArray))
	{
		pDatabaseConnector->CloseDbConnectionAndSession();
		return false;
	}
	pDatabaseConnector->CloseDbConnectionAndSession();

	return true;
}

bool CPersonsData::SelectAllCities(CCitiesArray& oCitiesArray)
{
	DataBaseConnector* pDatabaseConnector = DataBaseConnector::GetInstance();

	/*if (!pDatabaseConnector->OpenDbConnection())
	{
		pDatabaseConnector->CloseDbConnectionAndSession();
		return false;

	}*/

	CCitiesTable oCitiesTable(pDatabaseConnector->GetSession());

	if (!oCitiesTable.SelectAll(oCitiesArray))
	{
		pDatabaseConnector->CloseDbConnectionAndSession();
		return false;
	}

	pDatabaseConnector->CloseDbConnectionAndSession();
	return true;
}
bool CPersonsData::SelectAll(CPersonsArray& oPersonsArray)
{
	DataBaseConnector* pDatabaseConnector = DataBaseConnector::GetInstance();

	CPersonsTable îPersonsTable(pDatabaseConnector->GetSession());
	if (!îPersonsTable.SelectAll(oPersonsArray))
	{
		pDatabaseConnector->CloseDbConnectionAndSession();
		return false;
	}

	pDatabaseConnector->CloseDbConnectionAndSession();
	return true;
}

bool CPersonsData::SelectWhereID(const long lID, PERSONS& recPersons)
{
	DataBaseConnector* pDatabaseConnector = DataBaseConnector::GetInstance();

	/*if (!pDatabaseConnector->OpenDbConnection())
	{
		pDatabaseConnector->CloseDbConnectionAndSession();
		return false;
	}*/

	CPersonsTable îPersonsTable(pDatabaseConnector->GetSession());

	if (!îPersonsTable.SelectWhereID(lID, recPersons))
	{
		pDatabaseConnector->CloseDbConnectionAndSession();
		return false;
	}

	pDatabaseConnector->CloseDbConnectionAndSession();
	return true;
}

bool CPersonsData::UpdateWhereID(const long lID, const PERSONS& recPersons)
{
	DataBaseConnector* pDatabaseConnector = DataBaseConnector::GetInstance();

	/*if (!pDatabaseConnector->OpenDbConnection())
	{
		pDatabaseConnector->CloseDbConnectionAndSession();
		return false;
	}*/

	CSession oSession = pDatabaseConnector->GetSession();
	CPersonsTable îPersonsTable(oSession);

	if (!îPersonsTable.UpdateWhereID(lID, recPersons))
	{
		pDatabaseConnector->CloseDbConnectionAndSession();
		return false;
	}

	pDatabaseConnector->CloseDbConnectionAndSession();

	return true;
}

bool CPersonsData::InsertRecord(const PERSONS& recPersons)
{
	DataBaseConnector* pDatabaseConnector = DataBaseConnector::GetInstance();

	/*if (!pDatabaseConnector->OpenDbConnection())
	{
		pDatabaseConnector->CloseDbConnectionAndSession();
		return false;
	}*/

	CPersonsTable îPersonsTable(pDatabaseConnector->GetSession());

	if (!îPersonsTable.InsertRecord(recPersons))
	{
		pDatabaseConnector->CloseDbConnectionAndSession();
		return false;
	}

	pDatabaseConnector->CloseDbConnectionAndSession();

	return true;
}

bool CPersonsData::DeleteWhereID(const long lID)
{
	DataBaseConnector* pDatabaseConnector = DataBaseConnector::GetInstance();

	/*if (!pDatabaseConnector->OpenDbConnection())
	{
		pDatabaseConnector->CloseDbConnectionAndSession();
		return false;
	}*/

	CPersonsTable îPersonsTable(pDatabaseConnector->GetSession());

	if (!îPersonsTable.DeleteWhereID(lID))
	{
		pDatabaseConnector->CloseDbConnectionAndSession();
		return false;
	}

	pDatabaseConnector->CloseDbConnectionAndSession();

	return true;
}

bool CPersonsData::DeletePersonAndPhoneNumbers(const long lID)
{
	DataBaseConnector* pDatabaseConnector = DataBaseConnector::GetInstance();

	/*if (!pDatabaseConnector->OpenDbConnection())
	{
		pDatabaseConnector->CloseDbConnectionAndSession();
		return false;
	}*/
	CSession oSession = pDatabaseConnector->GetSession();

	if (oSession.StartTransaction() != S_OK)
	{
		oSession.Abort();
		pDatabaseConnector->CloseDbConnectionAndSession();
		return false;
	}

	CPhoneNumbersTable oPhoneNumbersTable(oSession);

	CString strSqlQuery;
	strSqlQuery.Format(SqlQueries::WherePersonID, lID);

	if (!oPhoneNumbersTable.DeleteBySpecificColumnWhereID(lID, strSqlQuery))
	{
		oSession.Abort();
		pDatabaseConnector->CloseDbConnectionAndSession();
		return false;
	}

	CPersonsTable îPersonsTable(oSession);
	if (!îPersonsTable.DeleteWhereID(lID))
	{
		oSession.Abort();
		pDatabaseConnector->CloseDbConnectionAndSession();
		return false;
	}

	oSession.Commit();
	pDatabaseConnector->CloseDbConnectionAndSession();
	return true;
}

//TODO: Add transaction !!!!!
//TODO: Back all logic with arrays!
bool CPersonsData::UpdatePersonAndPhoneNumbers(long lPersonID, CPhoneNumbersMap& oModifiedPhoneNumbersMap)
{
	DataBaseConnector* pDbConnector = DataBaseConnector::GetInstance();
	CSession oSession = pDbConnector->GetSession();

	CPhoneNumbersArray oPhoneNumbersArray;

	if (!SelectAllPhoneNumbersByPersonId(lPersonID, oPhoneNumbersArray))
		return false;

	CPhoneNumbersTable oPhoneNumbersTable(oSession);

	for (INT_PTR i = 0; i < oPhoneNumbersArray.GetCount(); i++)
	{
		PHONE_NUMBERS* pCurrentOriginalPhoneNumber = oPhoneNumbersArray.GetAt(i);
		if (pCurrentOriginalPhoneNumber == NULL)
			continue;

		PHONE_NUMBERS* pPhoneNumbersFromModifiedMap;

		if (!oModifiedPhoneNumbersMap.Lookup(pCurrentOriginalPhoneNumber->lID, pPhoneNumbersFromModifiedMap))
		{
			if (!DeleteWhereID(pCurrentOriginalPhoneNumber->lID))
				break;

			continue;
		}
		if (ComparePhoneNumbers(*pPhoneNumbersFromModifiedMap, *pCurrentOriginalPhoneNumber))
		{
			if (!oPhoneNumbersTable.UpdateWhereID(pPhoneNumbersFromModifiedMap->lID, *pPhoneNumbersFromModifiedMap))
				return false;
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
				return false;
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
