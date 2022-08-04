#include "pch.h"
#include "CCitiesData.h"

CCitiesData::CCitiesData()
	:m_CitiesTable(m_oSession)
{};
CCitiesData::~CCitiesData() {};

bool CCitiesData::SelectAll(CCitiesArray& oCitiesArray)
{
	if (!m_CitiesTable.SelectAll(oCitiesArray))
		return false;

	return true;
};
bool CCitiesData::SelectWhereID(const long lID, CITIES& recCities)
{
	if (!m_CitiesTable.SelectWhereID(lID, recCities, SqlQueries::SelectWhereID))
		return false;

	return true;
}

bool CCitiesData::UpdateWhereID(const long lID, const CITIES& recCities)
{
	if (!m_CitiesTable.UpdateWhereID(lID, recCities, SqlQueries::SelectWhereID))
		return false;

	return true;
}

bool CCitiesData::InsertRecord(const CITIES& recCities)
{
	if (!m_CitiesTable.InsertRecord(recCities))
		return false;

	return true;
}

bool CCitiesData::DeleteWhereID(const long lID)
{
	if (!m_CitiesTable.DeleteWhereID(lID, SqlQueries::SelectWhereID))
		return false;

	return true;
}
