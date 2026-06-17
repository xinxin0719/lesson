#pragma once

#include <string>

#include "../thirdparty/nlohmann/json.hpp"

void sysOpera();
bool pathExist(const std::string& path);
void userModel(nlohmann::json datas, const std::string userFilePath);