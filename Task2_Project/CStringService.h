#pragma once
using namespace std;

class CStringService
{
public:
	CStringService()
	{

	}
	void AppendListOfIntegerArgs(CString& strDummy,int nArgsCount, ...) {
		va_list vl;
		va_start(vl, nArgsCount);
		va_arg(vl, int);
		for (size_t i = 0; i < nArgsCount; i++)
		{
			strDummy.AppendFormatV(_T("%d, "), vl);
			va_arg(vl, int);
		}
		va_end(vl);
	}
	void PrintLeftSide(CString& strDummy) {
		int nMiddle = strDummy.GetLength() / 2;
		cout << "\nPrinting the left side.\n";
		_tprintf(_T("%s"), (LPCTSTR)strDummy.Left(nMiddle));
	}
	void PrintCStringAsString(CString& strDummy) {
		_tprintf(_T("%s"), (LPCTSTR)strDummy);
	}
	void Compare(CString& comparator, CString compared) {
		int compareResult = comparator.Compare((LPCTSTR)compared);

		switch (compareResult)
		{
		case -1:cout << "\nCompared value is greater."; break;
		case 1: cout << "\nCompared value is less."; break;
		default:
			cout << "\nValues are equal!";
			break;
		}
	}
};

