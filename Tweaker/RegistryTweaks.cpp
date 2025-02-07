#include "RegistryTweaks.h"
#include <windows.h>
#include <iostream>
#include "TweakerMenu.h"

int RegistryTweaks::DisableWindowsDefender(config cfg) {
    std::cout << "Defender func triggered" << std::endl;
    if (!cfg.antivirus)
    {
        return 0;
    }

    HKEY hKey;
    LPCSTR subKey = "SOFTWARE\\Policies\\Microsoft\\Windows Defender";
    LONG result;
    result = RegCreateKeyExA(HKEY_LOCAL_MACHINE, subKey,0,NULL,0,KEY_ALL_ACCESS,NULL,&hKey,NULL);

    if (result == ERROR_SUCCESS) {
        std::cout << "Ключ успешно создан!" << std::endl;
        const char* valueName = "DisableAntiSpyware";
        DWORD valueData = 1;
        result = RegSetValueExA(hKey, "DisableAntiSpyware", 0, REG_DWORD, (const BYTE*)1, 1);

        if (result == ERROR_SUCCESS) {
            std::cout << "Set DisableAntiSpyware" << std::endl;
        }
        else {
            std::cerr << "Error writing value: " << result << std::endl;
        }
        RegCloseKey(hKey);
    }
    else {
        std::cerr << "Error creating key: " << result << std::endl;
    }

    return 0;
}