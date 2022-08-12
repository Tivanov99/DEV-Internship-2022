#include "pch.h"
#include "PhoneTypesData.h"
#include "DataBaseConnector.h"


CPhoneTypesData::CPhoneTypesData()
{
};

CPhoneTypesData::~CPhoneTypesData() {};

bool CPhoneTypesData::SelectAll(CPhoneTypesArray& oPhoneTyesArray)
{
	if (!DataBaseConnector::GetInstance()->OpenSession())
		return false;

	CPhoneTypesTable oPhoneTypesTable(DataBaseConnector::GetInstance()->GetSession());
	if (!oPhoneTypesTable.SelectAll(oPhoneTyesArray))
	{
		DataBaseConnector::GetInstance()->CloseSession();
		return false;
	}
	DataBaseConnector::GetInstance()->CloseSession();
	return true;
};
bool CPhoneTypesData::SelectWhereID(const long lID, PHONE_TYPES& recPhoneType)
{
	if (!DataBaseConnector::GetInstance()->OpenSession())
		return false;

	CPhoneTypesTable oPhoneTypesTable(DataBaseConnector::GetInstance()->GetSession());
	if (!oPhoneTypesTable.SelectWhereID(lID, recPhoneType))
	{
		DataBaseConnector::GetInstance()->CloseSession();
		return false;
	}
	DataBaseConnector::GetInstance()->CloseSession();
	return true;
}

bool CPhoneTypesData::UpdateWhereID(const long lID, const PHONE_TYPES& recPhoneType)
{
	if (!DataBaseConnector::GetInstance()->OpenSession())
		return false;

	CPhoneTypesTable oPhoneTypesTable(DataBaseConnector::GetInstance()->GetSession());
	if (!oPhoneTypesTable.UpdateWhereID(lID, recPhoneType))
	{
		DataBaseConnector::GetInstance()->CloseSession();
		return false;
	}
	DataBaseConnector::GetInstance()->CloseSession();
	return true;
}

bool CPhoneTypesData::InsertRecord(PHONE_TYPES& recPhoneType)
{
	DataBaseConnector::GetInstance()->OpenSession();
	CPhoneTypesTable oPhoneTypesTable(DataBaseConnector::GetInstance()->GetSession());
	if (!oPhoneTypesTable.InsertRecord(recPhoneType))
	{
		DataBaseConnector::GetInstance()->CloseSession();
		return false;
	}
	DataBaseConnector::GetInstance()->CloseSession();
	return true;
}

bool CPhoneTypesData::DeleteWhereID(const long lID)
{
	if (!DataBaseConnector::GetInstance()->OpenSession())
		return false;

	CPhoneTypesTable oPhoneTypesTable(DataBaseConnector::GetInstance()->GetSession());
	if (!oPhoneTypesTable.DeleteWhereID(lID))
	{
		DataBaseConnector::GetInstance()->CloseSession();
		return false;
	}
	DataBaseConnector::GetInstance()->CloseSession();
	return true;
}
