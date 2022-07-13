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

///<summary>type-def ����������� CTypedPtrArray ����� �������� CPtrArray ��������� � ��������� CITIES< / summary >

//typedef CSelfClearingTypedPtrArray<CITIES> CCitiesArray;
