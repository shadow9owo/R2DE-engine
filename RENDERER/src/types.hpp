#pragma once

#include <cstdint> // for int64_t
#include <cstring>

enum class ValueType {
    INT, INT64, FLOAT, CHAR, PTR, STRING, NONE
};

union ValueData {
    int i;
    int64_t i64;
    float f;
    char c;
    void* ptr;
    const char* str;

    ValueData() { ptr = nullptr; }
};

struct Value {
    ValueType type;
    ValueData data;

    Value() : type(ValueType::NONE) {}

    Value(int v) { type = ValueType::INT; data.i = v; }
    Value(int64_t v) { type = ValueType::INT64; data.i64 = v; }
    Value(float v) { type = ValueType::FLOAT; data.f = v; }
    Value(char v) { type = ValueType::CHAR; data.c = v; }
    Value(void* v) { type = ValueType::PTR; data.ptr = v; }
    Value(const char* v) { type = ValueType::STRING; data.str = v; }
};
