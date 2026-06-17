#include <Windows.h>

#include "main.hpp"

bool pathExist(const std::string& path) {
    return GetFileAttributesA(path.c_str()) != INVALID_FILE_ATTRIBUTES;
}