
// Copyright (c) 2023. tiredy
//
// this program is free software: you can redistribute it and/or modify
// it under the terms of the gnu affero general public license as
// published by the free software foundation, either version 3 of the
// license, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but without any warranty; without even the implied warranty of
// merchantability or fitness for a particular purpose. See the
// gnu affero general public license for more details.
//
// You should have received a copy of the gnu affero general public license
// along with this program. If not, see <https: //www. Gnu. Org/licenses/>

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