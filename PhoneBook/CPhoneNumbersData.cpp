#include "pch.h"
#include "CPhoneNumbersData.h"
#include "CPhoneNumbersTable.h"


CPhoneNumbersData::CPhoneNumbersData()
{
};
CPhoneNumbersData::~CPhoneNumbersData() {};

bool CPhoneNumbersData::SelectAll(CPhoneNumbersArray& oPhoneNumbersArray)
{
	CPhoneNumbersTable oPhoneNumbersTable(m_oDbConnector.GetSession());

	if (!oPhoneNumbersTable.SelectAll(oPhoneNumbersArray))
	{
		m_oDbConnector.CloseDbConnectionAndSession();
		return false;
	}
	m_oDbConnector.CloseDbConnectionAndSession();

	return true;
};

bool CPhoneNumbersData::SelectWhereID(const long lID, PHONE_NUMBERS& recPhoneNumbers)
{
	CPhoneNumbersTable oPhoneNumbersTable(m_oDbConnector.GetSession());

	if (!oPhoneNumbersTable.SelectWhereID(lID, recPhoneNumbers))
	{
		m_oDbConnector.CloseDbConnectionAndSession();

		return false;
	}
	m_oDbConnector.CloseDbConnectionAndSession();

	return true;
}

bool CPhoneNumbersData::UpdateWhereID(const long lID, const PHONE_NUMBERS& recPhoneNumbers)
{
	CPhoneNumbersTable oPhoneNumbersTable(m_oDbConnector.GetSession());

	if (!oPhoneNumbersTable.UpdateWhereID(lID, recPhoneNumbers))
	{
		m_oDbConnector.CloseDbConnectionAndSession();
		return false;
	}
	m_oDbConnector.CloseDbConnectionAndSession();

	return true;
}

bool CPhoneNumbersData::InsertRecord(const PHONE_NUMBERS& recPhoneNumbers)
{
	CPhoneNumbersTable oPhoneNumbersTable(m_oDbConnector.GetSession());

	if (!oPhoneNumbersTable.InsertRecord(recPhoneNumbers))
	{
		m_oDbConnector.CloseDbConnectionAndSession();

		return false;
	}
	m_oDbConnector.CloseDbConnectionAndSession();

	return true;
}

bool CPhoneNumbersData::DeleteWhereID(const long lID)
{
	CPhoneNumbersTable oPhoneNumbersTable(m_oDbConnector.GetSession());

	if (!oPhoneNumbersTable.DeleteWhereID(lID))
	{
		m_oDbConnector.CloseDbConnectionAndSession();

		return false;
	}
	m_oDbConnector.CloseDbConnectionAndSession();

	return true;
}