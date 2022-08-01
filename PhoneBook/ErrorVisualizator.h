#pragma once
static class ErrorMessageVisualizator
{
public:
	/// <summary>
	///  Функция която извежда съобщение при неуспешен опит за прочитане на резултат от заявка.
	/// </summary>
	/// <param name="strErrorMessage">Обект който съдържа подробно разяснение за текущата грешка.</param>
	/// <param name="strQuery">Обект който съдържа текущата заявка.</param>
	static void ShowErrorMessage(const LPCSTR strErrorMessage, const CString& strQuery);
};

