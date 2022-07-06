#pragma once
#include <string>
#include "Structures.h"
#include "BaseService.h";
using namespace std;

class CityService : public BaseService<CITIES>
{
private:
	//<summary>������� �������� ������� �� 'CITY_NAME' �� ������� ���� �������� ���������</summary>
	void SetCityName(const CString &sorce, CITIES* city);
	//<summary>������� �������� ������� �� 'AREA_NAME' �� ������� ���� �������� ���������</summary>
	void SetAreaName(const CString &sorce, CITIES* city);
	//<summary>������� �������� ������� �� 'POSTAL_CODE' �� ������� ���� �������� ���������</summary>
	void SetPostalCode(const int nSorce, CITIES* city);
public:

	CityService()
	{

	}
	~CityService() {

	};
	//<summary>������� �������� ������ �������� �������� � ������� ����� ���� ��������, ����������� �� ����� ���� 'BaseService' </summary>
	void AddDefaultElements(CCitiesArray& oCities) override;
	//<summary>������� ���������� ���������� �� ����� ������� �� �� ��������� �� nIndex, ����������� �� ����� ���� 'BaseService'.</summary>
	void ShowElementInfoAtIndex(const int nIndex, const CCitiesArray &oArray)override;
	//<summary>������� ��������� 'CITY_NAME' ���������� �� ����� ����� ������ ��� � �������� ���� ����� �������� 'oldCityName'.</summary>
	void ChangeCityName(const CString &oldCityName, const CString &newCityName, CCitiesArray& oCitiesArray);
	//<summary>������� ��������� 'CITY_NAME' �� ����� ������� ���� ��������.</summary>
	void ChangeCityName(CITIES& pOldCity, const CString &newCityName);
	//<summary>������� ��������� 'AREA_NAME' ���������� �� ����� ����� ������ ��� � �������� ���� ����� �������� 'oldCityAreaName'.</summary>
	void ChangeCityAreaName(const CString &oldCityAreaName, const CString &newCityAreaName, CCitiesArray& oCitiesArray);
	//<summary>������� ��������� 'AREA_NAME' �� ����� ������� ���� ��������.</summary>
	void ChangeCityAreaName(CITIES& pOldCity, const CString &newAreaName);
	//<summary>������� ��������� 'POSTAL_CODE' ���������� �� ����� ����� ������ ��� � �������� ���� ����� �������� 'cityName'.</summary>
	void ChangeCityPosalCode(const CString &cityName, const int nNewCityPosalCode, CCitiesArray& oCitiesArray);
	//<summary>������� ��������� 'POSTAL_CODE' ���������� �� ����� ������� ���� ����� ��������.</summary>
	void ChangeCityPostalCode(CITIES& pCity, const int nNewPostalCode);
};


