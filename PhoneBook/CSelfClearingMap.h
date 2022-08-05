#include <atlcomcli.h>
#include <map>
#pragma once
using namespace std;

template<class K, class T>
class CSelfClearingMap : public map< K, T>
{
public:
	CSelfClearingMap(){};
	~CSelfClearingMap()
	{
		RemoveAllElements();
	};
private:
	void RemoveAllElements()
	{
		map<K, T>::iterator itr;
		for (itr = begin();itr != end(); ++itr)
		{
			T pCurrent = itr->second;
			delete pCurrent;
			pCurrent = NULL;
		}
		clear();
	}
};

