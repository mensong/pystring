
#include "pystring.h"
#include "pywstring.h"
#include <iostream>

#define MyAssert(a) \
	if ((a)) printf("\n[ pass ] %s\n", #a); \
	else printf("\n[unpass] %s\n", #a);

void main()
{
	{
		std::wstring s = L"123";
		int realSize = (int)s.size();
		s += L'\0';s += L'\0';
		MyAssert(pywstring::normalizecstring(s).size()==realSize);

	}

	{
		MyAssert(pywstring::capitalize(L"i love you")[0] == L'I');

	}

	{

		MyAssert(pywstring::center(L"mensong", 20) == L"      mensong       ");
	}

	{
		MyAssert(pywstring::count(L"abc123abc456abc789abc000abc000abc000", L"abc") == 6);
	}
	
	{
		MyAssert(pywstring::expandtabs(L"12345\t", 8) == L"12345   ");
	}

	{
		MyAssert(pywstring::isalnum(L"abd123") && !pywstring::isalnum(L"abd.123"));
	}

	{
		MyAssert(pywstring::isalpha(L"abcd") && !pywstring::isalpha(L"abcd123"));
	}

	{
		MyAssert(pywstring::isdigit(L"0123456789") && !pywstring::isdigit(L"0123456789abc"));
	}

	{
		MyAssert(
			pywstring::islower(L"abcdefghijklmnopqrstuvwxyz") && 
			!pywstring::islower(L"Abcdefghijklmnopqrstuvwxyz") &&
			!pywstring::islower(L"0") &&
			!pywstring::islower(L"我")
			);
	}

	{
		MyAssert(
			pywstring::isupper(L"ABCDEFGHIJKLMNOPQRSTUVWXYZ") && 
			!pywstring::isupper(L"aBCDEFGHIJKLMNOPQRSTUVWXYZ") &&
			!pywstring::isupper(L"0") &&
			!pywstring::isupper(L"我")
			);
	}

	{
		MyAssert(pywstring::isspace(L" \t\n\v\f\r"));
	}

	{
		MyAssert(pywstring::istitle(L"I Love\tYou") && pywstring::istitle(L" I Love\tYou ") && !pywstring::istitle(L"i love\tyou"));
	}

	{
		std::vector<std::wstring> seq;
		seq.push_back(L"1");
		seq.push_back(L"2");
		seq.push_back(L"3");
		MyAssert(pywstring::join(L" ", seq) == L"1 2 3");
	}

	{
		MyAssert(pywstring::ljust(L"12345", 10) == L"12345     ");
	}

	{
		MyAssert(pywstring::rjust(L"12345", 10) == L"     12345");
	}

	{
		MyAssert(pywstring::lower(L"我ABCD123") == L"我abcd123");
	}

	{
		MyAssert(pywstring::upper(L"我abcd123") == L"我ABCD123");
	}

	{
		MyAssert(pywstring::lstrip(L" \t\n\v\f\r我abcd123") == L"我abcd123");
		MyAssert(pywstring::lstrip(L"234365650abcd123", L"1234567890") == L"abcd123");

		MyAssert(pywstring::rstrip(L"我abcd123 \t\n\v\f\r") == L"我abcd123");
		MyAssert(pywstring::rstrip(L"234365650abcd123", L"1234567890") == L"234365650abcd");

		MyAssert(pywstring::strip(L"234365650abcd123", L"1234567890") == L"abcd");
	}

	{
		MyAssert(pywstring::mul(L"Abc", 3) == L"AbcAbcAbc");
	}

	{
		MyAssert([]() -> bool{
			std::vector<std::wstring> res; 
			pywstring::partition(L"key=val=123", L"=", res);
			return res.size() == 3 && res[0] == L"key" && res[1] == L"=" && res[2] == L"val=123";
		}());
	}

	{
		MyAssert([]() -> bool{
			std::vector<std::wstring> res; 
			pywstring::rpartition(L"key=val=123", L"=", res);
			return res.size() == 3 && res[0] == L"key=val" && res[1] == L"=" && res[2] == L"123";
		}());
	}

	{
		MyAssert(pywstring::replace(L"hello123world123!", L"123", L" ") == L"hello world !");
	}

	{
		MyAssert(pywstring::startswith(L"AbCd.SchDoc", L"AbCd"));
	}

	{
		MyAssert(pywstring::endswith(L"AbCd.SchDoc", L".SchDoc"));
	}

	{
		MyAssert([]() -> bool{
			std::vector<std::wstring> res;
			pywstring::split(L"0|1|2", res, L"|");
			return res.size() == 3 && res[0] == L"0" && res[1] == L"1" && res[2] == L"2";
		}());
		MyAssert([]() -> bool{
			std::vector<std::wstring> res;
			pywstring::split(L"0 1\t2", res);
			return res.size() == 3 && res[0] == L"0" && res[1] == L"1" && res[2] == L"2";
		}());

		MyAssert([]() -> bool{
			std::vector<std::wstring> res;
			pywstring::split(L"C:\\Windows\\System32", res, L"\\", 1);
			return res.size() == 2 && res[0] == L"C:" && res[1] == L"Windows\\System32";
		}());
		MyAssert([]() -> bool{
			std::vector<std::wstring> res;
			pywstring::rsplit(L"C:\\Windows\\System32", res, L"\\", 1);
			return res.size() == 2 && res[0] == L"C:\\Windows" && res[1] == L"System32";
		}());
	}

	{
		MyAssert([]() -> bool{
			std::vector<std::wstring> res;
			pywstring::splitlines(L"123\r\n456\n789", res);
			return res.size() == 3 && res[0] == L"123" && res[1] == L"456" && res[2] == L"789";
		}());
	}

	{
		MyAssert(
			pywstring::startswith(L"AbCd.SchDoc", L"abcd", true) && 
			!pywstring::startswith(L"AbCd.SchDoc", L"abcd", false)
			);
	}

	{
		MyAssert(
			pywstring::endswith(L"AbCd.SchDoc", L".schdoc", true) && 
			!pywstring::endswith(L"AbCd.SchDoc", L".schdoc", false)
			);
	}

	{
		 MyAssert(pywstring::swapcase(L"Hello World! 123") == L"hELLO wORLD! 123");
	}

	{
		MyAssert(pywstring::title(L"hello world! 123") == L"Hello World! 123");
	}

	{
		std::map<std::wstring::value_type, std::wstring::value_type> table;
		table.insert(std::make_pair('h', 'H'));
		table.insert(std::make_pair('w', 'W'));
		table.insert(std::make_pair('1', '\0'));
		table.insert(std::make_pair('2', '\0'));
		table.insert(std::make_pair('3', '\0'));
		MyAssert(pywstring::translate(L"hello world123", table) == L"Hello World");
	}

	{
		MyAssert(pywstring::zfill(L"12345", 10) == L"0000012345");
	}

	{
		MyAssert(pywstring::alignment(L"12345", 10, 1, ' ') == L"  12345   ");
	}

	{
		std::wstring s = L"123";
		s += L'\0';
		MyAssert(pywstring::length(s) == 3);
	}

	{
		std::wstring s;
		s += L'\0';
		MyAssert(pywstring::iscempty(s));
	}

	{
		MyAssert(pywstring::equal(L"Abc", L"abc", true) && !pywstring::equal(L"Abc", L"abc", false));
	}

	{
		std::wstring s1 = L"123";
		s1 += L'\0';
		MyAssert(pywstring::concat(s1, L"abc") == L"123abc");
	}

	system("pause");
}