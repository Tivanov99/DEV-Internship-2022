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
	/// <summary>������� ����� ����� ������ ������� ���� ������������.</summary>
	PERSONS& GetPerson();
	/// <summary>������� ����� ����� ������ ������� ���� ������������.</summary>
	CPhoneNumbersArray& GetPhoneNumbers();
	//Members:
	//------------------
private:
	PERSONS& m_recPerson;
	CPhoneNumbersArray& m_PhoneNumbersArray;
};

