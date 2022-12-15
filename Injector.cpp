#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>
#include <string>
#include <vector>
#include <algorithm>

std::vector<std::string> listProcess()
{
int bitType;
#ifdef _WIN64
	bitType = 64;
#else
	bitType = 86;
#endif

	std::cout << "DLL INJECTOR PLATFORM: " << bitType << std::endl;
	std::cout << "If your dll was compiled with a different platform type than the platform compiled with the injector, this will not work!\n";
   
    std::vector<std::string> pids;
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot != INVALID_HANDLE_VALUE)
    {
        PROCESSENTRY32 pe32 = { sizeof(PROCESSENTRY32) };
        if (Process32First(snapshot, &pe32))
        {
            do
            {
                //can use these if you want to list processess in a combo
                //pids.push_back(pe32.szExeFile);
                //std::sort(std::begin(pids), std::end(pids));
                if (pe32.szExeFile == "csgo.exe");
                {
                    pids.push_back(pe32.szExeFile);
                }

            } while (Process32Next(snapshot, &pe32) && pe32.szExeFile != "csgo.exe");
        }
        CloseHandle(snapshot);
    }
    return pids;
}

bool inject()
{
    DWORD exitCode = 0;

    std::string filePath = "C:\\Users\\forwa\\OneDrive\\Desktop\\CSESP\\ImGui-DirectX-9-Kiero-Hook-master\\Debug\\ImGui DirectX 9 Kiero Hook 2.dll";

    std::vector<std::string> pids = listProcess();
    Beep(330, 200);
    HANDLE snapshot = 0;
    PROCESSENTRY32 pe32 = { 0 };
    pe32.dwSize = sizeof(PROCESSENTRY32);
    snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    Process32First(snapshot, &pe32);
    do {
        if (strcmp(pe32.szExeFile, "csgo.exe") == 0) {

            HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, true, pe32.th32ProcessID);
            if (!process) {

                std::cout << "Could not inject!\n";
                Sleep(3000);
                CloseHandle(process);
                return 0;
            }

            void* lpBaseAddress = VirtualAllocEx(process, NULL, strlen(filePath.c_str()), MEM_COMMIT, PAGE_READWRITE);

            WriteProcessMemory(process, lpBaseAddress, filePath.c_str(), strlen(filePath.c_str()) + 1, NULL);

            //Creating the thread
            //Loadlib lives in kernel32
            HMODULE kernel32base = GetModuleHandle("kernel32.dll");

            HANDLE thread = CreateRemoteThread(process, NULL, 0, (LPTHREAD_START_ROUTINE)GetProcAddress(kernel32base, "LoadLibraryA"), lpBaseAddress, 0, NULL);

            WaitForSingleObject(thread, INFINITE);
            GetExitCodeThread(thread, &exitCode);

            VirtualFreeEx(process, lpBaseAddress, 0, MEM_RELEASE);
            CloseHandle(thread);
            CloseHandle(process);
            break;
        }

    } while (Process32Next(snapshot, &pe32));

    return true;
}

int main()
{
	//run inject
	inject();
}
