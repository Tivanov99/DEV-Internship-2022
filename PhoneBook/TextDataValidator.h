#pragma once
class TextDataValidator
{
	// Constructor/Destructor
	// ----------------
public:
	TextDataValidator();
	~TextDataValidator();

	// Methods
	// ----------------
public:
	/// <summary>�������� �������� ����� ������ �� ���������� �� ������ ���� �������� ���� ��������, � ��� ���������� �� ������ ���������� � ����� ���������� ���������.</summary>
	/// <param name="strData">���������� �� ���������� ��������.</param>
	/// <param name="nMinLenght">���������� ��������� ������� �� ���������� ����.</param>
	/// <returns>��������� ��������� ����������� ������, ��� ��� ������.</returns>
	CString ValidateTextData(const CString& strData, const int nMinLenght) const;

private:
	/// <summary>��������� �������� ���� ���� ������� ���� ������ ����� ����� � �����.</summary>
	/// <param name="strValue">���������� �� ����������� �������� � ���������� �����</param>
	/// <returns>true ��� ���� ������ ����� ����� � ����� � �������� ������ false.</returns>
	bool CheckForSymbols(const CString& strValue) const;
};

