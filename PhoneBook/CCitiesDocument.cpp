#include "pch.h"
#include "CCitiesDocument.h"

CCitiesDocument::CCitiesDocument() {};
CCitiesDocument::~CCitiesDocument() {};


BOOL CCitiesDocument::OnNewDocument()
{
	oCitiesData.SelectAll(oCitiesArray);
};
void CCitiesDocument::UpdateAllViews(CView* pSender, LPARAM lHint = 0L,
	CObject* pHint = NULL)
{

};