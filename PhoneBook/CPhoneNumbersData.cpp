#include "pch.h"
#include "CPhoneNumbersData.h"


CPhoneNumbersData::CPhoneNumbersData() {};
CPhoneNumbersData::~CPhoneNumbersData() {};

bool CPhoneNumbersData::SelectAll(CPhoneNumbersArray& oPhoneNumbersArray)
{
	if (!m_PhoneNumbersTable.SelectAll(oPhoneNumbersArray))
		return false;

	return true;
};

bool CPhoneNumbersData::SelectWhereID(const long lID, PHONE_NUMBERS& recPhoneNumbers)
{
	if (!m_PhoneNumbersTable.SelectWhereID(lID, recPhoneNumbers))
		return false;

	return true;
}

bool CPhoneNumbersData::UpdateWhereID(const long lID, const PHONE_NUMBERS& recPhoneNumbers)
{
	if (!m_PhoneNumbersTable.UpdateWhereID(lID, recPhoneNumbers))
		return false;

	return true;
}

bool CPhoneNumbersData::Insert(const PHONE_NUMBERS& recPhoneNumbers)
{
	if (!m_PhoneNumbersTable.Insert(recPhoneNumbers))
		return false;

	return true;
}

bool CPhoneNumbersData::DeleteWhereID(const long lID)
{
	if (!m_PhoneNumbersTable.DeleteWhereID(lID))
		return false;

	return true;
}