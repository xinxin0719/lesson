#pragma once

#include <string>

#include "../thirdparty/nlohmann/json.hpp"

void sysOpera();
bool pathExist(const std::string& path);
void signUp(nlohmann::json datas, const std::string userFilePath);
void signIn(nlohmann::json datas, const std::string userFilePath);
void resetPassword(nlohmann::json datas, const std::string userFilePath);
void home(std::string name);