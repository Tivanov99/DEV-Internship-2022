#pragma once
#include <afxstr.h>
#include "TextDataValidator.h"
class CCitiesDataValidator : public TextDataValidator
{
public:
	CCitiesDataValidator();
	~CCitiesDataValidator();
public:
	/// <summary>
	/// �������� '�������� ���' ��� ��������� �� �����.
	/// </summary>
	/// /// <param name="lPostalCode">���������� �� ���������� ��������.</param>
	/// <returns>���� 'true' ��� 'false' ������ ���� ���� ����� � �������.</returns>
	bool ValidatePostalCode(const long& lPostalCode) const;
};

