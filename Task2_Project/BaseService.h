#pragma once
class BaseService
{
private:

public:
	void ValidateIndex(const int nIndex, const int nLenght);
	/*template<class T> void AddDefaultElements(CTypedPtrArray<CPtrArray, class T*>& elementsCollection) = 0;
	template<class T> void ShowElementInfoAtIndex(const int nIndex, const CTypedPtrArray<CPtrArray, class T*>& elementsCollection) = 0;*/
	template<class T> T* GetPointerAtIndex(const int nIndex, CTypedPtrArray<CPtrArray, class T*>& elementsCollection);
	template <class T>void  RemoveAt(const int nIndex, const int count, CTypedPtrArray<CPtrArray, class T*>& elementsCollection);
};

