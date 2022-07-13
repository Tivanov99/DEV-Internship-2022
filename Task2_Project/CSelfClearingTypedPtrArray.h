#pragma once
template<class T>
class CSelfClearingTypedPtrArray : public CTypedPtrArray<CPtrArray, T*>
{
public:
	CSelfClearingTypedPtrArray()
	{};
	~CSelfClearingTypedPtrArray()
	{
		for (INT_PTR i = 0; i < GetCount(); i++)
		{
			T* pCurrent = GetAt(i);
			delete pCurrent;
			pCurrent = NULL;
		}
		RemoveAll();
	};
};
