#pragma once

//https://emscripten.org/docs/porting/multimedia_and_graphics/OpenGL-support.html

//if youre reading this dont remove this file its kinda important and its a leftover of an earlier version

enum SDL_EVENTS
{
    none = 0,
    quit,
    keydown,
    keyup,
    mousedown,
    mouseup,
    mousemove
};

enum SDL_PLATFORMS
{
    WIN_NT,
    UNIX_LINUX,
    MACOS,
    IOS,
    ANDROID,
    UNKNOWN
};

enum SpecialSaveFileSymbols : signed char {
    Newline = -1,
    Separator = -2,
    EndOfFile = -3 
};