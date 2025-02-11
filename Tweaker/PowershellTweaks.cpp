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
    si.cb = sizeof(si);

    if (!CreateProcessA(NULL, const_cast<char*>(fullCommand.c_str()), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
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

std::string CreateRemovePackageCommand(const std::vector<std::string>& packages) {
    std::string command;
    for (const auto& package : packages) {
        if (!command.empty()) {
            command += "; ";
        }
        command += "Get-AppxPackage '" + package + "' | Remove-AppxPackage";
    }
    return command;
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

    std::vector<std::string> packagesToRemove;
    for (const auto& package : packages) {
        if (package.first) {
            packagesToRemove.push_back(package.second);
        }
    }
    if (!packagesToRemove.empty()) {
        std::string command = CreateRemovePackageCommand(packagesToRemove);
        if (ExecutePowerShellCommand(command)) {
            for (const auto& package : packagesToRemove) {
                std::cout << "Package " << package << " deleted." << std::endl;
            }
        }
        else {
            std::cerr << "Error deleting packages." << std::endl;
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