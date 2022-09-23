#include "pch.h"
#include "settings.h"

static void SetResolution(HMODULE& hModule)
{
    // Module Directory
    char buffer[MAX_PATH + 1];
    GetModuleFileNameA(hModule, buffer, MAX_PATH + 1);
    auto path = std::string(buffer);
    path = path.substr(0, path.find_last_of("\\"));

    // Load Settings
    if (Settings::Load(path))
    {
        // Resolution Settings
        DEVMODE devMode = { 0 };
        devMode.dmSize = sizeof(DEVMODE);
        devMode.dmPelsWidth = Settings::width;
        devMode.dmPelsHeight = Settings::height;
        devMode.dmDisplayFrequency = Settings::refresh;
        devMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

        /*
         * Changing...
         * 'CDS_FULLSCREEN' flag auto restore to prior resolution on application exit.
         */
        ChangeDisplaySettings(&devMode, CDS_FULLSCREEN);
    }
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
        SetResolution(hModule);
        break;
    }

    return TRUE;
}
