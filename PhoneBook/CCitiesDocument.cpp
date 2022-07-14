#include "pch.h"
#include "CCitiesDocument.h"

CCitiesDocument::CCitiesDocument() {};
CCitiesDocument::~CCitiesDocument() {};


BOOL CCitiesDocument::OnNewDocument()
{
	oCitiesData.SelectAll(oCitiesArray);
};