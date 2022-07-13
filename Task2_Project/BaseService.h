
#pragma once

using namespace std;
//<summary>����� template-�� ���� �� ����� �������</summary>
template<class  T>
class BaseService
{

private:


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
		///������� ���������� ���������� �� ����� ������� �� �� ��������� �� nIndex.
		///������� ����������� �� ����� ���� 'BaseService'.
	///</summary>
	/// <param name="nIndex">������� �� �������� � ������.</param>
	T* CreatePointer(T o)
	{
		T* pCities = new T;
		*pCities = o;
		return pCities;
	};
};

template<class  T>
BaseService<T>::BaseService() {};
template<class  T>
BaseService<T>::~BaseService() {};