#include "pch.h"
#include "CPersonsData.h"

CPersonsData::CPersonsData(){};
CPersonsData::~CPersonsData() {};

bool CPersonsData::SelectAllCities(CCitiesArray& oCitiesArray)
{
	m_oDbConnector.OpenDbConnectionAndSession();
	CCitiesTable oCitiesTable(m_oDbConnector.GetSession());

	if (!oCitiesTable.SelectAll(oCitiesArray))
	{
		m_oDbConnector.CloseDbConnectionAndSession();
		return false;
	}

	m_oDbConnector.CloseDbConnectionAndSession();
	return true;
}
bool CPersonsData::SelectAll(CPersonsArray& oPersonsArray)
{
	m_oDbConnector.OpenDbConnectionAndSession();
	CPersonsTable īPersonsTable(m_oDbConnector.GetSession());
	if (!īPersonsTable.SelectAll(oPersonsArray))
	{
		m_oDbConnector.CloseDbConnectionAndSession();
		return false;
	}

	m_oDbConnector.CloseDbConnectionAndSession();
	return true;
}

bool CPersonsData::SelectWhereID(const long lID, PERSONS& recPersons)
{
	m_oDbConnector.OpenDbConnectionAndSession();
	CPersonsTable īPersonsTable(m_oDbConnector.GetSession());

	if (!īPersonsTable.SelectWhereID(lID, recPersons))
	{
		m_oDbConnector.CloseDbConnectionAndSession();
		return false;
	}

	m_oDbConnector.CloseDbConnectionAndSession();
	return true;
}

bool CPersonsData::UpdateWhereID(const long lID, const PERSONS& recPersons)
{
	m_oDbConnector.OpenDbConnectionAndSession();
	CPersonsTable īPersonsTable(m_oDbConnector.GetSession());

	if (!īPersonsTable.UpdateWhereID(lID, recPersons))
	{
		m_oDbConnector.CloseDbConnectionAndSession();
		return false;
	}

	m_oDbConnector.CloseDbConnectionAndSession();

	return true;
}

bool CPersonsData::Insert(const PERSONS& recPersons)
{
	m_oDbConnector.OpenDbConnectionAndSession();
	CPersonsTable īPersonsTable(m_oDbConnector.GetSession());

	if (!īPersonsTable.Insert(recPersons))
	{
	m_oDbConnector.CloseDbConnectionAndSession();
		return false;
	}

	m_oDbConnector.CloseDbConnectionAndSession();

	return true;
}

bool CPersonsData::DeleteWhereID(const long lID)
{
	m_oDbConnector.OpenDbConnectionAndSession();
	CSession oSession = m_oDbConnector.GetSession();

	oSession.StartTransaction();

	//TODO : Check here for hresult;

	CPhoneNumbersTable oPhoneNumbersTable(oSession);

	if (!oPhoneNumbersTable.DeleteWherePersonID(lID))
	{
		oSession.Abort();
		m_oDbConnector.CloseDbConnectionAndSession();
		return false;
	}

	CPersonsTable īPersonsTable(m_oDbConnector.GetSession());
	if (!īPersonsTable.DeleteWhereID(lID))
	{
		oSession.Abort();
		m_oDbConnector.CloseDbConnectionAndSession();
		return false;
	}

	oSession.Commit();

	m_oDbConnector.CloseDbConnectionAndSession();

	return true;
}

bool CPersonsData::SelectAllPhoneNumbersByPersonId(long lPersonID, CPhoneNumbersArray& oPhoneNumbersArray)
{
	m_oDbConnector.OpenDbConnectionAndSession();
	CPhoneNumbersTable oPhoneNumbersTable(m_oDbConnector.GetSession());

	if (oPhoneNumbersTable.SelectAllByPersonId(lPersonID, oPhoneNumbersArray))
	{
		m_oDbConnector.CloseDbConnectionAndSession();
		return false;
	}

	m_oDbConnector.CloseDbConnectionAndSession();

	return true;
}
