
#pragma once


template<class T>
class BaseService
{
	typedef CTypedPtrArray < CPtrArray, T*> CTypeArray;
public:
	void ValidateIndex(const int nIndex, const int nLenght);
	virtual void AddDefaultElements(CTypeArray& oArray) = 0;
	virtual void ShowElementInfoAtIndex(const int nIndex, const CTypeArray& elementsCollection) = 0;
	T* GetPointerAtIndex(const int nIndex, CTypeArray& elementsCollection);
	void  RemoveAt(const int nIndex, const int count, CTypeArray& elementsCollection);
};

