#pragma once
static class ErrorVisualizator
{
public:
	/// <summary>
	///  ������� ����� ������� ��������� ��� ��������� ���� �� ��������� �� �������� �� ������.
	/// </summary>
	/// <param name="strErrorMessage">����� ����� ������� �������� ���������� �� �������� ������.</param>
	/// <param name="strQuery">����� ����� ������� �������� ������.</param>
	static void ShowErrorMessage(const LPCSTR strErrorMessage, const CString& strQuery);
};

