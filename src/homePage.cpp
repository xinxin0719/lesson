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
    using json = nlohmann::json;
    const std::string goodsFilePath = "./data/goods.json";
    static int currentPage = 0;   // 当前页码，0‑based

    while (true) {
    start:
        std::print("\033[H\033[J");   // 清屏
        std::println("-1.退出");
        std::println("1.发布商品");
        std::println("2.编辑已发布的物品");
        std::println("3.前一页");
        std::println("4.后一页");

        // 读取商品数据
        json datas = json::array();
        {
            std::ifstream in(goodsFilePath);
            if (in.is_open()) {
                in >> datas;
            }
        }

        // 计算总页数
        const int itemsPerPage = 5;
        int totalItems = datas.size();
        int totalPages = (totalItems + itemsPerPage - 1) / itemsPerPage;
        if (totalPages == 0) totalPages = 1;  // 至少有一页（空页）
        // 修正 currentPage，防止越界
        if (currentPage < 0) currentPage = 0;
        if (currentPage >= totalPages) currentPage = totalPages - 1;

        // 显示当前页物品（输入提示的上方）
        std::println("\n========== 商品列表 (第 {}/{} 页) ==========", currentPage + 1, totalPages);
        if (totalItems == 0) {
            std::println("  （暂无商品）");
        } else {
            int startIdx = currentPage * itemsPerPage;
            int endIdx = std::min(startIdx + itemsPerPage, totalItems);
            for (int i = startIdx; i < endIdx; ++i) {
                auto& goods = datas[i];
                std::println("  {} | {} | ¥{} | {} | {}",
                    goods.value("name", "??"),
                    goods.value("type", "??"),
                    goods.value("price", "??"),
                    goods.value("quality", "??"),
                    goods.value("sellWay", "??"));
            }
        }
        std::println("");  // 额外空行

        // 输入操作码
        int opera;
        std::print("输入操作码：");
        if (!(std::cin >> opera)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::println("输入无效，请重试。");
            Sleep(1500);
            continue;
        }

        switch (opera) {
        case -1:
            return;

        case 1: {
            // 发布商品
            json newGoods = json::object();
            std::string message;

            std::print("输入物品名称（输入0取消）：");
            std::cin >> message;
            if (message == "0") break;
            // 检查重名
            for (auto& goods : datas) {
                if (goods["name"] == message) {
                    std::println("  商品不能重名");
                    for (float i = 3; i >= 0; i -= 0.1f) {
                        std::print("\r  {:.1f}s后重试", i);
                        Sleep(100);
                    }
                    goto start;
                }
            }
            newGoods["name"] = message;

            std::print("输入物品分类（输入0取消）：");
            std::cin >> message;
            if (message == "0") break;
            newGoods["type"] = message;

            std::print("输入物品描述（输入0取消）：");
            std::cin >> message;
            if (message == "0") break;
            newGoods["script"] = message;

            std::print("输入物品价格（输入0取消）：");
            std::cin >> message;
            if (message == "0") break;
            newGoods["price"] = message;

            std::print("输入物品成色（输入0取消）：");
            std::cin >> message;
            if (message == "0") break;
            newGoods["quality"] = message;

            std::print("输入物品交易方式（输入0取消）：");
            std::cin >> message;
            if (message == "0") break;
            newGoods["sellWay"] = message;

            newGoods["owner"] = name;
            datas.push_back(newGoods);

            std::ofstream out(goodsFilePath);
            if (out.is_open()) {
                out << datas.dump(2);
                std::println("\n商品录入完成");
                // 发布后跳到最后一页，方便看到新商品
                currentPage = (datas.size() - 1) / itemsPerPage;
            } else {
                std::println("保存失败，请检查文件权限。");
            }
            Sleep(1000);
            goto start;
        }

        case 2: {
            // 编辑商品
            std::string goodsName;
            std::print("请输入要修改的商品名称：");
            std::cin >> goodsName;

            bool found = false;
            for (auto& goods : datas) {
                if (goods["name"] == goodsName && goods["owner"] == name) {
                    found = true;
                    std::println("当前信息：");
                    std::println("  名称: {}", goods["name"].get<std::string>());
                    std::println("  分类: {}", goods["type"].get<std::string>());
                    std::println("  描述: {}", goods["script"].get<std::string>());
                    std::println("  价格: {}", goods["price"].get<std::string>());
                    std::println("  成色: {}", goods["quality"].get<std::string>());
                    std::println("  交易方式: {}", goods["sellWay"].get<std::string>());

                    std::string input;
                    std::print("新名称（输入0保持不变）：");
                    std::cin >> input;
                    if (input != "0") goods["name"] = input;

                    std::print("新分类（输入0保持不变）：");
                    std::cin >> input;
                    if (input != "0") goods["type"] = input;

                    std::print("新描述（输入0保持不变）：");
                    std::cin >> input;
                    if (input != "0") goods["script"] = input;

                    std::print("新价格（输入0保持不变）：");
                    std::cin >> input;
                    if (input != "0") goods["price"] = input;

                    std::print("新成色（输入0保持不变）：");
                    std::cin >> input;
                    if (input != "0") goods["quality"] = input;

                    std::print("新交易方式（输入0保持不变）：");
                    std::cin >> input;
                    if (input != "0") goods["sellWay"] = input;

                    std::ofstream out(goodsFilePath);
                    if (out.is_open()) {
                        out << datas.dump(2);
                        std::println("商品信息修改成功！");
                    } else {
                        std::println("保存失败，请检查文件权限。");
                    }
                    break;
                }
            }
            if (!found) {
                std::println("未找到该商品或您无权修改。");
            }
            Sleep(1000);
            goto start;
        }

        case 3: {
            // 前一页
            if (currentPage <= 0) {
                std::println("已经是第一页了");
                Sleep(1500);
            } else {
                --currentPage;
            }
            goto start;
        }

        case 4: {
            // 后一页
            if (currentPage >= totalPages - 1) {
                std::println("已经是最后一页了");
                Sleep(1500);
            } else {
                ++currentPage;
            }
            goto start;
        }

        default:
            std::println("请输入有效的操作码。");
            for (float i = 3; i >= 0; i -= 0.1f) {
                std::print("\r  {:.1f}s后重试", i);
                Sleep(100);
            }
            break;
        }
    }
}