#pragma once

#include <graphics.h>
#include <iostream>
using namespace std;
#include <string>
#include <vector>

#include "AccountSystem.h"
#include "AccountOperation.h"
#include "JosephGame.h"


// 定义窗口大小
const int WindowWidth = 800;   // 窗口宽度
const int WindowHeight = 450;  // 窗口高度

// 按钮相关定义
const int ButtonWidth = 120;   // 按钮宽度
const int ButtonHeight = 35;   // 按钮高度

// 按钮结构体
class Button {
    public:
        int x, y;                // 按钮左上角坐标
        string label;            // 按钮文字
        COLORREF normalColor;    // 正常状态颜色
        COLORREF highlightColor; // 高亮状态颜色
        bool highlighted;        // 是否高亮
        Button() {
            x = 0;
            y = 0;
            label = "wrong";
            normalColor = RGB(200, 200, 200);      // 正常颜色
            highlightColor = RGB(0, 225, 225);      // 高亮颜色
            highlighted = false;                  // 初始状态为非高亮
        }
        // 点击事件处理函数
        int onClick(int i, int layer, AccountSystem &account_system,AccountOperation& account_operation, JosephGame& Joseph_game) {
            highlighted = true;
            int re = 0;
            if (layer == 1) {
                switch (i) {
                case 0:account_system.createAccount(); break;
                case 1:if (account_operation.SigninAccount() != 0) {
                    MessageBox(GetHWnd(), "Signed in Successfully", _T("YOUR ACCOUNT"), MB_OK);
                    re = 1;
                     } break;
                case 2:account_operation.BrowseSystem(); break;
                case 3:account_operation.SearchSystem(); break;
                case 4:account_operation.ImportData(); break;
                case 5:account_operation.ExportData(); break;
                case 6:closegraph(); break;
                default:cout << "Invalid choice. Please try again." << endl; break;
                }
            }
            else if (layer == 2) {
                switch (i) {
                case 0: account_operation.QueryAccount();break;
                case 1:account_operation.ModifyAccount();break;
                case 2:if (account_operation.CancelAccount()) {
                            re = 1;
                       }
                       break;
                case 3:Joseph_game.GameAndScores(0, account_operation.current_player);break;
                case 4:Joseph_game.GameAndScores(1, account_operation.current_player);break;
                case 5: break;
                default:cout << "Invalid choice. Please try again." << endl; break;
                }
            }
            return re;
        }

        // 绘制按钮
        void draw() const {
            setfillcolor(highlighted ? highlightColor : normalColor);
            setbkmode(TRANSPARENT); // 设置背景透明
            settextstyle(15, 0, _T("Arial")); // 明确指定字体为 Arial
            fillrectangle(x, y, x + ButtonWidth, y + ButtonHeight);
            settextcolor(BLACK);

            LOGFONT font;
            gettextstyle(&font); // 获取当前字体设置
            font.lfWeight = FW_BOLD; // 设置字体加粗
            settextstyle(&font); // 应用新的字体设置

            outtextxy(x + 10, y + 10, label.c_str());
        }

        // 检查是否点击在按钮范围内
        bool isClicked(int mouseX, int mouseY) const {
            return (mouseX >= x && mouseX <= x + ButtonWidth && mouseY >= y && mouseY <= y + ButtonHeight);
        }
};

