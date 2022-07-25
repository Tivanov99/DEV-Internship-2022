#pragma once
#include <afxtempl.h>



#define CITY_NAME_SIZE	32
#define AREA_NAME_SIZE	32

/// <summary>
///  ������� ��������� CITIES ������������� �� ��������� 'CITIES'
/// </summary>

struct CITIES
{
	/// <summary>���������� ��������� �������� ���� �� �������� 'ID' � ��������� 'CITIES'</summary>
	
	long lID;

	/// <summary>���������� ��������� �������� ������ �� �����.</summary>
	long lUpdateCounter;
	/// <summary>���������� ��������� ���������� �� ������ 'CITY_NAME' � ��������� 'CITIES'</summary>
	TCHAR szCITY_NAME[CITY_NAME_SIZE];
	/// <summary>���������� ��������� ���������� �� ������ 'AREA_NAME' � ��������� 'CITIES'</summary>
	TCHAR szAREA_NAME[AREA_NAME_SIZE];
	/// <summary>���������� ��������� ���������� �� ������ 'POSTAL_CODE' � ��������� 'CITIES'</summary>
	long lPOSTAL_CODE;

	~CITIES()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};

#define FIRST_NAME_SIZE		32
#define SECOND_NAME_SIZE	32
#define LAST_NAME_SIZE		32
#define ADDRESS_SIZE		256

/// <summary>
///  ������� ��������� PERSONS ������������� �� ��������� 'PERSONS'
/// </summary>
struct PERSONS {
	/// <summary>���������� ��������� �������� ���� �� �������� 'ID' � ��������� 'PERSONS'</summary>
	long lID;
	/// <summary>?</summary>
	long lUpdateCounter;
	/// <summary>���������� ��������� ���������� �� ������ 'FIRST_NAME' � ���������  'PERSONS'</summary>
	TCHAR szFIRST_NAME[FIRST_NAME_SIZE];
	/// <summary>���������� ��������� ���������� �� ������ 'SECOND_NAME' � ���������  'PERSONS'</summary>
	char szSECOND_NAME[SECOND_NAME_SIZE];
	/// <summary>���������� ��������� ���������� �� �������� 'LAST_NAME' � ���������  'PERSONS'</summary>
	TCHAR szLAST_NAME[LAST_NAME_SIZE];
	/// <summary>���������� ��������� �������� ���� (�� ������ 'CITY_ID' � ���������  'PERSONS')
	/// <summary>����� ��� ��������� 'CITIES' � ������ 'ID'</summary>
	long lCITY_ID;
	/// <summary>���������� ��������� ���������� �� �������� 'ADDRESS' � ���������  'PERSONS'</summary>
	TCHAR szADDRESS[ADDRESS_SIZE];

	PERSONS()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};

#define PHONE_NUMBER_SIZE	16

/// <summary>
///  ������� ��������� 'PHONE_NUMBERS' ������������� �� ��������� 'PHONE_NUMBERS'
/// </summary>
struct PHONE_NUMBERS {
	/// <summary>���������� ��������� �������� ���� �� �������� 'ID' � ��������� 'PHONE_NUMBERS'</summary>
	long lID;
	/// <summary>?</summary>
	long lUpdateCounter;
	/// <summary>
		/// ���������� ��������� �������� ���� (�� ������ 'PHONE_TYPE_ID' � ��������� 'PHONE_TYPES')
		/// ����� ��� �������� 'ID' � ��������� 'PHONE_NUMBERS'</summary>;
	/// </summary>
	long lPHONE_TYPE_ID;
	/// <summary>���������� ��������� ���������� �� �������� 'PHONE_NUMBER' � ���������  'PHONE_NUMBERS'</summary>
	TCHAR szPHONE_NUMBER[PHONE_NUMBER_SIZE];

	PHONE_NUMBERS()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};

#define PHONE_TYPE_SIZE	16
/// <summary>
///  ������� ��������� PHONE_TYPES ������������� �� ��������� 'PHONE_TYPES'
/// </summary>
struct PHONE_TYPES {
	/// <summary>���������� ��������� �������� ���� �� �������� 'ID' � ��������� 'PHONE_TYPES'</summary>
	long lID;
	/// <summary>?</summary>
	long lUpdateCounter;
	/// <summary>���������� ��������� ���������� �� �������� 'PHONE_TYPE' � ���������  'PHONE_TYPES'</summary>
	TCHAR szPHONE_TYPE[PHONE_TYPE_SIZE];
	PHONE_TYPES()
	{
		SecureZeroMemory(this, sizeof(*this));
	};
};

//typedef CSelfClearingTypedPtrArray<CITIES> CCitiesArray;
enum ContextMenuOperations
{
	Edit,
	Delete,
	Create
};

