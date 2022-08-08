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

	pDatabaseConnector->OpenDbConnectionAndSession();
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

	if (!pDatabaseConnector->OpenDbConnectionAndSession())
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

	if (!pDatabaseConnector->OpenDbConnectionAndSession())
	{
		pDatabaseConnector->CloseDbConnectionAndSession();
		return false;

	}

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

	if (!pDatabaseConnector->OpenDbConnectionAndSession())
	{
		pDatabaseConnector->CloseDbConnectionAndSession();
		return false;
	}

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

	if (!pDatabaseConnector->OpenDbConnectionAndSession())
	{
		pDatabaseConnector->CloseDbConnectionAndSession();
		return false;
	}

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

	if (!pDatabaseConnector->OpenDbConnectionAndSession())
	{
		pDatabaseConnector->CloseDbConnectionAndSession();
		return false;
	}

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

	if (!pDatabaseConnector->OpenDbConnectionAndSession())
	{
		pDatabaseConnector->CloseDbConnectionAndSession();
		return false;
	}

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

	if (!pDatabaseConnector->OpenDbConnectionAndSession())
	{
		pDatabaseConnector->CloseDbConnectionAndSession();
		return false;
	}

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

	if (!pDatabaseConnector->OpenDbConnectionAndSession())
	{
		pDatabaseConnector->CloseDbConnectionAndSession();

		return false;
	}
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

	CPersonsTable îPersonsTable(pDatabaseConnector->GetSession());
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
bool CPersonsData::UpdatePersonPhoneNumbers(long lPersonID, CPhoneNumbersMap& oModifiedPhoneNumbersMap)
{
	CPhoneNumbersArray oPhoneNumbersArray;

	if (!SelectAllPhoneNumbersByPersonId(lPersonID, oPhoneNumbersArray))
		return false;

	PHONE_NUMBERS* pOriginalPhoneNumber;
	long lId;

	POSITION posOriginalPhoneNumbers = oPhoneNumbersOriginalMap.GetStartPosition();

	while (posOriginalPhoneNumbers)
	{
		if (posOriginalPhoneNumbers == NULL)
			break;
		oPhoneNumbersOriginalMap.GetNextAssoc(posOriginalPhoneNumbers, lId, pOriginalPhoneNumber);

		if (pOriginalPhoneNumber == NULL)
			continue;

		PHONE_NUMBERS* pCurrentModifiedPhoneNumber;

		if (!oModifiedPhoneNumbersMap.Lookup(lId, pCurrentModifiedPhoneNumber))
		{
			if (!m_oPhoneNumbersData.DeleteWhereID(pOriginalPhoneNumber->lID))
				return false;

			oPhoneNumbersOriginalMap.RemoveKey(pOriginalPhoneNumber->lID);
			continue;
		}

		if (m_oPhoneNumbersData.ComparePhoneNumbers(*pCurrentModifiedPhoneNumber, *pOriginalPhoneNumber))
		{
			if (!m_oPhoneNumbersData.UpdateWhereID(pCurrentModifiedPhoneNumber->lID, *pCurrentModifiedPhoneNumber))
				return false;

			oModifiedPhoneNumbersMap.RemoveKey(pOriginalPhoneNumber->lID);
		}
		else
		{
			oModifiedPhoneNumbersMap.RemoveKey(pOriginalPhoneNumber->lID);
		}
	}

	//Insert
	POSITION posModifiedMap = oModifiedPhoneNumbersMap.GetStartPosition();

	while (posModifiedMap)
	{
		if (posModifiedMap == NULL)
			break;
		PHONE_NUMBERS* pCurrentPhoneNumber;
		long lCurrentId;
		oModifiedPhoneNumbersMap.GetNextAssoc(posModifiedMap, lCurrentId, pCurrentPhoneNumber);

		if (pCurrentPhoneNumber != NULL)
			if (!m_oPhoneNumbersData.InsertRecord(*pCurrentPhoneNumber))
				return false;
	}

	return true;
}
