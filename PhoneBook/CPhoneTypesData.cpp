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
	pdbConnector->OpenSession();
	CPhoneTypesTable oPhoneTypesTable(pdbConnector->GetSession());
	if (!oPhoneTypesTable.SelectAll(oPhoneTyesArray))
		return false;

	return true;
};
bool CPhoneTypesData::SelectWhereID(const long lID, PHONE_TYPES& recPhoneType)
{
	DataBaseConnector* pdbConnector = DataBaseConnector::GetInstance();

	pdbConnector->OpenSession();

	CPhoneTypesTable oPhoneTypesTable(pdbConnector->GetSession());
	if (!oPhoneTypesTable.SelectWhereID(lID, recPhoneType))
		return false;

	return true;
}

bool CPhoneTypesData::UpdateWhereID(const long lID, const PHONE_TYPES& recPhoneType)
{
	DataBaseConnector* pdbConnector = DataBaseConnector::GetInstance();
	pdbConnector->OpenSession();
	CPhoneTypesTable oPhoneTypesTable(pdbConnector->GetSession());
	if (!oPhoneTypesTable.UpdateWhereID(lID, recPhoneType))
		return false;

	return true;
}

bool CPhoneTypesData::InsertRecord(const PHONE_TYPES& recPhoneType)
{
	DataBaseConnector* pdbConnector = DataBaseConnector::GetInstance();
	pdbConnector->OpenSession();
	CPhoneTypesTable oPhoneTypesTable(pdbConnector->GetSession());
	if (!oPhoneTypesTable.InsertRecord(recPhoneType))
		return false;

	return true;
}

bool CPhoneTypesData::DeleteWhereID(const long lID)
{
	DataBaseConnector* pdbConnector = DataBaseConnector::GetInstance();
	pdbConnector->OpenSession();
	CPhoneTypesTable oPhoneTypesTable(pdbConnector->GetSession());
	if (!oPhoneTypesTable.DeleteWhereID(lID))
		return false;

	return true;
}
