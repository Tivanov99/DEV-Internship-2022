#pragma once
#include "CCitiesTable.h"
class CCitiesData
{
	// Constants
	// ----------------


	// Constructor / Destructor
	// ----------------
public:
	CCitiesData();
	~CCitiesData();

	// Methods
	// ----------------

	/// <summary>
	///  ������� ����� ���� ����� ������ �� ��������� "CITIES" � �� ������ � ������� ���� �������� �����.
	/// </summary>
	/// <param name="oCitiesArray">����� � ����� �� ����� �������� ������ ��������� �����.</param>
	bool SelectAll(CSelfClearingTypedPtrArray<CITIES>& oCitiesArray);

	/// <summary>
	///  ������� ����� ���� ����� �� ��������� "CITIES" ����� ID �������� �� "lID" � �� ���������� � "recCities" ���������.
	/// </summary>
	/// <param name="lID">�������� ������������� ���� ����� �� �� ����� ����� � ������.</param>
	/// <param name="recCities">���������� ����� �� ������� ��������� �� ���������</param>
	bool SelectWhereID(const long lID, CITIES& recCities);

	/// <summary>
	///  ������� ����� ���� �������� ������� ����� �� ��������� "CITIES" � �� ����� ���� ��������.
	/// </summary>
	CITIES* SelectLast();

	/// <summary>
	///  ������� ����� ����� ������� �� ����� �� ��������� "CITIES" ����� ID �������� �� "lID" ���������,
	///  � �� ������� ��������� �� ��������� "recCities" � ������ �������� �� ������.
	/// </summary>
	/// <param name="lID">�������� ������������� ���� ����� �� �� ����� ����� � ������.</param>
	/// <param name="recCities">���������� ����� ������� ���� ����������� �����.</param>
	bool UpdateWhereID(const long lID, const CITIES& recCities);

	/// <summary>
	///  ������� ����� ������ ����� ������� ���� �������� ��� ��������� "CITIES".
	/// </summary>
	/// <param name="recCities">���������� ����� ������� ��� �����.</param>
	bool Insert(const CITIES& recCities);

	/// <summary>
	///  ������� ����� ������� ����� �� ��������� "CITIES" ����� �������� �� "lID" ���������.
	/// </summary>
	/// <param name="lID">�������� ������������� ���� ����� �� �� ����� ����� � ������.</param>
	bool DeleteWhereID(const long lID);

	// Overrides
	// ----------------


	// Members
	// ----------------
private:
	/// <summary>
	/// ������ �� ������ �� ������ �������� ������ ��������.
	/// </summary>
	CCitiesTable m_CitiesTable;
};

