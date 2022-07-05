#include "pch.h";
#include "BaseService.h";
using namespace std;


void BaseService::ValidateIndex(const int nIndex, const int nLenght)
{
	 if (nIndex > nLenght) {
		throw invalid_argument("Index out of range!");
	}
	else if (nIndex < 0) {
		throw invalid_argument("Index should be possitive!");
	}
};
template<class T> T* BaseService:: GetPointerAtIndex(const int nIndex, CTypedPtrArray<CPtrArray, class T*>& elementsCollection) {
	try
	{
		ValidateIndex(nIndex, elementsCollection);
		T* pPointer = NULL;
		pPointer = &elementsCollection[nIndex];
		return pPointer;
	}
	catch (exception ex)
	{
		cout << ex.what() << endl;
	}
};
template <class T> void BaseService::ReRemoveAt(const int nIndex, const int count, CTypedPtrArray<CPtrArray, class T*>& elementsCollection)
{
	try
	{
		ValidateIndex(nIndex, elementsCollection);
		elementsCollection.RemoveAt(nIndex, count);
		elementsCollection.FreeExtra();
	}
	catch (exception ex)
	{
		cout << ex.what() << endl;
	}
};