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
#include <Windows.h>

#include "main.hpp"
#include "../thirdparty/nlohmann/json.hpp"

void sysOpera() {
    int opera;
    using json = nlohmann::json;
    json datas = json::array();
    const std::string userFilePath = "./data/user.json";
    while (true) {
        std::print("\033[H\033[J");
        std::println("操作选项：\n    0.退出\n    1.注册\n    2.登录\n    3.修改个人信息");
        std::print("请输入操作码：");
        if (std::cin >> opera) {
            if (opera == 0) {
                return;
            } else {
                switch (opera)
                {
                case 1:
                {
                    userModel(datas, userFilePath);
                    break;
                }
                case 2:
                {
                    break;
                }
                case 3:
                {
                    break;
                }
                
                default:
                    std::println("请输入有效的操作。");
                    for (float i = 3; i >= 0; i -= 0.1) {
                        std::print("\r  {:.1f}s后重试", i);
                        Sleep(100);
                    }
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
        }
    }
}
   