#include "pch.h"
#include "PhoneNumbersData.h"
#include "PhoneNumbersTable.h"


CPhoneNumbersData::CPhoneNumbersData()
{

};
CPhoneNumbersData::~CPhoneNumbersData() {};

bool CPhoneNumbersData::SelectAll(CPhoneNumbersArray& oPhoneNumbersArray)
{
	DataBaseConnector* pDbConnector = DataBaseConnector::GetInstance();

	if (!pDbConnector->OpenSession())
		return false;

	CPhoneNumbersTable oPhoneNumbersTable(pDbConnector->GetSession());

	if (!oPhoneNumbersTable.SelectAll(oPhoneNumbersArray))
	{
		pDbConnector->CloseSession();
		return false;
	}
	pDbConnector->CloseSession();

	return true;
};

bool CPhoneNumbersData::SelectWhereID(const long lID, PHONE_NUMBERS& recPhoneNumbers)
{
	DataBaseConnector* pDbConnector = DataBaseConnector::GetInstance();

	if (!pDbConnector->OpenSession())
		return false;

	CPhoneNumbersTable oPhoneNumbersTable(pDbConnector->GetSession());

	if (!oPhoneNumbersTable.SelectWhereID(lID, recPhoneNumbers))
	{
		pDbConnector->CloseSession();

		return false;
	}
	pDbConnector->CloseSession();

	return true;
}

bool CPhoneNumbersData::UpdateWhereID(const long lID, const PHONE_NUMBERS& recPhoneNumbers)
{
	DataBaseConnector* pDbConnector = DataBaseConnector::GetInstance();

	if (!pDbConnector->OpenSession())
		return false;

	CPhoneNumbersTable oPhoneNumbersTable(pDbConnector->GetSession());

	if (!oPhoneNumbersTable.UpdateWhereID(lID, recPhoneNumbers))
	{
		pDbConnector->CloseSession();
		return false;
	}
	pDbConnector->CloseSession();

	return true;
}

bool CPhoneNumbersData::InsertPhoneNumber(PHONE_NUMBERS& recPhoneNumbers)
{
	DataBaseConnector* pDbConnector = DataBaseConnector::GetInstance();

	if (!pDbConnector->OpenSession())
		return false;

	CPhoneNumbersTable oPhoneNumbersTable(pDbConnector->GetSession());

	if (!oPhoneNumbersTable.InsertRecord(recPhoneNumbers))
	{
		pDbConnector->CloseSession();

		return false;
	}
	pDbConnector->CloseSession();

	return true;
}

bool CPhoneNumbersData::DeleteWhereID(const long lID)
{
	DataBaseConnector* pDbConnector = DataBaseConnector::GetInstance();

	if (!pDbConnector->OpenSession())
		return false;

	CPhoneNumbersTable oPhoneNumbersTable(pDbConnector->GetSession());

	if (!oPhoneNumbersTable.DeleteWhereID(lID))
	{
		pDbConnector->CloseSession();

		return false;
	}
	pDbConnector->CloseSession();

	return true;
}