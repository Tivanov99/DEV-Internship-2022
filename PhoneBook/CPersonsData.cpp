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

	CPersonsTable īPersonsTable(pDatabaseConnector->GetSession());
	if (!īPersonsTable.SelectAll(oPersonsArray))
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

	CPersonsTable īPersonsTable(pDatabaseConnector->GetSession());

	if (!īPersonsTable.SelectWhereID(lID, recPersons))
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

	CPersonsTable īPersonsTable(pDatabaseConnector->GetSession());

	if (!īPersonsTable.UpdateWhereID(lID, recPersons))
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

	CPersonsTable īPersonsTable(pDatabaseConnector->GetSession());

	if (!īPersonsTable.InsertRecord(recPersons))
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

	CPersonsTable īPersonsTable(pDatabaseConnector->GetSession());

	if (!īPersonsTable.DeleteWhereID(lID))
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

	CPersonsTable īPersonsTable(pDatabaseConnector->GetSession());
	if (!īPersonsTable.DeleteWhereID(lID))
	{
		oSession.Abort();
		pDatabaseConnector->CloseDbConnectionAndSession();
		return false;
	}

	oSession.Commit();

	pDatabaseConnector->CloseDbConnectionAndSession();

	return true;
}

