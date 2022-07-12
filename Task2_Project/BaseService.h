
#pragma once

using namespace std;
//<summary>����� template-�� ���� �� ����� �������</summary>
template<class  T>
class BaseService
{

private:
	typedef CTypedPtrArray < CPtrArray, T*> CTypeArray;

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
	virtual void ShowElementInfoAtIndex(const int nIndex) = 0;
};

template<class  T>
BaseService<T>::BaseService() {};
template<class  T>
BaseService<T>::~BaseService() {};