#include <fstream>
#include <string>
#include <iostream>
#include <print>
#include <Windows.h>

#include "main.hpp"
#include "../thirdparty/nlohmann/json.hpp"

void signUp(nlohmann::json datas, const std::string userFilePath) {
    std::ifstream in(userFilePath);
    in >> datas;
    std::string name, password, confirmPassword;
    resetName:
    std::print("\n请输入用户名（输入0取消）：");
    std::cin >> name;
    if (name == "0") {
        return;
    }
    for (const auto& user : datas) {
        if (user["name"] == name) {
            std::println("用户名已存在");
            Sleep(1000);
            std::print("\033[3A\033[J");
            goto resetName;
        }
    }
    resetPassword:
    std::print("请输入密码（输入0取消）：");
    std::cin >> password;
    if (password == "0") {
        return;
    }
    std::print("请确认密码（输入0取消）：");
    std::cin >> confirmPassword;
    if (confirmPassword == "0") {
        return;
    }
    if (password != confirmPassword) {
        std::print("两次输入密码不一致");
        Sleep(1000);
        std::print("\033[2A\r\033[J");
        goto resetPassword;
    } else {
        std::println("注册完成");
        datas.push_back({{"name", name}, {"password", password}});
        std::ofstream out(userFilePath);
        out << datas.dump(2);
        for (float i = 3; i >= 0; i -= 0.1) {
            std::print("\r  {:.1f}s后继续", i);
            Sleep(100);
        }
    }
}

void signIn(nlohmann::json datas, const std::string userFilePath) {
    std::string name, password;
    std::print("\n请输入用户名（输入0取消）：");
    std::cin >> name;
    if (name == "0") {
        return;
    }
    std::ifstream in(userFilePath);
    in >> datas;
    for (const auto& user : datas) {
        if (user["name"] == name) {
            while (true) {
                std::print("\n请输入密码（输入0取消）：");
                std::cin >> password;
                if (password == "0") {
                    return;
                }
                if (user["password"] == password) {
                    home(name);
                    return;
                } else {
                    std::println("  密码错误");
                    for (float i = 3; i >= 0; i -= 0.1) {
                        std::print("\r  {:.1f}s后重试", i);
                        Sleep(100);
                    }
                    std::print("\033[3A\r\033[J");
                }
            }
        }
    }
    std::print("用户不存在");
    Sleep(1000);
}


void resetPassword(nlohmann::json datas, const std::string userFilePath) {
    std::string name, password;
    std::print("\n请输入用户名（输入0取消）：");
    std::cin >> name;
    if (name == "0") {
        return;
    }
    std::ifstream in(userFilePath);
    in >> datas;
    for (auto& user : datas) {
        if (user["name"] == name) {
            while (true) {
                std::print("\n请输入密码（输入0取消）：");
                std::cin >> password;
                if (password == "0") {
                    return;
                }
                if (user["password"] == password) {
                    std::string newPassword;
                    std::print("输入新密码（输入0取消）：");
                    std::cin >> newPassword;
                    if (newPassword == "0") {
                        return;
                    }
                    user["password"] = newPassword;
                    std::ofstream out(userFilePath);
                    out << datas.dump(2);
                    return;
                } else {
                    std::println("  密码错误");
                    for (float i = 3; i >= 0; i -= 0.1) {
                        std::print("\r  {:.1f}s后重试", i);
                        Sleep(100);
                    }
                    std::print("\033[3A\r\033[J");
                }
            }
        }
    }
    std::print("用户不存在");
    Sleep(1000);
}