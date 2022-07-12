#pragma once
#include "BaseService.h";
#include "Structures.h";

class PhoneTypeService : public BaseService<PHONE_TYPES>
{
private:
	///<summary>Функция задаваща стойност на мембър 'PHONE_TYPE' на подаден обект като аргумент.</summary>
	/// <param name="strType">Вид телефонен номер.</param>
	/// <param name="oPhone">Референция към обект.</param>
	void SetPhoneType(CString& strType, PHONE_TYPES& oPhone);
public:
	PhoneTypeService();
	~PhoneTypeService();

	///<summary>
		/// Функция добавяща всички дефоутни елементи в подаден масив като аргумент.
		/// Функция пренаписана от базов клас 'BaseService'.
	/// </summary>
	///<param name="citiesArray">Масив в който ще се добавят всички стойности.</param>
	void AddDefaultElements(CPhoneTypesArray& oArray) override;

	///<summary>
		///Функция принтираща информация за обект намиращ се на позицията на nIndex.
		///Функция пренаписана от базов клас 'BaseService'.
	///</summary>
	/// <param name="оnIndex">Позиция на елемента в масива.</param>
	/// <param name="оoArray">Масив с елементи.</param>
	void ShowElementInfoAtIndex(const int nIndex, const CPhoneTypesArray& oArray) override;
};

