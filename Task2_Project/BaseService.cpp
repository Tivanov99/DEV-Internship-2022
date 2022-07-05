#include "pch.h";
#include "BaseService.h";
using namespace std;


void BaseService<class T>::ValidateIndex(const int nIndex, const int nLenght)
{
	 if (nIndex > nLenght) {
		throw invalid_argument("Index out of range!");
	}
	else if (nIndex < 0) {
		throw invalid_argument("Index should be possitive!");
	}
};
T* BaseService<class T>:: GetPointerAtIndex(const int nIndex, CTypeArray& oArray) {
	try
	{
		ValidateIndex(nIndex, oArray.GetCount()-1);
		T* pPointer = NULL;
		pPointer = oArray[nIndex];
		return pPointer;
	}
	catch (exception ex)
	{
		cout << ex.what() << endl;
	}
};
void BaseService<T>::RemoveAt(const int nIndex, const int count, CTypeArray& oArray)
{
	try
	{
		ValidateIndex(nIndex, oArray.GetCount()-1);
		oArray.RemoveAt(nIndex, count);
		oArray.FreeExtra();
	}
	catch (exception ex)
	{
		cout << ex.what() << endl;
	}
};