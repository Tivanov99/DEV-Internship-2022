#pragma once
#include "CCitiesData.h"

class CCitiesDocument :public CDocument
{
	// Constructor / Destructor
	// ----------------
public:
	CCitiesDocument();
	~CCitiesDocument();


	// Members
	// ----------------
private:
		CCitiesData oCitiesData;
};

