#pragma once
#include "CCitiesTable.h"

class CCitiesData
{
	// Constructor / Destructor
	// ----------------
public:
	CCitiesData();
	~CCitiesData();

	// Methods
	// ----------------

	/// <summary>������� ����� ���� ����� ������ �� ��������� "CITIES" � �� ������ � ������� ���� �������� �����.</summary>
	/// <param name="oCitiesArray">����� � ����� �� ����� �������� ������ ��������� �����.</param>
	bool SelectAll(CCitiesArray& oCitiesArray);

	/// <summary>������� ����� ���� ����� �� ��������� "CITIES" ����� ID �������� �� "lID" � �� ���������� � "recCities" ���������.</summary>
	/// <param name="lID">�������� ������������� ���� ����� �� �� ����� ����� � ������.</param>
	/// <param name="recCities">���������� ����� �� ������� ��������� �� ���������</param>
	bool SelectWhereID(const long lID, CITIES& recCities);

	/// <summary>������� ����� ����� ������� �� ����� �� ��������� "CITIES" ����� ID �������� �� "lID" ���������,� �� ������� ��������� �� ��������� "recCities" � ������ �������� �� ������.</summary>
	/// <param name="lID">�������� ������������� ���� ����� �� �� ����� ����� � ������.</param>
	/// <param name="recCities">���������� ����� ������� ���� ����������� �����.</param>
	bool UpdateCityById(const long lID, const CITIES& recCities);

	/// <summary>������� ����� ������ ����� ������� ���� �������� ��� ��������� "CITIES".</summary>
	/// <param name="recCities">���������� ����� ������� ��� �����.</param>
	bool InsertRecord(CITIES& recCities);

	/// <summary>������� ����� ������� ����� �� ��������� "CITIES" ����� �������� �� "lID" ���������.</summary>
	/// <param name="lID">�������� ������������� ���� ����� �� �� ����� ����� � ������.</param>
	bool DeleteWhereID(const long lID);
};

