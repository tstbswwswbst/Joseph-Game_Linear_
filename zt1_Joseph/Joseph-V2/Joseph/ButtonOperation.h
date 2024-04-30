#pragma once
#include <graphics.h>
#include <iostream>
using namespace std;
#include <string>
#include <vector>
#include "button.h"


class ButtonOperation
{
public:

    // 按钮数组
    vector<Button> buttons;

    // 初始化按钮
    void initButtons(int button_num,int layer) {

        int startX = WindowWidth - ButtonWidth - 80; // 初始 x 坐标在屏幕右侧
        int startY = (WindowHeight - button_num * (ButtonHeight + 20)) / 2; // 计算按钮起始 y 坐标

        if (layer == 1) {
            // 创建7个按钮
            for (int i = 0; i < button_num; ++i) {
                Button btn;
                btn.x = startX;
                btn.y = startY + i * (ButtonHeight + 20); // 计算当前按钮的 y 坐标
                switch (i) {
                case 0:btn.label = "Sign up"; break;
                case 1:btn.label = "Sign in"; break;
                case 2:btn.label = "Browse Accounts"; break;
                case 3:btn.label = "Search Accounts"; break;
                case 4:btn.label = "Import Data"; break;
                case 5:btn.label = "Export Data"; break;
                case 6:btn.label = "Exit"; break;
                default:break;
                }
                btn.normalColor = RGB(200, 200, 200);      // 正常颜色
                btn.highlightColor = RGB(0, 225, 225);      // 高亮颜色
                btn.highlighted = false;                  // 初始状态为非高亮
                buttons.push_back(btn);
            }
        }
        else if (layer == 2) {
            // 创建6个按钮
            for (int i = 0; i < button_num; ++i) {
                Button btn;
                btn.x = startX;
                btn.y = startY + i * (ButtonHeight + 20); // 计算当前按钮的 y 坐标
                switch (i) {
                case 0:btn.label = "Query Account"; break;
                case 1:btn.label = "Modify Account"; break;
                case 2:btn.label = "Cancel Account"; break;
                case 3:btn.label = "Start Game"; break;
                case 4:btn.label = "Chanllenge Game"; break;
                case 5:btn.label = "Exit Account"; break;
                default:break;
                }
                btn.normalColor = RGB(200, 200, 200);      // 正常颜色
                btn.highlightColor = RGB(0, 225, 225);      // 高亮颜色
                btn.highlighted = false;                  // 初始状态为非高亮
                buttons.push_back(btn);
            }
        }
    }

    // 绘制所有按钮
    void drawButtons() {
        for (const auto& btn : buttons) {
            btn.draw();
        }
    }


    // 处理按钮点击事件
    int handleButtonClick(int mouseX, int mouseY, vector<Button>& buttons,int layer, AccountSystem& account_system, AccountOperation& account_operation, JosephGame& Joseph_game,int& flag) {
        int i = 0;
        flag = 0;
        for (i = 0; i < buttons.size(); ++i) {
            if (buttons[i].isClicked(mouseX, mouseY)) {
                // 切换按钮状态
                for (auto& btn : buttons) {
                    btn.highlighted = false;
                }
                buttons[i].highlighted = true;
                for (const auto& btn : buttons) {
                    btn.draw();
                }
                // 设置按钮点击事件处理函数
                flag = buttons[i].onClick(i,layer, account_system, account_operation, Joseph_game);

                return i; // 只处理一个按钮的点击事件
            }
        }
    }
};
