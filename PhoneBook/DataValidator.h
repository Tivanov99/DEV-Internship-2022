#pragma once
class DataValidator
{
public:
	DataValidator();
	~DataValidator();
public:
	/// <summary>
	/// �������� �������� ����� ������ �� ���������� �� ������ ���� �������� ���� ��������, � ��� ���������� �� ������ ���������� � ����� ���������� ���������.
	/// </summary>
	/// <param name="strData">���������� �� ���������� ��������.</param>
	/// <param name="nMinLenght">���������� ��������� ������� �� ���������� ����.</param>
	/// <returns>��������� ��������� ����������� ������, ��� ��� ������.</returns>
	CString ValidateTextData(const CString& strData, const int nMinLenght) const;

	/// <summary>
	/// �������� '�������� ���' ��� ��������� �� �����.
	/// </summary>
	/// /// <param name="lPostalCode">���������� �� ���������� ��������.</param>
	/// <returns>���� 'true' ��� 'false' ������ ���� ���� ����� � �������.</returns>
	bool ValidatePostalCode(const long& lPostalCode) const;
private:
	/// <summary>
	/// ��������� �������� ���� ���� ������� ���� ������ ����� ����� � �����.
	/// </summary>
	/// <param name="strValue">���������� �� ����������� �������� � ���������� �����</param>
	/// <returns>true ��� ���� ������ ����� ����� � ����� � �������� ������ false.</returns>
	bool CheckForSymbols(const CString& strValue) const;
};

