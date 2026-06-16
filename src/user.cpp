//第三方库：nlohmann/json v3.12.0 MIT协议
//官方仓库：https://github.com/nlohmann/json
//下载包仅单头文件，LICENSE文件已手动补充至同目录LICENSE

#define NOMINMAX

#include <print>
#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <limits>

#include "terminal.hpp"

void sysOpera() {
    start:
    std::println("操作选项:\n    0.退出\n    1.注册    \n    2.登录\n    3.修改个人信息");
    int n;
    if (std::cin >> n) {

    } else {
        std::println("请输入有效的操作");
        for (int i = 3; i >= 0; i--) {
            std::print("{}", i);
            Sleep(1000);
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        system("cls");
        goto start;
    }
}
   