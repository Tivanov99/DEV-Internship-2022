#pragma once
template<class T>
class CSelfClearingTypedPtrArray : public CTypedPtrArray<CPtrArray, T*>
{
	//Constructor/Destructor
	//------------------
public:
	CSelfClearingTypedPtrArray()
	{};
	~CSelfClearingTypedPtrArray()
	{
		RemoveAllElements();
	};
	//Methods
	//-----------------
public:
	void RemovePointerAt(INT_PTR nIndex);
private:
	void RemoveAllElements()
	{
		for (INT_PTR i = 0; i < GetCount(); i++)
		{
			RemovePointerAt(i);
		}
		RemoveAll();
	}
};

template<class T>
void CSelfClearingTypedPtrArray<T>::RemovePointerAt(INT_PTR nIndex)
{
	T* pCurrent = GetAt(nIndex);
	pCurrent = NULL; 
	delete pCurrent;
	RemoveAt(nIndex);
}