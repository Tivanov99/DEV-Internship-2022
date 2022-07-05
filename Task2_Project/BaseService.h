
#pragma once


template<class T>
class BaseService
{
private:

public:
	void ValidateIndex(const int nIndex, const int nLenght);
	virtual void AddDefaultElements(CTypedPtrArray<CPtrArray, class T*>& oArray) = 0;
	virtual void ShowElementInfoAtIndex(const int nIndex, const CTypedPtrArray<CPtrArray, class T*>& elementsCollection) = 0;
	 T* GetPointerAtIndex(const int nIndex, CTypedPtrArray<CPtrArray, class T*>& elementsCollection);
	void  RemoveAt(const int nIndex, const int count, CTypedPtrArray<CPtrArray, class T*>& elementsCollection);
};

