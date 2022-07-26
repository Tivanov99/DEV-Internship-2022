#include "pch.h"
#include "CCitiesData.h"

CCitiesData::CCitiesData() {};
CCitiesData::~CCitiesData() {};

bool CCitiesData::SelectAll(CSelfClearingTypedPtrArray<CITIES>& oCitiesArray)
{
	return m_CitiesTable.SelectAll(oCitiesArray);
};
bool CCitiesData::SelectWhereID(const long lID, CITIES& recCities)
{
	return m_CitiesTable.SelectWhereID(lID, recCities);
}

bool CCitiesData::UpdateWhereID(const long lID, const CITIES& recCities)
{
	return m_CitiesTable.UpdateWhereID(lID, recCities);
}

bool CCitiesData::Insert(const CITIES& recCities)
{
	return m_CitiesTable.Insert(recCities);
}

bool CCitiesData::DeleteWhereID(const long lID)
{
	return m_CitiesTable.DeleteWhereID(lID);
}
