
#pragma once

using namespace std;
//<summary>����� template-�� ���� �� ����� �������</summary>
template<class  T>
class BaseService 
{

private:
	typedef CTypedPtrArray < CPtrArray, T*> CTypeArray;

public:

	BaseService()
	{

	}
	~BaseService()
	{

	}
	//<summary>������� ���������� ��������� �� nIndex � ���������� ������ nLenght.</summary>
	void ValidateIndex(const int nIndex, const int nLenght);
	//<summary>������� �������� ������ �������� �������� � ������� ����� ���� ��������.</summary>
	virtual void AddDefaultElements(CTypeArray &oArray) = 0;
	//<summary>������� ���������� ���������� �� ����� ������� �� �� ��������� �� nIndex, ����� ��� ������ � ������������.</summary>
	virtual void ShowElementInfoAtIndex(const int nIndex, const CTypeArray &oArray) = 0;
	//<summary>������� ������� Pointer �� ������� ������ ���� ��������.</summary>
	T* GetPointerAtIndex(const int nIndex, CTypeArray &oArray);
	//<summary>������� ���������� ��������� ���� Pointer-� 'count'��������� �� ������� ���� �������� ����� 'nIndex'</summary>
	void  RemoveAt(const int nIndex, const int count, CTypeArray &oArray);
};

template<class T>
void BaseService<T>::ValidateIndex(const int nIndex, const int nLenght)
{
	if (nIndex > nLenght)
	{
		throw invalid_argument("Index out of range!");
	}
	else if (nIndex < 0)
	{
		throw invalid_argument("Index should be possitive!");
	}
};

template<class  T>
T* BaseService<T>::GetPointerAtIndex(const int nIndex, CTypeArray& oArray)
{
	try
	{
		ValidateIndex(nIndex, oArray.GetCount() - 1);
		T* pPointer = NULL;
		pPointer = oArray[nIndex];
		return pPointer;
	}
	catch (exception ex)
	{
		cout << ex.what() << endl;
	}
};

template<class  T>
void BaseService<T>::RemoveAt(const int nIndex, const int count, CTypeArray& oArray)
{
	try
	{
		ValidateIndex(nIndex, oArray.GetCount() - 1);

		T* pCurrent = oArray[nIndex];
		oArray.RemoveAt(nIndex, count);
		delete pCurrent;
		pCurrent = NULL;
		oArray.FreeExtra();
	}
	catch (exception ex)
	{
		cout << ex.what() << endl;
	}
};