//
// Created by tiredy on 9/29/23.
//

#include <iostream>
#include <chrono>
#include <thread>

#ifdef _WIN32
#include <windows.h>
#else

#include <dlfcn.h>

#endif

int main(int argc, char const *argv[]) {
    std::cout << "Hello, world!";

#ifdef _WIN32
    HINSTANCE hDllProcID = LoadLibrary("./mana-util-win32.dll");
    if (!hDllProcID)
    {
        LPVOID errorMsg;
        FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, 0, GetLastError(), 0, (LPSTR)&errorMsg, 0, 0); wprintf(L"Failed to load/find the dll! Error %d: %s\n", GetLastError(), errorMsg);
        LocalFree(errorMsg);
    }
#else
    void *libHandle = dlopen("./mana-util-unix.so", RTLD_LAZY);
    if (!libHandle) {
        std::cout << "Failed to load/find the so: " << dlerror() << "\n";
    }
#endif

    while (true) {
        std::cout << "Bump!\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}