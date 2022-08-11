#pragma once
#include "Structures.h"
#include "PersonsTable.h"
#include "DataBaseConnector.h"
#include <map>


class CPersonsData 
{
	// Constructor / Destructor
	// ----------------
public:
	
	CPersonsData();
	~CPersonsData();

	// Methods
	// ----------------
public:
	/// <summary>������� ����� ���� ����� ������ �� ��������� "PHONE_TYPES" � �� ������ � ������� ���� �������� �����.</summary>
	/// <param name="oCitiesArray">����� � ����� �� ����� �������� ������ ��������� �����.</param>
	bool SelectAllPhoneTypes(CPhoneTypesArray& oPhoneTypesArray);
	/// <summary>������� ����� ���� ����� ������ �� ��������� "CITIES" � �� ������ � ������� ���� �������� �����.</summary>
	/// <param name="oCitiesArray">����� � ����� �� ����� �������� ������ ��������� �����.</param>
	bool SelectAllCities(CCitiesArray& oCitiesArray);
	/// <summary>������� ����� ���� ����� ������ �� ��������� "PHONE_NUMBERS" � �� ������ � ������� ���� �������� �����.</summary>
	/// <param name="oPhoneNumbersArray">����� � ����� �� ����� �������� ������ ��������� �����.</param>
	bool SelectAllPhoneNumbersByPersonId(long lPersonID, CPhoneNumbersArray& oPhoneNumbersArray);
	/// <summary>������� ����� ���� ����� ������ �� ��������� "PERSONS" � �� ������ � ������� ���� �������� �����.</summary>
	/// <param name="oPersonsArray">����� � ����� �� ����� �������� ������ ��������� �����.</param>
	bool SelectAll(CPersonsArray& oPersonsArray);
	/// <summary>������� ����� ���� ����� �� ��������� "PERSONS" ����� ID �������� �� "lID" � �� ���������� � "recPersons" ���������.</summary>
	/// <param name="lID">�������� ������������� ���� ����� �� �� ����� ����� � ������.</param>
	/// <param name="recPersons">���������� ����� �� ������� ��������� �� ���������</param>
	bool SelectWhereID(const long lID, PERSONS& recPersons);
	/// <summary>������� ����� ����� ������� �� ����� �� ��������� "PERSONS" ����� ID �������� �� "lID" ���������,� �� ������� ��������� �� ��������� "recPersons" � ������ �������� �� ������.</summary>
	/// <param name="lID">�������� ������������� ���� ����� �� �� ����� ����� � ������.</param>
	/// <param name="recCities">���������� ����� ������� ���� ����������� �����.</param>
	bool UpdateWhereID(const long lID, const PERSONS& recPersons);
	/// <summary>������� ����� ������ ����� ������� ���� �������� ��� ��������� "PERSONS".</summary>
	/// <param name="recPersons">���������� ����� ������� ��� �����.</param>
	bool InsertPersonAndPhoneNumbers(PERSONS& recPersons, CPhoneNumbersArray& oPhoneNumbersArray);
	/// <summary>������� ����� ������� ����� �� ��������� "PERSONS" ����� �������� �� "lID" ���������.</summary>
	/// <param name="lID">�������� ������������� ���� ����� �� �� ����� ����� � ������.</param>
	bool DeleteWhereID(const long lID);
	/// <summary>������� ����� ������� ����� �� ��������� 'PERSONS' ����� ID �������� �� 'lID', � ������ ������ �� ��������� 'PHONE_NUMBERS' ����� �������� �� �������� 'PERSON_ID' �� ��������� � 'lID'.</summary>
	/// <param name="lID">�������� ������������� �� ����� �� �������� �������� �� ������.</param>
	bool DeletePersonAndPhoneNumbers(const long lID);
	/// <summary>������� ����� ����������� ����� �� ��������� 'PERSONS' ����� ID �������� �� 'lPersonID', � ������ ������ �� ��������� 'PHONE_NUMBERS' ����� �������� �� �������� 'PERSON_ID' �� ��������� � 'lPersonID'.</summary>
	/// <param name="recPersons">����� ����� ������� ���������� ����������.</param>
	/// <param name="oModifiedPhoneNumbersMap">�������� ��������� ������ ������ �� ��������� ������ ���� ���� � ���������� �������� � ���������� ��������.</param>
	bool UpdatePersonAndPhoneNumbers(const PERSONS& recPersons, CPhoneNumbersArray& oModifiedPhoneNumbersArray);
	/// <summary>������� ����� ����� ���� ������ �������� ������������� 'lID'.</summary>
	/// <param name="lID">�������� �������������</param>
	/// <param name="oCity">���������� ��� ����� ������ �� �� ������ �����</param>
	/// <returns></returns>
	bool SelectCityWhereID(const long lID, CITIES& recCities);
private:
	/// <summary>�������� 2 ������ �� ������� ����� ���.</summary>
	/// <param name="oComparedPhoneNumber">����� ����� �� ���� ���������.</param>
	/// <param name="oPhoneNumberComparator">����� � ����� �� �� ��������.</param>
	bool ComparePhoneNumbers(PHONE_NUMBERS& oComparedPhoneNumber, PHONE_NUMBERS& oPhoneNumberComparator);
	/// <summary>������� ����� ����������� ������ ������.</summary>
	/// <param name="pCurrentOriginalPhoneNumber">����� ����� �� ���� ��������� ���� ���������� � 'oModifiedPhoneNumbersArray'.</param>
	/// <param name="oModifiedPhoneNumbersArray">����� � ���� ������������� ������.</param>
	bool UpdatePhoneNumbers(PHONE_NUMBERS& pCurrentOriginalPhoneNumber,CPhoneNumbersArray& oModifiedPhoneNumbersArray);

	/// <summary>������� ����� ������ �������� � �� 'oPhoneNumbersArray' � ������.</summary>
	/// <param name="oPhoneNumbersArray">����� �������� ������ ���� ������.</param>
	bool InsertPhoneNumbers(CPhoneNumbersArray& oPhoneNumbersArray);
};
