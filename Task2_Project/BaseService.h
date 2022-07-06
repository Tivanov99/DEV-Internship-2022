
#pragma once

using namespace std;

template<class  T>
class BaseService 
{
private:
	typedef CTypedPtrArray < CPtrArray, T*> CTypeArray;
public:
	void ValidateIndex(const int nIndex, const int nLenght);
	virtual void AddDefaultElements(CTypeArray &oArray) = 0;
	virtual void ShowElementInfoAtIndex(const int nIndex, const CTypeArray &oArray) = 0;
	T* GetPointerAtIndex(const int nIndex, CTypeArray &oArray);
	void  RemoveAt(const int nIndex, const int count, CTypeArray &oArray);
};

template<class T>
void BaseService<T>::ValidateIndex(const int nIndex, const int nLenght)
{
	if (nIndex > nLenght) {
		throw invalid_argument("Index out of range!");
	}
	else if (nIndex < 0) {
		throw invalid_argument("Index should be possitive!");
	}
};

template<class  T>
T* BaseService<T>::GetPointerAtIndex(const int nIndex, CTypeArray& oArray) {
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
		oArray.RemoveAt(nIndex, count);
		oArray.FreeExtra();
	}
	catch (exception ex)
	{
		cout << ex.what() << endl;
	}
};