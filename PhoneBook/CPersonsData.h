#pragma once
#include "Structures.h"
#include "CPersonsTable.h"
#include "CCitiesTable.h"


class CPersonsData 
{
	// Constructor / Destructor
	// ----------------
public:
	// Methods
	// ----------------
	CPersonsData();
	~CPersonsData();

	/// <summary>
	///  ������� ����� ���� ����� ������ �� ��������� "CITIES" � �� ������ � ������� ���� �������� �����.
	/// </summary>
	/// <param name="oCitiesArray">����� � ����� �� ����� �������� ������ ��������� �����.</param>
	bool SelectAllCities(CCitiesArray& oCitiesArray);

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
	bool Insert(const PERSONS& recPersons);

	/// <summary>
	///  ������� ����� ������� ����� �� ��������� "PERSONS" ����� �������� �� "lID" ���������.
	/// </summary>
	/// <param name="lID">�������� ������������� ���� ����� �� �� ����� ����� � ������.</param>
	bool DeleteWhereID(const long lID);
private:
	/// <summary>
	/// ������ �� ������ �� ������ �������� ������ ��������.
	/// </summary>
	CPersonsTable m_oPersonsTable;

	CCitiesTable m_oCitiesTable;
};

