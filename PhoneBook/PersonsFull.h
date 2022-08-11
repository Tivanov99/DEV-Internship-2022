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
	/// <summary>Функция която връща записа подаден през конструктора.</summary>
	PERSONS& GetPerson();
	/// <summary>Функция която връща масива подаден през конструктора.</summary>
	CPhoneNumbersArray& GetPhoneNumbers();
	//Members:
	//------------------
private:
	PERSONS& m_recPerson;
	CPhoneNumbersArray& m_PhoneNumbersArray;
};

