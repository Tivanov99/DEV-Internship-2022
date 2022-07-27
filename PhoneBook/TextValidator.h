#pragma once
class TextValidator
{
	TextValidator();
	~TextValidator();
public:
	CString ValidateTextData(const CString strData, const int nMinLenght) const;
private:
	bool CheckForSymbols(const CString& strValue) const;
};

