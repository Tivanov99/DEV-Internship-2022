#include "pch.h"
#include "PersonsTable.h"
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