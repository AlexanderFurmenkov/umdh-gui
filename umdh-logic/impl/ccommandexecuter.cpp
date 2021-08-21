#include "ccommandexecuter.h"

#pragma warning(push, 0)
#include <windows.h>
#pragma warning(pop)

#pragma comment(lib, "shell32.lib")

using namespace logic;

namespace
{
    void executeUmdhCommandWithElevationOfPrivileges(std::wstring pathToApp, std::wstring args)
    {
        SHELLEXECUTEINFO shExInfo = {};
        shExInfo.cbSize = sizeof(shExInfo);
        shExInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
        shExInfo.hwnd = 0;
        shExInfo.lpVerb = L"runas";
        shExInfo.lpFile = pathToApp.c_str();
        shExInfo.lpParameters = args.c_str();
        shExInfo.lpDirectory = 0;
        shExInfo.nShow = SW_SHOW;
        shExInfo.hInstApp = 0;

        if (ShellExecuteEx(&shExInfo))
        {
            WaitForSingleObject(shExInfo.hProcess, INFINITE);
            CloseHandle(shExInfo.hProcess);
        }
    }


    void executeUmdhCommand(std::wstring pathToApp, std::wstring args)
    {
        STARTUPINFO si;
        LPCTSTR lpAppName = pathToApp.c_str();
        args = L" " + args;
        LPTSTR lpArgs = _wcsdup(args.c_str());

        PROCESS_INFORMATION pi;
        DWORD exitCode = 0;

        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        ZeroMemory(&pi, sizeof(pi));

        if (!CreateProcess(lpAppName,
                           lpArgs,
                           NULL,
                           NULL,
                           FALSE,
                           CREATE_NEW_CONSOLE,
                           NULL,
                           NULL,
                           &si,
                           &pi)
            )
        {
            executeUmdhCommandWithElevationOfPrivileges(pathToApp, args);
            return;
        }

        WaitForSingleObject(pi.hProcess, INFINITE);
        free(lpArgs);

        if (!GetExitCodeProcess(pi.hProcess, &exitCode)) {
            return;
        }

        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
}

void logic::CCommandExecuter::execute(std::wstring pathToApp, std::wstring args)
{
    executeUmdhCommand(std::move(pathToApp), std::move(args));
}
