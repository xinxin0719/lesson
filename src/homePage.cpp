#define NOMINMAX

#include <print>
#include <iostream>
#include <Windows.h>
#include <limits>
#include <string>
#include <fstream>

#include "main.hpp"
#include "../thirdparty/nlohmann/json.hpp"

void home(std::string name) {
    while (true) {
        start:
        std::print("\033[H\033[J");
        int opera;
        using json = nlohmann::json;
        json datas = json::array();
        const std::string goodsFilePath = "./data/goods.json";
        std::println("-1.退出\n1.发布商品\n2.编辑已发布的物品");
        std::print("\n输入操作码：");
        if (std::cin >> opera) {
            switch (opera)
            {
            case -1:
                return;
            case 1:
            {
                std::ifstream in(goodsFilePath);
                json data = json::object();
                in >> datas;
                std::string message;
                std::print("输入物品名称（输入0取消）：");
                std::cin >> message;
                if (message == "0") {break;}
                for (auto goods : datas) {
                    if (goods["name"] == message) {
                        std::println("  商品不能重名");
                        for (float i = 3; i >= 0; i -= 0.1) {
                            std::print("\r  {:.1f}s后重试", i);
                            Sleep(100);
                        }
                        goto start;
                    }
                }
                data["name"] = message;
                std::print("输入物品分类（输入0取消）：");
                std::cin >> message;
                if (message == "0") {break;}
                data["type"] = message;
                std::print("输入物品描述（输入0取消）：");
                std::cin >> message;
                if (message == "0") {break;}
                data["script"] = message;
                std::print("输入物品价格（输入0取消）：");
                std::cin >> message;
                if (message == "0") {break;}
                data["price"] = message;
                std::print("输入物品成色（输入0取消）：");
                std::cin >> message;
                if (message == "0") {break;}
                data["quality"] = message;
                std::print("输入物品交易方式（输入0取消）：");
                std::cin >> message;
                if (message == "0") {break;}
                data["sellWay"] = message;
                data["owner"] = name;
                std::ofstream out(goodsFilePath);
                datas.push_back(data);
                out << datas.dump(2);
                std::print("\n商品录入完成");
                Sleep(1000);
                break;
            }
            
            default:
                break;
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