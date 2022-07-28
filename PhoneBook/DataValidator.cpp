#include "pch.h"
#include "DataValidator.h"


DataValidator::DataValidator() {};
DataValidator::~DataValidator() {};


CString DataValidator::ValidateTextData(const CString& strData, const int nMinLenght) const
{
	CString strErrorMessage;

	if (strData.GetLength() < nMinLenght)
	{
		strErrorMessage.AppendFormat(_T("The minimum length must be at least %i! "), nMinLenght);
	}
	if (!CheckForSymbols(strData))
	{
		strErrorMessage.Append(_T("The text field contains forbidden sybmols!"));
	}

	return strErrorMessage;
}


bool DataValidator::CheckForSymbols(const CString& strValue) const
{
	for (INT_PTR i = 0; i < strValue.GetLength(); i++)
	{
		switch (strValue.GetAt(i))
		{
		case '!':;
		case '.':;
		case '?':;
		case ';':;
		case ':':;
		case ',':;
		case '|':;
		default:
			continue;
		}
		return false;
	}
	return true;
}

bool DataValidator::ValidatePostalCode(const long& lPostalCode)const
{
	return	lPostalCode <= 0 ? false : true;
}
