#pragma once
#include "Structures.h"
class CPersonsFull
{
public:
	//Constructor/Destrucotr
	//-----------------------
	CPersonsFull(PERSONS& recPerson, CPhoneNumbersArray& oPhoneNumbersArray);
	~CPersonsFull();

	//Methods
	//--------------
public:
	PERSONS& GetPerson();
	CPhoneNumbersArray& GetPhoneNumbers();
	//Members:
	//------------------
private:
	PERSONS& m_recPerson;
	CPhoneNumbersArray& m_PhoneNumbersArray;
};

