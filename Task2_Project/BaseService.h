
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
	virtual void AddDefaultElements(CTypeArray& oArray) = 0;
	
	///<summary>
		///������� ���������� ���������� �� ����� ������� �� �� ��������� �� nIndex.
		///������� ����������� �� ����� ���� 'BaseService'.
	///</summary>
	/// <param name="nIndex">������� �� �������� � ������.</param>
	/// <param name="oArray">����� � ��������.</param>
	virtual void ShowElementInfoAtIndex(const int nIndex, const CTypeArray& oArray) = 0;
	
	///<summary>������� ������� Pointer �� ������� ������ ���� ��������.</summary>
	/// <param name="nIndex">������� �� �������� � ������.</param>
	/// <param name="oArray">����� � ������.</param>
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