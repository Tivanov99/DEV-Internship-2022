#pragma once
#include <string>
#include "Structures.h"
#include "BaseService.h";
using namespace std;

class CityService : public BaseService<CITIES>
{
private:
	///<summary>������� �������� ������� �� 'CITY_NAME' �� ������� ���� �������� ���������</summary>
	///<param name="strCityName">����� �� ���� ����� �� ���� �������� ���� ��������</param>
	///<param name="oCity">����� ����� "szCITY_NAME" �� ���� �������� � ���������� �������� �� "strCityName"</param>
	void SetCityName(const CString& strCityName, CITIES& oCity);

	///<summary>������� �������� ������� �� 'AREA_NAME' �� ������� ���� �������� ���������</summary>
	///<param name="strAreaName">����� �� ������ ����� �� ���� �������� ���� ��������</param>
	///<param name="oCity"> ����� �� �������� ����� �� ���� �������� ���� �������� �� "szAREA_NAME"</param>
	void SetAreaName(const CString& strAreaName, CITIES& oCity);

	///<summary>������� �������� ������� �� 'POSTAL_CODE' �� ������� ���� �������� ���������</summary>
	///<param name="nPostalCode">�������� ��� ����� �� ���� ������� ���� ��������</param>
	///<param name="oCity">����� �� �������� ����� �� ���� �������� ���� �������� �� "lPOSTAL_CODE"</param>
	void SetPostalCode(const long lPostalCode, CITIES& oCity);

	CCitiesArray citiesArray;
public:
	CityService();
	~CityService();

	///<summary>������� ������� �������� ���� �������� ����� ����� ����� �� ��� �� ������'strCityAreaName'.</summary>
	///<param name="strCityAreaName">��� �� ������</param>
	CITIES* GetByAreaName(const CString& strCityAreaName);

	///<summary>������� ������� �������� ���� �������� ����� ����� ����� �� ��� �� ����'strCityName'.</summary>
	///<param name="strCityName">��� �� ����</param>
	CITIES* GetByCityName(const CString& strCityName);

	///<summary>������� ������� �������� ���� �������� ����� ����� ����� �� �������� ��� 'lPostalCode'.</summary>
	///<param name="lPostalCode">�������� ���</param>
	CITIES* GetByPostalCode(const long lPostalCode);

	///<summary>
		/// ������� ��������� 'CITY_NAME' ���������� �� �����
		///  ����� ������ ��� � �������� ���� �������� 'strCurrentCityName'.
	///</summary>
	///<param name="strCurrentCityName">�������� ��� �� ������.</param>
	///<param name="strNewCityName">������ ��� �� ������.</param>
	///<param name="oCitiesArray">������� � ����� �� �� ����� ���� �� ���������� ������ ��� "strCurrentCityName".</param>
	void ChangeCityName(const CString& strCurrentCityName, const CString& strNewCityName);

	///<summary>������� ��������� 'CITY_NAME' �� ����� ������� ���� ��������.</summary>
	///<param name="�City">���������� ��� �����.</param>
	///<param name="newCityName">������ ��� �� ������.</param>
	void ChangeCityName(CITIES& �City, const CString& strNewCityName);

	///<summary>
		/// ������� ��������� 'AREA_NAME' ���������� �� �����
		///����� ������ ��� � �������� ���� �������� 'strCurrentCityAreaName'.
	///</summary>
	///<param name="newCityName">�������� ��� �� ��������.</param>
	///<param name="strNewCityAreaName">������ ��� �� ��������.</param>
	///<param name="oCitiesArray">����� � ����� �� �� ����� ����� �� ���������� "strCurrentCityAreaName".</param>
	void ChangeCityAreaName(const CString& strCurrentCityAreaName, const CString& strNewCityAreaName);

	///<summary>������� ��������� 'AREA_NAME' �� ����� ������� ���� ��������.</summary>
	///<param name="oCity">���������� ��� �����.</param>
	///<param name="strNewAreaName">�������� � ����� �� ���� ��������� �������� �������� �� � "szAREA_NAME".</param>
	void ChangeCityAreaName(CITIES& oCity, const CString& strNewAreaName);

	///<summary>
		///������� ��������� 'POSTAL_CODE' ���������� �� �����
		///����� ������ ��� � �������� ���� �������� 'strCityName'.
	///</summary>
	///<param name="strCityName">�������� ��� �� ������.</param>
	///<param name="nNewCityPosalCode">��� �������� ���.</param>
	///<param name="oCitiesArray">����� � ����� �� �� ����� ����� �� ���������� 'strCityName'.param>
	void ChangeCityPosalCodeByCityName(const CString& strCityName, const long lNewCityPosalCode);
	///<summary>������� ��������� 'POSTAL_CODE' ���������� �� ����� ������� ���� �������� 'pCity'.</summary>
	///<param name="�City">���������� ��� �����.</param>
	///<param name="nNewPostalCode">��� �������� ���.</param>
	void ChangeCityPostalCode(CITIES& �City, const long lNewPostalCode);

	///<summary>
		/// ������� �������� ������ �������� �������� � ������� ����� ����
		/// ��������, ����������� �� ����� ���� 'BaseService'.
	///</summary>
	/// <param name="citiesArray">����� � ����� �� �� ������� ������ ���������.</param>
	void AddDefaultElements() override;

	///<summary>
		///������� ���������� ���������� �� ����� �������
		///�� �� ��������� �� nIndex, ����������� �� ����� ���� 'BaseService'.
	///</summary>
	///<param name="nIndex">������� � ������.</param>
	///<param name="oArray">����� ��� ���������.</param> 
	void ShowElementInfoAtIndex(const long lIndex)override;
};


