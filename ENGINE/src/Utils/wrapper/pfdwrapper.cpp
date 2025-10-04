#define PFD_IMPLEMENTATION //garbage windows api macros to make it work with raylib
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include "../../native/portable-file-dialogs.h"
#include <iostream>
#include "../../data.hpp"
#include "pfdwrapper.hpp"

namespace wrapper {
    void LogErr(const std::string& msg) {
        pfd::message("Error", msg, pfd::choice::ok, pfd::icon::error);
        return;
    }

    void SaveProjectFile() {
        auto result = pfd::save_file(
            "Save your project file",
            "output.R2DE",
            { "R2DE project files (.R2DE)", "*.R2DE" }
        );

        if (!result.result().empty()) {
            data::filepath = result.result();
        }
        else {
            data::filepath = nullptr;
        }
        return;
    }

    void OpenProjectFile() {
        data::project = {};
        data::contentsofproject = {};

        pfd::open_file result = pfd::open_file(
            "Select a project file",
            ".",
            { "R2DE project files (.R2DE)", "*.R2DE" },
            pfd::opt::none
        );

        if (!result.result().empty()) {
            data::contentsofproject = result.result();
        }
        else {
            data::contentsofproject = {};
        }

        return;
    }
}
