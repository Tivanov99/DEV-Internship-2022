#include "pch.h"
#include "CPhoneTypesData.h"


CPhoneTypesData::CPhoneTypesData()
	:m_PhoneTypesTable(m_oSession)
{
};

CPhoneTypesData::~CPhoneTypesData() {};

bool CPhoneTypesData::SelectAll(CPhoneTypesArray& oPhoneTyesArray)
{
	if (!m_PhoneTypesTable.SelectAll(oPhoneTyesArray))
		return false;

	return true;
};
bool CPhoneTypesData::SelectWhereID(const long lID, PHONE_TYPES& recPhoneType)
{
	if (!m_PhoneTypesTable.SelectWhereID(lID, recPhoneType))
		return false;

	return true;
}

bool CCitiesData::UpdateWhereID(const long lID, const CITIES& recCities)
{
	if (!m_CitiesTable.UpdateWhereID(lID, recCities))
		return false;

	return true;
}

bool CCitiesData::InsertRecord(const CITIES& recCities)
{
	if (!m_CitiesTable.InsertRecord(recCities))
		return false;

	return true;
}

bool CCitiesData::DeleteWhereID(const long lID)
{
	if (!m_CitiesTable.DeleteWhereID(lID))
		return false;

	return true;
}
