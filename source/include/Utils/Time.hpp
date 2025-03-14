#pragma once

#ifdef _WIN32
#include "SafeWindows.hpp"
#else
#include <fcntl.h>
#include <sys/time.h>
#include <time.h>
#endif

#include <chrono>
#include <format>
#include <string>

#include "Conf/Conf.h"

// Possible related issue https://github.com/llvm/llvm-project/issues/99982

MAA_NS_BEGIN

inline std::string format_now()
{
    constexpr std::string_view kFormat = "{:0>4}-{:0>2}-{:0>2} {:0>2}:{:0>2}:{:0>2}.{:0>3}";

#ifdef _WIN32
    SYSTEMTIME sys {};
    GetLocalTime(&sys);
    return std::format(kFormat, sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond, sys.wMilliseconds);
#else
    timeval tv = {};
    gettimeofday(&tv, nullptr);
    time_t nowtime = tv.tv_sec;
    tm* tm_info = localtime(&nowtime);
    return std::format(
        kFormat,
        tm_info->tm_year + 1900,
        tm_info->tm_mon,
        tm_info->tm_mday,
        tm_info->tm_hour,
        tm_info->tm_min,
        tm_info->tm_sec,
        tv.tv_usec / 1000);
#endif
}

inline std::string format_now_for_filename()
{
    constexpr std::string_view kFormat = "{:0>4}.{:0>2}.{:0>2}-{:0>2}.{:0>2}.{:0>2}.{}";

#ifdef _WIN32
    SYSTEMTIME sys {};
    GetLocalTime(&sys);
    return std::format(kFormat, sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond, sys.wMilliseconds);
#else
    timeval tv = {};
    gettimeofday(&tv, nullptr);
    time_t nowtime = tv.tv_sec;
    tm* tm_info = localtime(&nowtime);
    return std::format(
        kFormat,
        tm_info->tm_year + 1900,
        tm_info->tm_mon,
        tm_info->tm_mday,
        tm_info->tm_hour,
        tm_info->tm_min,
        tm_info->tm_sec,
        tv.tv_usec / 1000);
#endif
}

template <typename duration_t = std::chrono::milliseconds>
inline duration_t duration_since(const std::chrono::steady_clock::time_point& start_time)
{
    return std::chrono::duration_cast<duration_t>(std::chrono::steady_clock::now() - start_time);
}

MAA_NS_END
