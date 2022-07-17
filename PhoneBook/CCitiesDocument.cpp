#include "pch.h"
#include "CCitiesDocument.h"

CCitiesDocument::CCitiesDocument() {};
CCitiesDocument::~CCitiesDocument() {};


BOOL CCitiesDocument::OnNewDocument()
{
	return oCitiesData.SelectAll(oCitiesArray);
};

const CSelfClearingTypedPtrArray<CITIES>& CCitiesDocument::GetAllData()
{
	return oCitiesArray;
}
