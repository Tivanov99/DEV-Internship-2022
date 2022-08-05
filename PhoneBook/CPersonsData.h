#pragma once
#include "Structures.h"
#include "CPersonsTable.h"
#include "CCitiesTable.h"
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

	/// <summary>
	///  ������� ����� ���� ����� ������ �� ��������� "PHONE_TYPES" � �� ������ � ������� ���� �������� �����.
	/// </summary>
	/// <param name="oCitiesArray">����� � ����� �� ����� �������� ������ ��������� �����.</param>
	bool SelectAllPhoneTypes(CPhoneTypesArray& oPhoneTypesArray);

	/// <summary>
	///  ������� ����� ���� ����� ������ �� ��������� "CITIES" � �� ������ � ������� ���� �������� �����.
	/// </summary>
	/// <param name="oCitiesArray">����� � ����� �� ����� �������� ������ ��������� �����.</param>
	bool SelectAllCities(CCitiesArray& oCitiesArray);

	/// <summary>
	///  ������� ����� ���� ����� ������ �� ��������� "PHONE_NUMBERS" � �� ������ � ������� ���� �������� �����.
	/// </summary>
	/// <param name="oPhoneNumbersArray">����� � ����� �� ����� �������� ������ ��������� �����.</param>
	bool SelectAllPhoneNumbersByPersonId(long lPersonID, CPhoneNumbersArray& oPhoneNumbersArray);

	/// <summary>
	///  ������� ����� ���� ����� ������ �� ��������� "PERSONS" � �� ������ � ������� ���� �������� �����.
	/// </summary>
	/// <param name="oPersonsArray">����� � ����� �� ����� �������� ������ ��������� �����.</param>
	bool SelectAll(CPersonsArray& oPersonsArray);

	/// <summary>
	///  ������� ����� ���� ����� �� ��������� "PERSONS" ����� ID �������� �� "lID" � �� ���������� � "recPersons" ���������.
	/// </summary>
	/// <param name="lID">�������� ������������� ���� ����� �� �� ����� ����� � ������.</param>
	/// <param name="recPersons">���������� ����� �� ������� ��������� �� ���������</param>
	bool SelectWhereID(const long lID, PERSONS& recPersons);

	/// <summary>
	///  ������� ����� ����� ������� �� ����� �� ��������� "PERSONS" ����� ID �������� �� "lID" ���������,
	///  � �� ������� ��������� �� ��������� "recPersons" � ������ �������� �� ������.
	/// </summary>
	/// <param name="lID">�������� ������������� ���� ����� �� �� ����� ����� � ������.</param>
	/// <param name="recCities">���������� ����� ������� ���� ����������� �����.</param>
	bool UpdateWhereID(const long lID, const PERSONS& recPersons);

	/// <summary>
	///  ������� ����� ������ ����� ������� ���� �������� ��� ��������� "PERSONS".
	/// </summary>
	/// <param name="recPersons">���������� ����� ������� ��� �����.</param>
	bool InsertRecord(const PERSONS& recPersons);

	/// <summary>
	///  ������� ����� ������� ����� �� ��������� "PERSONS" ����� �������� �� "lID" ���������.
	/// </summary>
	/// <param name="lID">�������� ������������� ���� ����� �� �� ����� ����� � ������.</param>
	bool DeleteWhereID(const long lID);

	bool DeletePersonPhoneNumbers(const long lID);
};

