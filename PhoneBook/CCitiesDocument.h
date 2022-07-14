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
	
	void UpdateAllViews(CView* pSender, LPARAM lHint = 0L,
		CObject* pHint = NULL);
	// Members
	// ----------------
private:
		CCitiesData oCitiesData;
		CSelfClearingTypedPtrArray<CITIES> oCitiesArray;
};

