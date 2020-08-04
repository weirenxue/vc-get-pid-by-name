#include <iostream>
#include <windows.h>
#include <tlhelp32.h>

int findProcessID(wchar_t processName[]);

int main()
{
	// Declare a wchar_t array to put process name.
	wchar_t processName[100];

	// Input the process name, such as "notepad.exe".
	printf("Enter your family name: ");
	scanf_s("%ls", processName);

	// Get the PID.
	int pid = findProcessID(processName);
	if (pid > 0) {
		printf("The process \"%ls\" is found.\n\tAnd PID is %d\n", processName, pid);
	}
	else {
		printf("Not found the process \"%ls\".\n", processName);
	}


	system("PAUSE");

	return 0;
}

int findProcessID(wchar_t processName[]) {
	// Enumerate all processes.
	PROCESSENTRY32 entry;

	// dwSize: The size of the structure, in bytes. 
	// Before calling the Process32First function, 
	// set this member to sizeof(PROCESSENTRY32). 
	// If you do not initialize dwSize, Process32First fails.
	entry.dwSize = sizeof(PROCESSENTRY32);

	// Includes all processes in the system in the snapshot.
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (Process32First(snapshot, &entry) == TRUE) {
		while (Process32Next(snapshot, &entry) == TRUE) {
			if (wcscmp(entry.szExeFile, processName) == 0) {
				// Match the process name.
				return entry.th32ProcessID;
			}
		}
	}
	return -1;
}