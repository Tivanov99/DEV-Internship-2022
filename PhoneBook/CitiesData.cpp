#include "pch.h"
#include "CitiesData.h"
#include "DataBaseConnector.h"

CCitiesData::CCitiesData()
{};
CCitiesData::~CCitiesData() {};

bool CCitiesData::SelectAll(CCitiesArray& oCitiesArray)
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
};
bool CCitiesData::SelectWhereID(const long lID, CITIES& recCities)
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

bool CCitiesData::UpdateCityById(const long lID, const CITIES& recCities)
{
	if (!DataBaseConnector::GetInstance()->OpenSession())
		return false;

	CCitiesTable oCitiesTable(DataBaseConnector::GetInstance()->GetSession());
	if (!oCitiesTable.UpdateWhereID(lID, recCities))
	{
		DataBaseConnector::GetInstance()->CloseSession();
		return false;
	}
	DataBaseConnector::GetInstance()->CloseSession();
	return true;
}

bool CCitiesData::InsertRecord(CITIES& recCities)
{
	if (!DataBaseConnector::GetInstance()->OpenSession())
		return false;

	CCitiesTable oCitiesTable(DataBaseConnector::GetInstance()->GetSession());

	if (!oCitiesTable.InsertRecord(recCities))
	{
		DataBaseConnector::GetInstance()->CloseSession();
		return false;
	}
	DataBaseConnector::GetInstance()->CloseSession();
	return true;
}

bool CCitiesData::DeleteWhereID(const long lID)
{
	if (!DataBaseConnector::GetInstance()->OpenSession())
		return false;

	CCitiesTable oCitiesTable(DataBaseConnector::GetInstance()->GetSession());

	if (!oCitiesTable.DeleteWhereID(lID))
	{
		DataBaseConnector::GetInstance()->CloseSession();
		return false;
	}
	DataBaseConnector::GetInstance()->CloseSession();
	return true;
}
