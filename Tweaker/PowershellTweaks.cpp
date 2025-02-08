#include "PowershellTweaks.h"
#include "config.h"
#include "iostream"
#include <windows.h>
#include <vector>


bool ExecutePowerShellCommand(const std::string& command) {
    std::string fullCommand = "powershell.exe -Command \"" + command + "\"";
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&pi, sizeof(pi));


    if (!CreateProcessA( NULL, const_cast<char*>(fullCommand.c_str()), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) 
    {
        std::cerr << "CreateProcess failed (" << GetLastError() << ").\n";
        return false;
    }
    WaitForSingleObject(pi.hProcess, INFINITE);

    DWORD exitCode;
    if (!GetExitCodeProcess(pi.hProcess, &exitCode)) {
        std::cerr << "GetExitCodeProcess failed (" << GetLastError() << ").\n";
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        return false;
    }

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return exitCode == 0;
}

int PowershellTweaks::DeletePackages(config::apps apps) {
    std::vector<std::pair<bool, std::string>> packages = {
        {apps.paint, "Microsoft.Paint"},
        {apps.music, "Microsoft.ZuneMusic"},
        {apps.phone, "Microsoft.YourPhone"},
        {apps.maps, "Microsoft.WindowsMaps"},
        {apps.camera, "Microsoft.WindowsCamera"},
        {apps.people, "Microsoft.People"},
        {apps.clipchamp, "Microsoft.Clipchamp"},
        {apps.xbox, "Microsoft.Xbox.TCUI"},
        {apps.xbox, "Microsoft.XboxGameOverlay"},
        {apps.xbox, "Microsoft.XboxSpeechToTextOverlay"},
        {apps.xbox, "Microsoft.XboxGamingOverlay"},
        // {apps.xbox, "Microsoft.XboxGameCallableUI"}, 
        {apps.xbox, "Microsoft.XboxIdentityProvider"},
        {apps.todo, "Microsoft.Todos"},
        {apps.alarms, "Microsoft.WindowsAlarms"}
    };

    for (const auto& package : packages) {
        if (package.first) {
            if (ExecutePowerShellCommand("Get-AppxPackage '" + package.second + "' | Remove-AppxPackage")) {
                std::cout << "Package " << package.second << " deleted." << std::endl;
            }
            else {
                std::cerr << "Error deleting package " << package.second << std::endl;
            }
        }
    }

    return 0;
}



int PowershellTweaks::ActivateWindows() {
    if (ExecutePowerShellCommand("slmgr /ipk W269N-WFGWX-YVC9B-4J6C9-T83GX | slmgr /skms kms8.msguides.com | slmgr /ato")) {
        std::cout << "Windows activated successfully." << std::endl;
        return 0;
    }
    else {
		std::cout << "Error activating Windows." << std::endl;
    }
}