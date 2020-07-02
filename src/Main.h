#ifndef MAIN_H
#define MAIN_H

// os 0 for windows, 1 for mac, 2 for linux
#if defined(__WIN32) || defined(_WIN64)
#include <tchar.h>
#include <windows.h>
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup") // disable console
const int OS = 0;
#elif defined(__APPLE__) || defined(__MACH__)
const int OS = 1;
#elif defined(__linux__)
const int OS = 2;
#endif

#include "Engine.h"

#endif
