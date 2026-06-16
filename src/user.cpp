//第三方库：nlohmann/json v3.12.0 MIT协议
//官方仓库：https://github.com/nlohmann/json
//下载包仅单头文件，LICENSE文件已手动补充至同目录LICENSE

#define NOMINMAX

#include <print>
#include <iostream>
#include <cstdlib>
#include <limits>
#include <string>
#include <fstream>

#include "terminal.hpp"
#include "../thirdparty/nlohmann/json.hpp"

void sysOpera() {
    using json = nlohmann::json;
    json datas = json::array();
    const std::string userFilePath = "./data/user.json";
    start:
    std::ifstream in(userFilePath);
    in >> datas;
    std::println("操作选项：\n    0.退出\n    1.注册    \n    2.登录\n    3.修改个人信息");
    int n;
    std::print("请输入操作码：");
    if (std::cin >> n) {
        if (n == 0) {
            return;
        } else {
            switch (n)
            {
            case 1:
            {
                std::string name, password, confirmPassword;
                std::print("\n请输入用户名：");
                std::cin >> name;
                resetPassword:
                std::print("请输入密码：");
                std::cin >> password;
                std::print("请确认密码：");
                std::cin >> confirmPassword;
                if (password != confirmPassword) {
                    std::print("两次输入密码不一致");
                    Sleep(1000);
                    std::print("\033[2A\r\033[J");
                    goto resetPassword;
                } else {
                    std::println("注册完成");
                    datas.push_back({{"name", name}, {"password", password}});
                    std::println("\ndatas = {}", datas.dump(2));
                    std::ofstream out(userFilePath);
                    out << datas.dump(2);
                    for (float i = 3; i >= 0; i -= 0.1) {
                        std::print("\r  {:.1f}s后继续", i);
                        Sleep(100);
                    }
                    std::print("\033[H\033[J");
                    goto start;
                }
                break;
            }
            
            default:
                std::println("请输入有效的操作。");
                for (float i = 3; i >= 0; i -= 0.1) {
                    std::print("\r  {:.1f}s后重试", i);
                    Sleep(100);
                }
                std::print("\033[H\033[J");
                goto start;
            }
        }
    } else {
        std::println("请输入有效的操作。");
        for (float i = 3; i >= 0; i -= 0.1) {
            std::print("\r  {:.1f}s后重试", i);
            Sleep(100);
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::print("\033[H\033[J");
        goto start;
    }
}
   