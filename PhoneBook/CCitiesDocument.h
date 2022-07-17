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
	virtual BOOL OnNewDocument();
	const CSelfClearingTypedPtrArray< CITIES>& GetAllData();


	// Members
	// ----------------
private:
		CCitiesData m_CitiesData;
		CSelfClearingTypedPtrArray< CITIES> oCitiesArray;
};

