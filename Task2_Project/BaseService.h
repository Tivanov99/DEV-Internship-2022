
#pragma once

using namespace std;
//<summary>Базов template-ен клас за всики сървиси</summary>
template<class  T>
class BaseService
{

private:
	typedef CTypedPtrArray < CPtrArray, T*> CTypeArray;

public:

	BaseService();
	~BaseService();
	///<summary>
		/// Функция добавяща всички дефоутни елементи в подаден масив като аргумент.
		/// Функция пренаписана от базов клас 'BaseService'.
	/// </summary>
	///<param name="oArray">Масив в който ще се добавят всички стойности.</param>
	virtual void AddDefaultElements(CTypeArray& oArray) = 0;
	
	///<summary>
		///Функция принтираща информация за обект намиращ се на позицията на nIndex.
		///Функция пренаписана от базов клас 'BaseService'.
	///</summary>
	/// <param name="nIndex">Позиция на елемента в масива.</param>
	/// <param name="oArray">Масив с елементи.</param>
	virtual void ShowElementInfoAtIndex(const int nIndex, const CTypeArray& oArray) = 0;
	
	///<summary>Функция връщаща Pointer от подаден индекс като аргумент.</summary>
	/// <param name="nIndex">Позиция на елемента в масива.</param>
	/// <param name="oArray">Масив с обекти.</param>
	T* GetPointerAtIndex(const int nIndex, CTypeArray& oArray);
};


template<class  T>
T* BaseService<T>::GetPointerAtIndex(const int nIndex, CTypeArray& oArray)
{
	if (nIndex > oArray.GetCount() - 1)
		return NULL;

	T* pPointer = oArray.GetAt(nIndex);
	if(pPointer==NULL)
		return NULL;

	return pPointer;
};

template<class  T>
BaseService<T>::BaseService() {};
template<class  T>
BaseService<T>::~BaseService() {};