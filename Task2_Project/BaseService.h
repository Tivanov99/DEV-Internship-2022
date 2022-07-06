
#pragma once


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

