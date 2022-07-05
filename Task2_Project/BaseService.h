#pragma once
class BaseService
{
private:

public:
	void ValidateIndex(const int nIndex, const int nLenght);
	virtual void AddDefaultElements() = 0;
	virtual	void ShowElementInfoAtIndex(const int nIndex, const CTypedPtrArray<CPtrArray, class T*>& elementsCollection) = 0;
	template<class T> T* GetPointerAtIndex(const int nIndex, CTypedPtrArray<CPtrArray, class T*>& elementsCollection);
	template <class T>void  ReRemoveAt(const int nIndex, const int count, CTypedPtrArray<CPtrArray, class T*>& elementsCollection);
};

