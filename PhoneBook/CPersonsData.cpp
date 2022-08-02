#include "pch.h"
#include "CPersonsData.h"
#include "CPhoneNumbersTable.h"

CPersonsData::CPersonsData()
{
};
CPersonsData::~CPersonsData() {};

bool CPersonsData::SelectAllCities(CCitiesArray& oCitiesArray)
{
	DataBaseConnector* pDatabaseConnector = DataBaseConnector::GetInstance();

	pDatabaseConnector->OpenDbConnectionAndSession();

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

	pDatabaseConnector->OpenDbConnectionAndSession();
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

	pDatabaseConnector->OpenDbConnectionAndSession();
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

	pDatabaseConnector->OpenDbConnectionAndSession();
	CPersonsTable îPersonsTable(pDatabaseConnector->GetSession());

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

	pDatabaseConnector->OpenDbConnectionAndSession();
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

	pDatabaseConnector->OpenDbConnectionAndSession();
	CSession oSession = pDatabaseConnector->GetSession();

	HRESULT hReuslt = oSession.StartTransaction();

	if (hReuslt != S_OK)
	{
		oSession.Abort();
		pDatabaseConnector->CloseDbConnectionAndSession();
		return false;
	}

	CPhoneNumbersTable oPhoneNumbersTable(oSession);

	if (!oPhoneNumbersTable.DeleteWherePersonID(lID))
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

bool CPersonsData::SelectAllPhoneNumbers(long lPersonID, CPhoneNumbersArray& oPhoneNumbersArray)
{
	DataBaseConnector* pDatabaseConnector = DataBaseConnector::GetInstance();

	pDatabaseConnector->OpenDbConnectionAndSession();
	CPhoneNumbersTable oPhoneNumbersTable(pDatabaseConnector->GetSession());

	if (oPhoneNumbersTable.SelectAllByPersonId(lPersonID, oPhoneNumbersArray))
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

}
