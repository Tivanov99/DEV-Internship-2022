#include "pch.h"
#include "CitiesData.h"
#include "DataBaseConnector.h"

CCitiesData::CCitiesData()
{};
CCitiesData::~CCitiesData() {};

bool CCitiesData::SelectAll(CCitiesArray& oCitiesArray)
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
};
bool CCitiesData::SelectWhereID(const long lID, CITIES& recCities)
{
	DataBaseConnector* pDatabaseConnector = DataBaseConnector::GetInstance();

	if (!pDatabaseConnector->OpenSession())
		return false;

	CCitiesTable oCitiesTable(pDatabaseConnector->GetSession());

	if (!oCitiesTable.SelectWhereID(lID, recCities))
	{
		pDatabaseConnector->CloseSession();
		return false;
	}
	pDatabaseConnector->CloseSession();
	return true;
}

bool CCitiesData::UpdateCityById(const long lID, const CITIES& recCities)
{
	DataBaseConnector* pDatabaseConnector = DataBaseConnector::GetInstance();

	if (!pDatabaseConnector->OpenSession())
		return false;

	CCitiesTable oCitiesTable(pDatabaseConnector->GetSession());
	if (!oCitiesTable.UpdateWhereID(lID, recCities))
	{
		pDatabaseConnector->CloseSession();
		return false;
	}
	pDatabaseConnector->CloseSession();
	return true;
}

bool CCitiesData::InsertRecord(CITIES& recCities)
{
	DataBaseConnector* pDatabaseConnector = DataBaseConnector::GetInstance();

	if (!pDatabaseConnector->OpenSession())
		return false;

	CCitiesTable oCitiesTable(pDatabaseConnector->GetSession());

	if (!oCitiesTable.InsertRecord(recCities))
	{
		pDatabaseConnector->CloseSession();
		return false;
	}
	pDatabaseConnector->CloseSession();
	return true;
}

bool CCitiesData::DeleteWhereID(const long lID)
{
	DataBaseConnector* pDatabaseConnector = DataBaseConnector::GetInstance();

	if (!pDatabaseConnector->OpenSession())
		return false;

	CCitiesTable oCitiesTable(pDatabaseConnector->GetSession());

	if (!oCitiesTable.DeleteWhereID(lID))
	{
		pDatabaseConnector->CloseSession();
		return false;
	}
	pDatabaseConnector->CloseSession();
	return true;
}
