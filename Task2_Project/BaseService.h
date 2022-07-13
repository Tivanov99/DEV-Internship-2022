#include"CSelfClearingTypedPtrArray.h";

#pragma once

using namespace std;
//<summary>����� template-�� ���� �� ����� �������</summary>
template<class  T>
class BaseService
{
protected:
	CSelfClearingTypedPtrArray<T> oSelfClearingTypedArray;

public:

	BaseService();
	~BaseService();
	///<summary>
		/// ������� �������� ������ �������� �������� � ������� ����� ���� ��������.
		/// ������� ����������� �� ����� ���� 'BaseService'.
	/// </summary>
	///<param name="oArray">����� � ����� �� �� ������� ������ ���������.</param>
	virtual void AddDefaultElements() = 0;
	
	///<summary>
		///������� ���������� ���������� �� ����� ������� �� �� ��������� �� nIndex.
		///������� ����������� �� ����� ���� 'BaseService'.
	///</summary>
	/// <param name="nIndex">������� �� �������� � ������.</param>
	/// <param name="oArray">����� � ��������.</param>
	virtual void ShowElementInfoAtIndex(const long lIndex) = 0;

	///<summary>
		///������� ��������� ���������.
	///</summary>
	/// <param name="oElement">������� �������� �����������.</param>
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