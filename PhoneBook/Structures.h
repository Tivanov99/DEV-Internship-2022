#pragma once
#include <afxtempl.h>



#define CITY_NAME_SIZE	32
#define AREA_NAME_SIZE	32

/// <summary>
///  Дискова структура CITIES предназначена за таблицата 'CITIES'
/// </summary>
struct CITIES
{
	/// <summary>Променлива съдържаща първичен ключ от колоната 'ID' в таблицата 'CITIES'</summary>
	long lID;
	/// <summary>Променлива съдържаща текущата версия на запис.</summary>
	long lUpdateCounter;
	/// <summary>Променлива съдържаща стойността от колона 'CITY_NAME' в таблицата 'CITIES'</summary>
	TCHAR szCITY_NAME[CITY_NAME_SIZE];
	/// <summary>Променлива съдържаща стойността от колона 'AREA_NAME' в таблицата 'CITIES'</summary>
	TCHAR szAREA_NAME[AREA_NAME_SIZE];
	/// <summary>Променлива съдържаща стойността от колона 'POSTAL_CODE' в таблицата 'CITIES'</summary>
	long lPOSTAL_CODE;

	~CITIES()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};

///<summary>type-def презентиращ CTypedPtrArray който използва CPtrArray контейнер и таблицата CITIES< / summary >

//typedef CSelfClearingTypedPtrArray<CITIES> CCitiesArray;
