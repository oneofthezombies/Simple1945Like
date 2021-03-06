// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: reference additional headers your program requires here
#include <memory>
#include <vector>
#include <map>
#include <functional>
#include <chrono>
#include <bitset>
using namespace std;

#define WINDOW_WIDTH 428
#define WINDOW_HEIGHT 600
#define M_PI 3.141592

extern HINSTANCE hInst;
extern HWND hWnd;
extern bool IsFinished;