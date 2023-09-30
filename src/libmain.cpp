#include <iostream>
#include <thread>

#ifdef _WIN32
#include <windows.h>
// includes for windows
#else
// includes for linux
#endif

#include <gui/ManaGui.h>

void Main() {
    std::cout << "Hello, Library-World!\n";

    ManaGui gui = ManaGui();
    gui.init();

    bool shouldRun = true;
    while (shouldRun) {
        shouldRun = gui.run();
        gui.dragHandler();
    }
    gui.end();
}

#ifdef _WIN32
DWORD WINAPI WindowsMain(HMODULE hModule)
{
    MessageBox(0, "Hello", 0, MB_OK);
    Main();
    FreeLibrary(hModule);
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{
    static FILE *pFile = nullptr;
    static std::thread mainThread;
    if (reason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hModule);

        AllocConsole();
        freopen_s(&pFile, "CONOUT$", "w", stdout);
        freopen_s(&pFile, "CONOUT$", "w", stderr);

        mainThread = std::thread(WindowsMain, hModule);
        if(mainThread.joinable())
            mainThread.detach();

    }
    else if(reason == DLL_PROCESS_DETACH)
    {
        fclose(pFile);
        FreeConsole();
    }
    return TRUE;
}
#else

void LinuxMain() {
    static std::thread mainThread;
    mainThread = std::thread(Main);
    if (mainThread.joinable())
        mainThread.detach();
}

void __attribute__((constructor)) LinuxMain(void);

#endif