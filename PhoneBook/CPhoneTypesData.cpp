#include "pch.h"
#include "CPhoneTypesData.h"


CPhoneTypesData::CPhoneTypesData()
	:m_PhoneTypesTable(m_oSession)
{
};

CPhoneTypesData::~CPhoneTypesData() {};

bool CPhoneTypesData::SelectAll(CPhoneTypesArray& oPhoneTyesArray)
{
	if (!m_PhoneTypesTable.SelectAll(oPhoneTyesArray, SqlQueries::SelectAll))
		return false;

	return true;
};
bool CPhoneTypesData::SelectWhereID(const long lID, PHONE_TYPES& recPhoneType)
{
	if (!m_PhoneTypesTable.SelectWhereID(lID, recPhoneType, SqlQueries::SelectWhereID))
		return false;

	return true;
}

bool CPhoneTypesData::UpdateWhereID(const long lID, const PHONE_TYPES& recPhoneType)
{
	if (!m_PhoneTypesTable.UpdateWhereID(lID, recPhoneType, SqlQueries::SelectWhereID))
		return false;

	return true;
}

bool CPhoneTypesData::InsertRecord(const PHONE_TYPES& recPhoneType)
{
	if (!m_PhoneTypesTable.InsertRecord(recPhoneType))
		return false;

	return true;
}

bool CPhoneTypesData::DeleteWhereID(const long lID)
{
	if (!m_PhoneTypesTable.DeleteWhereID(lID, SqlQueries::SelectWhereID))
		return false;

	return true;
}
