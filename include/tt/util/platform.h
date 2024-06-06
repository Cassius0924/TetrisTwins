#ifndef UTIL_PLATFORM_H
#define UTIL_PLATFORM_H

#if WIN32 || _WIN32 || WIN64 || _WIN64 || _WIN64_
#define __PLATFORM_WIN 1

#elif __linux__
#define __PLATFORM_LINUX 1

#elif __APPLE__ || TARGET_OS_MAC
#define __PLATFORM_MAC 1

#else
#define __PLATFORM_UNKNOWN 1

#endif

#endif // UTIL_PLATFORM_H