#include "pch.h"
#include "SqlQueries.h"

const CString SqlQueries::SelectAll = _T("SELECT * FROM %s");
const CString SqlQueries::SelectWhereID = _T("SELECT * FROM % s WHERE ID = % d");
const CString SqlQueries::EmptySelect = _T("SELECT TOP 0 * FROM %s");
const CString SqlQueries::SelectByPersonID = _T("SELECT * FROM %s WHERE PERSON_ID = %d");
