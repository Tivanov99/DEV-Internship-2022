#include "pch.h"
#include "CPersonsData.h"

CPersonsData::CPersonsData()
	:m_oPersonsTable(m_oSession), m_oPhoneNumbersTable(m_oSession), m_oCitiesTable(m_oSession)
{
};
CPersonsData::~CPersonsData() {};

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
	
	//TODO: Check here for deleteting all phone numbers with that id.m_oSession

	if (!m_oPhoneNumbersTable.DeleteWherePersonID(1))
	{
		m_oSession.Abort();
		return false;
	}
	if (!m_oPersonsTable.DeleteWhereID(1))
	{
		m_oSession.Abort();
		return false;
	}
	return true;
}

bool CPersonsData::SelectAllPhoneNumbersByPersonId(long lPersonID, CPhoneNumbersArray& oPhoneNumbersArray)
{
	if (m_oPhoneNumbersTable.SelectAllByPersonId(lPersonID, oPhoneNumbersArray))
		return false;

	return true;
}
