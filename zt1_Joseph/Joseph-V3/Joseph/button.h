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

class Button {
    public:
        int x, y;                // 按钮左上角坐标
        string label;            // 按钮文字
        COLORREF normalColor;    // 正常状态颜色
        COLORREF highlightColor; // 高亮状态颜色
        bool highlighted;        // 是否高亮
        Button();
        // 点击事件处理函数
        int onClick(int i, int layer, AccountSystem& account_system, AccountOperation& account_operation, JosephGame& Joseph_game);
        // 绘制按钮
        void draw() const;
        // 检查是否点击在按钮范围内
        bool isClicked(int mouseX, int mouseY) const;
};

