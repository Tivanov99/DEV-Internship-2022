#include "pch.h"
#include "CPersonsData.h"

CPersonsData::CPersonsData()
	:m_oPersonsTable(m_oDbConnector.GetSession()),
	 m_oPhoneNumbersTable(m_oDbConnector.GetSession()),
	 m_oCitiesTable(m_oDbConnector.GetSession())
{
};
CPersonsData::~CPersonsData() {};

bool CPersonsData::SelectAllCities(CCitiesArray& oCitiesArray)
{
	m_oDbConnector.OpenDbConnectionAndSession();
	if (!m_oCitiesTable.SelectAll(oCitiesArray))
		return false;

	m_oDbConnector.CloseDbConnectionAndSession();
	return true;
}
bool CPersonsData::SelectAll(CPersonsArray& oPersonsArray)
{
	m_oDbConnector.OpenDbConnectionAndSession();
	CPersonsTable �PersonsTable(m_oDbConnector.GetSession());
	if (!�PersonsTable.SelectAll(oPersonsArray))
		return false;

	m_oDbConnector.CloseDbConnectionAndSession();
	return true;
}

bool CPersonsData::SelectWhereID(const long lID, PERSONS& recPersons)
{
	m_oDbConnector.OpenDbConnectionAndSession();
	CPersonsTable �PersonsTable(m_oDbConnector.GetSession());

	if (!�PersonsTable.SelectWhereID(lID, recPersons))
		return false;

	m_oDbConnector.CloseDbConnectionAndSession();
	return true;
}

bool CPersonsData::UpdateWhereID(const long lID, const PERSONS& recPersons)
{
	m_oDbConnector.OpenDbConnectionAndSession();
	CPersonsTable �PersonsTable(m_oDbConnector.GetSession());

	if (!�PersonsTable.UpdateWhereID(lID, recPersons))
		return false;

	m_oDbConnector.CloseDbConnectionAndSession();

	return true;
}

bool CPersonsData::Insert(const PERSONS& recPersons)
{
	m_oDbConnector.OpenDbConnectionAndSession();
	CPersonsTable �PersonsTable(m_oDbConnector.GetSession());

	if (!�PersonsTable.Insert(recPersons))
		return false;

	m_oDbConnector.CloseDbConnectionAndSession();

	return true;
}

bool CPersonsData::DeleteWhereID(const long lID)
{
	CSession oSession = m_oDbConnector.GetSession();

	m_oDbConnector.OpenDbConnectionAndSession();

	oSession.StartTransaction();

	if (!m_oPhoneNumbersTable.DeleteWherePersonID(1))
	{
		oSession.Abort();
		return false;
	}

	CPersonsTable �PersonsTable(m_oDbConnector.GetSession());
	if (!�PersonsTable.DeleteWhereID(1))
	{
		oSession.Abort();
		return false;
	}

	m_oDbConnector.CloseDbConnectionAndSession();

	return true;
}

bool CPersonsData::SelectAllPhoneNumbersByPersonId(long lPersonID, CPhoneNumbersArray& oPhoneNumbersArray)
{
	m_oDbConnector.OpenDbConnectionAndSession();

	if (m_oPhoneNumbersTable.SelectAllByPersonId(lPersonID, oPhoneNumbersArray))
		return false;

	m_oDbConnector.CloseDbConnectionAndSession();

	return true;
}
