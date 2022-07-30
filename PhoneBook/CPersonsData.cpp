#include "pch.h"
#include "CPersonsData.h"

CPersonsData::CPersonsData() {

};
CPersonsData::~CPersonsData() {

};

bool CPersonsData::SelectAllCities(CCitiesArray& oCitiesArray)
{
	if (!m_oCitiesTable.SelectAll(oCitiesArray))
		return false;

	return true;
}
bool CPersonsData::SelectAll(CPersonsArray& oPersonsArray)
{
	if (!m_oPersonsTable.SelectAll(oPersonsArray))
		return false;

	return true;
}

bool CPersonsData::SelectWhereID(const long lID, PERSONS& recPersons)
{
	if (!m_oPersonsTable.SelectWhereID(lID, recPersons))
		return false;

	return true;
}

bool CPersonsData::UpdateWhereID(const long lID, const PERSONS& recPersons)
{
	if (!m_oPersonsTable.UpdateWhereID(lID, recPersons))
		return false;

	return true;
}

bool CPersonsData::Insert(const PERSONS& recPersons)
{
	if (!m_oPersonsTable.Insert(recPersons))
		return false;

	return true;
}

bool CPersonsData::DeleteWhereID(const long lID)
{
	if (!m_oPersonsTable.DeleteWhereID(lID))
		return false;

	return true;
}

