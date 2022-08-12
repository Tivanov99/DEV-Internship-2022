#include "pch.h"
#include "PhoneNumbersData.h"
#include "PhoneNumbersTable.h"


CPhoneNumbersData::CPhoneNumbersData()
{

};
CPhoneNumbersData::~CPhoneNumbersData() {};

bool CPhoneNumbersData::SelectAll(CPhoneNumbersArray& oPhoneNumbersArray)
{
	if (!DataBaseConnector::GetInstance()->OpenSession())
		return false;

	CPhoneNumbersTable oPhoneNumbersTable(DataBaseConnector::GetInstance()->GetSession());

	if (!oPhoneNumbersTable.SelectAll(oPhoneNumbersArray))
	{
		DataBaseConnector::GetInstance()->CloseSession();
		return false;
	}
	DataBaseConnector::GetInstance()->CloseSession();

	return true;
};

bool CPhoneNumbersData::SelectWhereID(const long lID, PHONE_NUMBERS& recPhoneNumbers)
{
	if (!DataBaseConnector::GetInstance()->OpenSession())
		return false;

	CPhoneNumbersTable oPhoneNumbersTable(DataBaseConnector::GetInstance()->GetSession());

	if (!oPhoneNumbersTable.SelectWhereID(lID, recPhoneNumbers))
	{
		DataBaseConnector::GetInstance()->CloseSession();

		return false;
	}
	DataBaseConnector::GetInstance()->CloseSession();

	return true;
}

bool CPhoneNumbersData::UpdateWhereID(const long lID, const PHONE_NUMBERS& recPhoneNumbers)
{
	if (!DataBaseConnector::GetInstance()->OpenSession())
		return false;

	CPhoneNumbersTable oPhoneNumbersTable(DataBaseConnector::GetInstance()->GetSession());

	if (!oPhoneNumbersTable.UpdateWhereID(lID, recPhoneNumbers))
	{
		DataBaseConnector::GetInstance()->CloseSession();
		return false;
	}
	DataBaseConnector::GetInstance()->CloseSession();

	return true;
}

bool CPhoneNumbersData::InsertPhoneNumber(PHONE_NUMBERS& recPhoneNumbers)
{
	if (!DataBaseConnector::GetInstance()->OpenSession())
		return false;

	CPhoneNumbersTable oPhoneNumbersTable(DataBaseConnector::GetInstance()->GetSession());

	if (!oPhoneNumbersTable.InsertRecord(recPhoneNumbers))
	{
		DataBaseConnector::GetInstance()->CloseSession();

		return false;
	}
	DataBaseConnector::GetInstance()->CloseSession();

	return true;
}

bool CPhoneNumbersData::DeleteWhereID(const long lID)
{
	if (!DataBaseConnector::GetInstance()->OpenSession())
		return false;

	CPhoneNumbersTable oPhoneNumbersTable(DataBaseConnector::GetInstance()->GetSession());

	if (!oPhoneNumbersTable.DeleteWhereID(lID))
	{
		DataBaseConnector::GetInstance()->CloseSession();

		return false;
	}
	DataBaseConnector::GetInstance()->CloseSession();

	return true;
}