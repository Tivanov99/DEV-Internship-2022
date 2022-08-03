#include "pch.h"
#include "CPersonsTable.h"
#include "ErrorVisualizator.h"


/////////////////////////////////////////////////////////////////////////////
// CPersonsTable

CPersonsTable::CPersonsTable(CSession& oSession)
	:CBaseTable(oSession,_T("PERSONS"))
{
};
CPersonsTable::~CPersonsTable()
{
};