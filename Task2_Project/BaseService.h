#include"CSelfClearingTypedPtrArray.h";

#pragma once

using namespace std;
//<summary>Базов template-ен клас за всики сървиси</summary>
template<class  T>
class BaseService
{
protected:
	CSelfClearingTypedPtrArray<T> oSelfClearingTypedArray;

public:

	BaseService();
	~BaseService();
	///<summary>
		/// Функция добавяща всички дефоутни елементи в подаден масив като аргумент.
		/// Функция пренаписана от базов клас 'BaseService'.
	/// </summary>
	///<param name="oArray">Масив в който ще се добавят всички стойности.</param>
	virtual void AddDefaultElements() = 0;
	
	///<summary>
		///Функция принтираща информация за обект намиращ се на позицията на nIndex.
		///Функция пренаписана от базов клас 'BaseService'.
	///</summary>
	/// <param name="nIndex">Позиция на елемента в масива.</param>
	/// <param name="oArray">Масив с елементи.</param>
	virtual void ShowElementInfoAtIndex(const long lIndex) = 0;

	///<summary>
		///Функция създаваща показател.
	///</summary>
	/// <param name="oElement">Елемент съдържащ стойностите.</param>
	T* CreatePointer(T oElement)
	{
		T* pCities = new T;
		*pCities = oElement;
		return pCities;
	};
};

template<class  T>
BaseService<T>::BaseService() {};
template<class  T>
BaseService<T>::~BaseService() {};