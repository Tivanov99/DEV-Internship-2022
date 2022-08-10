#include "pch.h"
#include "CPhoneTypesData.h"
#include "DataBaseConnector.h"


CPhoneTypesData::CPhoneTypesData()
{
};

CPhoneTypesData::~CPhoneTypesData() {};

bool CPhoneTypesData::SelectAll(CPhoneTypesArray& oPhoneTyesArray)
{
	DataBaseConnector* pdbConnector  = DataBaseConnector::GetInstance();
	if (!pdbConnector->OpenSession())
		return false;

	CPhoneTypesTable oPhoneTypesTable(pdbConnector->GetSession());
	if (!oPhoneTypesTable.SelectAll(oPhoneTyesArray))
	{
		pdbConnector->CloseSession();
		return false;
	}
	pdbConnector->CloseSession();
	return true;
};
bool CPhoneTypesData::SelectWhereID(const long lID, PHONE_TYPES& recPhoneType)
{
	DataBaseConnector* pdbConnector = DataBaseConnector::GetInstance();

	if (!pdbConnector->OpenSession())
		return false;

	CPhoneTypesTable oPhoneTypesTable(pdbConnector->GetSession());
	if (!oPhoneTypesTable.SelectWhereID(lID, recPhoneType))
	{
		pdbConnector->CloseSession();
		return false;
	}
	pdbConnector->CloseSession();
	return true;
}

bool CPhoneTypesData::UpdateWhereID(const long lID, const PHONE_TYPES& recPhoneType)
{
	DataBaseConnector* pdbConnector = DataBaseConnector::GetInstance();

	if (!pdbConnector->OpenSession())
		return false;

	CPhoneTypesTable oPhoneTypesTable(pdbConnector->GetSession());
	if (!oPhoneTypesTable.UpdateWhereID(lID, recPhoneType))
	{
		pdbConnector->CloseSession();
		return false;
	}
	pdbConnector->CloseSession();
	return true;
}

bool CPhoneTypesData::InsertRecord(PHONE_TYPES& recPhoneType)
{
	DataBaseConnector* pdbConnector = DataBaseConnector::GetInstance();
	pdbConnector->OpenSession();
	CPhoneTypesTable oPhoneTypesTable(pdbConnector->GetSession());
	if (!oPhoneTypesTable.InsertRecord(recPhoneType))
	{
		pdbConnector->CloseSession();
		return false;
	}
	pdbConnector->CloseSession();
	return true;
}

bool CPhoneTypesData::DeleteWhereID(const long lID)
{
	DataBaseConnector* pdbConnector = DataBaseConnector::GetInstance();

	if (!pdbConnector->OpenSession())
		return false;

	CPhoneTypesTable oPhoneTypesTable(pdbConnector->GetSession());
	if (!oPhoneTypesTable.DeleteWhereID(lID))
	{
		pdbConnector->CloseSession();
		return false;
	}
	pdbConnector->CloseSession();
	return true;
}
