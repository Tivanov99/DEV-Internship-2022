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
		return false;

	CPhoneTypesTable oPhoneTypesTable(pDatabaseConnector->GetSession());

	if (!oPhoneTypesTable.SelectAll(oPhoneTypesArray))
		return false;

	return true;
}

bool CPersonsData::SelectAllCities(CCitiesArray& oCitiesArray)
{
	DataBaseConnector* pDatabaseConnector = DataBaseConnector::GetInstance();

	if (!pDatabaseConnector->OpenDbConnectionAndSession())
		return false;

	CCitiesTable oCitiesTable(pDatabaseConnector->GetSession());

	if (!oCitiesTable.SelectAll(oCitiesArray, SqlQueries::SelectAll))
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
		return false;

	CPersonsTable îPersonsTable(pDatabaseConnector->GetSession());
	if (!îPersonsTable.SelectAll(oPersonsArray, SqlQueries::SelectAll))
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
		return false;

	CPersonsTable îPersonsTable(pDatabaseConnector->GetSession());

	if (!îPersonsTable.SelectWhereID(lID, recPersons, SqlQueries::SelectWhereID))
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
		return false;

	CPersonsTable îPersonsTable(pDatabaseConnector->GetSession());

	if (!îPersonsTable.UpdateWhereID(lID, recPersons, SqlQueries::SelectWhereID))
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
		return false;

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

	if (!oPhoneNumbersTable.DeleteWhereID(lID, SqlQueries::WherePersonID))
	{
		oSession.Abort();
		pDatabaseConnector->CloseDbConnectionAndSession();
		return false;
	}

	CPersonsTable îPersonsTable(pDatabaseConnector->GetSession());
	if (!îPersonsTable.DeleteWhereID(lID,SqlQueries::SelectWhereID))
	{
		oSession.Abort();
		pDatabaseConnector->CloseDbConnectionAndSession();
		return false;
	}

	oSession.Commit();

	pDatabaseConnector->CloseDbConnectionAndSession();

	return true;
}

