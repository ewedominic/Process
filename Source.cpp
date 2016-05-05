#include <iostream>
#include <windows.h>
#include <TlHelp32.h>
#include <Psapi.h>

#pragma comment( lib, "Psapi.lib" )

int main()
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, GetCurrentProcessId());
	HANDLE hProcess;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(pe32);

	TCHAR ImageFileName[MAX_PATH];

	if (Process32First(hSnapshot, &pe32))
	{
		do
		{
			hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);

			SetConsoleTextAttribute(hConsole, 0x02);

			for (int i = 0; i < 40; i++)
				std::cout << '-';

			SetConsoleTextAttribute(hConsole, 0x07);

			printf("%s\t%d", pe32.szExeFile, pe32.th32ProcessID);
			GetProcessImageFileName(hProcess, ImageFileName, sizeof(ImageFileName));
			printf("\n%s\n", ImageFileName);

			SetConsoleTextAttribute(hConsole, 0x02);
			for (int i = 0; i < 40; i++)
				std::cout << '-';


		} while (Process32Next(hSnapshot, &pe32));
	}

	CloseHandle(hSnapshot);

	std::cin.get();
	return 0;
}