#pragma once
#include "Structures.h"
class CCitiesTable
{
public:
	CCitiesTable()
	{
			
	}
	BOOL SelectAll(CCitiesArray& oCitiesArray);
	BOOL SelectWhereID(const long lID, CITIES& recCities);
	BOOL UpdateWhereID(const long lID, const CITIES& recCities);
	BOOL Insert(const CITIES& recCities);
	BOOL DeleteWhereID(const long lID);
};

