#pragma once
#include <string>
#include "Structures.h"
#include "BaseService.h"

using namespace std;

class PhoneNumberService :public BaseService<PHONE_NUMBERS>
{
private:
	///<summary>
		/// Попълва 'PHONE_NUMBER' със стойността 'oPhoneNumber' на обект подаден като аргумент 'phoneNumber'.
	/// </summary>
	/// <param name="strPhoneNumber">Телефонен номер.</param>
	/// <param name="oPhoneNumber">Референция към обект.</param>
	void SetPhoneNumber(const CString& strPhoneNumber, PHONE_NUMBERS& oPhoneNumber);
public:

	PhoneNumberService();
	~PhoneNumberService();
	
	///<summary>
		//Функция променяща стойността на 'PHONE_NUMBER' на обект чиято текуща сойност е 'oldPhoneNumber'.
	///</summary>
	/// <param name="strCurrentPhoneNumber">Текущ телефонен номер.</param>
	/// <param name="strNewPhoneNumber">Нов телефонен номер.</param>
	void ChangePhoneNumber(const CString &strCurrentPhoneNumber, const CString &strNewPhoneNumber,
		CPhoneNumbersArray& oPhoneTypesArray);


	///<summary>
		/// Функция променяща стойността на 'PHONE_NUMBER' на обект подаден като аргумент 'pOldPhoneNumberElement' .
	/// </summary>
	/// <param name="оPhoneNumber">Референция към обект.</param>
	/// <param name="strNewPhoneNumber">Нов телефонен номер.</param>
	void ChangePhoneNumber(PHONE_NUMBERS& оPhoneNumber, const CString &strNewPhoneNumber);
	
	///<summary>
		///Функция принтираща информация за обект намиращ се на позицията на nIndex.
		///Функция пренаписана от базов клас 'BaseService'.
	///</summary>
	/// <param name="оnIndex">Позиция на елемента в масива.</param>
	/// <param name="оoArray">Масив с елементи.</param>
	void ShowElementInfoAtIndex(const int nIndex, const CPhoneNumbersArray& oArray) override;
	
	///<summary>
		/// Функция добавяща всички дефоутни елементи в подаден масив като аргумент.
		/// Функция пренаписана от базов клас 'BaseService'.
	/// </summary>
	///<param name="citiesArray">Масив в който ще се добавят всички стойности.</param>
	void AddDefaultElements(CPhoneNumbersArray& citiesArray) override;
};

