#include "pch.h"
#include "CitiesTable.h"
#include "ErrorVisualizator.h"


/////////////////////////////////////////////////////////////////////////////
// CCitiesTable

CCitiesTable::CCitiesTable(CSession& oSession)
	:CBaseTable(oSession,_T("CITIES"))
{};
CCitiesTable::~CCitiesTable()
{
};


