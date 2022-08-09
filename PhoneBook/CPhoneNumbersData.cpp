#include "pch.h"
#include "CPhoneNumbersData.h"
#include "CPhoneNumbersTable.h"


CPhoneNumbersData::CPhoneNumbersData()
{

};
CPhoneNumbersData::~CPhoneNumbersData() {};

bool CPhoneNumbersData::SelectAll(CPhoneNumbersArray& oPhoneNumbersArray)
{
	DataBaseConnector* pDbConnector = DataBaseConnector::GetInstance();

	if (!pDbConnector->OpenDbConnection())
		return false;

	CPhoneNumbersTable oPhoneNumbersTable(pDbConnector->GetSession());

	if (!oPhoneNumbersTable.SelectAll(oPhoneNumbersArray))
	{
		pDbConnector->CloseDbConnectionAndSession();
		return false;
	}
	pDbConnector->CloseDbConnectionAndSession();

	return true;
};

bool CPhoneNumbersData::SelectWhereID(const long lID, PHONE_NUMBERS& recPhoneNumbers)
{
	DataBaseConnector* pDbConnector = DataBaseConnector::GetInstance();

	if (!pDbConnector->OpenDbConnection())
		return false;

	CPhoneNumbersTable oPhoneNumbersTable(pDbConnector->GetSession());

	if (!oPhoneNumbersTable.SelectWhereID(lID, recPhoneNumbers))
	{
		pDbConnector->CloseDbConnectionAndSession();

		return false;
	}
	pDbConnector->CloseDbConnectionAndSession();

	return true;
}

bool CPhoneNumbersData::UpdateWhereID(const long lID, const PHONE_NUMBERS& recPhoneNumbers)
{
	DataBaseConnector* pDbConnector = DataBaseConnector::GetInstance();

	if (!pDbConnector->OpenDbConnection())
		return false;

	CPhoneNumbersTable oPhoneNumbersTable(pDbConnector->GetSession());

	if (!oPhoneNumbersTable.UpdateWhereID(lID, recPhoneNumbers))
	{
		pDbConnector->CloseDbConnectionAndSession();
		return false;
	}
	pDbConnector->CloseDbConnectionAndSession();

	return true;
}

bool CPhoneNumbersData::InsertRecord(const PHONE_NUMBERS& recPhoneNumbers)
{
	DataBaseConnector* pDbConnector = DataBaseConnector::GetInstance();

	if (!pDbConnector->OpenDbConnection())
		return false;

	CPhoneNumbersTable oPhoneNumbersTable(pDbConnector->GetSession());

	if (!oPhoneNumbersTable.InsertRecord(recPhoneNumbers))
	{
		pDbConnector->CloseDbConnectionAndSession();

		return false;
	}
	pDbConnector->CloseDbConnectionAndSession();

	return true;
}

bool CPhoneNumbersData::DeleteWhereID(const long lID)
{
	DataBaseConnector* pDbConnector = DataBaseConnector::GetInstance();

	if (!pDbConnector->OpenDbConnection())
		return false;

	CPhoneNumbersTable oPhoneNumbersTable(pDbConnector->GetSession());

	if (!oPhoneNumbersTable.DeleteWhereID(lID))
	{
		pDbConnector->CloseDbConnectionAndSession();

		return false;
	}
	pDbConnector->CloseDbConnectionAndSession();

	return true;
}