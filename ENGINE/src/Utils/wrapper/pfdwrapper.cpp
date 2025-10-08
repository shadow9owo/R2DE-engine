#define PFD_IMPLEMENTATION

#ifdef _WIN32
#include <Windows.h>
#endif

#include "../../native/portable-file-dialogs.h"
#include "../../data.hpp"

namespace wrapper {
    void LogErr(const std::string& msg) { pfd::message("Error", msg, pfd::choice::ok, pfd::icon::error); }
    void SaveProjectFile() {
        auto r = pfd::save_file("Save your project file", "output.R2DE", { "R2DE project files (.R2DE)","*.R2DE" });
        data::filepath = r.result();
    }
    void OpenProjectFile() {
        auto r = pfd::open_file("Select a project file", ".", { "R2DE project files (.R2DE)","*.R2DE" }, pfd::opt::none);
        data::contentsofproject = r.result();
    }
}
