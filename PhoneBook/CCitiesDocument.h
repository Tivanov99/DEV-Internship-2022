#pragma once
#include "CCitiesData.h"

class CCitiesDocument :public CDocument
{
	// Constructor / Destructor
	// ----------------
public:
	CCitiesDocument();
	~CCitiesDocument();

	// Methods
	// ----------------
	BOOL OnNewDocument() override;
	// Members
	// ----------------
private:
		CCitiesData oCitiesData;
};

