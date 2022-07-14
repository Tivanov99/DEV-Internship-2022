#include "pch.h"
#include "CCitiesData.h"

CCitiesData::CCitiesData() {};
CCitiesData::~CCitiesData() {};

bool CCitiesData::SelectAll(CSelfClearingTypedPtrArray<CITIES>& oCitiesArray)
{
	m_CitiesTable.SelectAll(oCitiesArray);
};
bool CCitiesData::SelectWhereID(const long lID, CITIES& recCities)
{
	m_CitiesTable.SelectWhereID(lID, recCities);
}

bool CCitiesData::UpdateWhereID(const long lID, const CITIES& recCities)
{
	m_CitiesTable.UpdateWhereID(lID, recCities);
}

bool CCitiesData::Insert(const CITIES& recCities)
{
	m_CitiesTable.Insert(recCities);
}

bool CCitiesData::DeleteWhereID(const long lID)
{
	m_CitiesTable.DeleteWhereID(lID);
}