#include <atlcomcli.h>
#include <afxtempl.h>

#pragma once
using namespace std;

template<class K, class T>
class CSelfClearingMap : public CMap<K, K, T ,T>
{
public:
	CSelfClearingMap() {};
	~CSelfClearingMap()
	{
		RemoveAllElements();
	};
private:
	void RemoveAllElements()
	{
		/*POSITION posPhoneNumbers = GetStartPosition();

		T* pRec;

		while (posPhoneNumbers)
		{

		}
		map<K, K, T*, T*>::iterator itr;
		for (itr = begin();itr != end(); ++itr)
		{
			T* pCurrent = itr->second;
			delete pCurrent;
			pCurrent = NULL;
		}
		RemoveAll();*/
	}
};

