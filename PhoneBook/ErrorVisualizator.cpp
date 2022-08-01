#include "pch.h"
#include "ErrorVisualizator.h"

void ErrorMessageVisualizator::ShowErrorMessage(const LPCSTR strErrorMessage, const CString& strQuery)
{
	CString strError;
	if (strQuery.GetString() != NULL)
	{
		strError.Format((CString)strErrorMessage, strQuery);
	}
	else
	{
		strError.Format((CString)strErrorMessage);
	}
	AfxMessageBox(strError);
}
