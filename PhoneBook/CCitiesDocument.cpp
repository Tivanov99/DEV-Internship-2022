#include "pch.h"
#include "CCitiesDocument.h"




CCitiesDocument::CCitiesDocument() {};
CCitiesDocument::~CCitiesDocument() {};


BOOL CCitiesDocument::OnNewDocument()
{
	return m_CitiesData.SelectAll(oCitiesArray);
};

const CSelfClearingTypedPtrArray< CITIES>& CCitiesDocument::GetAllData()
{
	return oCitiesArray;
}
