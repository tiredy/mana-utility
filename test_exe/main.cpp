
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