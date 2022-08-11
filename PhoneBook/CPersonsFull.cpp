#include "pch.h"
#include "CPersonsFull.h"

CPersonsFull:: CPersonsFull(PERSONS& recPerson, CPhoneNumbersArray& oPhoneNumbersArray)
	:m_recPerson(recPerson), m_PhoneNumbersArray(oPhoneNumbersArray)
{}

CPersonsFull:: ~CPersonsFull() {};

PERSONS& CPersonsFull::GetPerson()
{
	return m_recPerson;
}

CPhoneNumbersArray& CPersonsFull::GetPhoneNumbers()
{
	return m_PhoneNumbersArray;
}