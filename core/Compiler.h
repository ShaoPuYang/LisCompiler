/*
 * @Copyrigt 2023, liserver. All rights reserved.
 */

// Compiler core.

#pragma once

// #define int long long

#include <iostream>
#include <string>
#include <vector>

#include "library/application/config.h"

#ifndef __cplusplus
    #error Code Only Support C++
#endif // __cplusplus

#ifdef __DEBUG // define in Makefile , if Debug is True, then, will -D__DEBUG.
    #define DEBUG 1
#else
    
#endif // __DEBUG

// About errors :: Message::Error
#define CP_ERR 0 // Compiler error
#define LK_ERR 1 // Linker   error

// About CP_ERR (Compiler)
#define CP_NO_ARGS 1
#define CP_FINE_NO_TEXT 2
#define CP_FILE_NOT_FOUND 3
#define CP_ARG_MUST_NOT_END 4
#define CP_VERSION_ERROR 5

#define CP_UNKNOW_TOKEN 6
#define CP_NOTFIND_TOKEN 7

// This project is support windows macos and linux. So, first we need to know the system.
enum __Platform
{
    Windows = 0,
    MacOS,
    Linux
};

// About platform init
// Windows have two version, 32bit and 64bit. But, we needn't to know the version.
#ifndef  DISABLE_PLATFORM_H
    #if _WIN32 || _WIN64
        #define _OS Platform::Windows
        #define __WIN
        #include <Windows.h>
    #elif __APPLE__
        #define _OS Platform::MacOS
        #define __MAC
        #include <TargetConditionals.h>
    #elif __linux
        #define _OS Platform::Linux
        #define __LINUX
        #include <unistd.h>
    #else
        #error "Unknown system."
    #endif
#endif // ! DISABLE_PLATFORM_H

// Type defines
typedef __Platform Platform;
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;

// The identifier
#ifndef __COMPILER_H_ID__
#define __COMPILER_H_ID__
    extern __Configtion Configtion;
#endif // __COMPILER_H_ID__