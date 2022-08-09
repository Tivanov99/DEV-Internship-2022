#include "pch.h"
#include "CCitiesData.h"
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
		return false;

	return true;
};
bool CCitiesData::SelectWhereID(const long lID, CITIES& recCities)
{
	DataBaseConnector* pDatabaseConnector = DataBaseConnector::GetInstance();

	if (!pDatabaseConnector->OpenSession())
		return false;

	CCitiesTable oCitiesTable(pDatabaseConnector->GetSession());

	if (!oCitiesTable.SelectWhereID(lID, recCities))
		return false;

	return true;
}

bool CCitiesData::UpdateWhereID(const long lID, const CITIES& recCities)
{
	DataBaseConnector* pDatabaseConnector = DataBaseConnector::GetInstance();

	if (!pDatabaseConnector->OpenSession())
		return false;

	CCitiesTable oCitiesTable(pDatabaseConnector->GetSession());
	if (!oCitiesTable.UpdateWhereID(lID, recCities))
		return false;

	return true;
}

bool CCitiesData::InsertRecord(const CITIES& recCities)
{
	DataBaseConnector* pDatabaseConnector = DataBaseConnector::GetInstance();

	if (!pDatabaseConnector->OpenSession())
		return false;

	CCitiesTable oCitiesTable(pDatabaseConnector->GetSession());

	if (!oCitiesTable.InsertRecord(recCities))
		return false;

	return true;
}

bool CCitiesData::DeleteWhereID(const long lID)
{
	DataBaseConnector* pDatabaseConnector = DataBaseConnector::GetInstance();

	if (!pDatabaseConnector->OpenSession())
		return false;

	CCitiesTable oCitiesTable(pDatabaseConnector->GetSession());

	if (!oCitiesTable.DeleteWhereID(lID))
		return false;

	return true;
}
