#pragma once
#include <string>

namespace wrapper {
    extern void LogErr(const std::string& msg);

    extern void SaveProjectFile();
    extern void OpenProjectFile();
}
