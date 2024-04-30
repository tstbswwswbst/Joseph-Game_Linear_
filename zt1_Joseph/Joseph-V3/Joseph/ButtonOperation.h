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
    void initButtons(int button_num, int layer);
    // 绘制所有按钮
    void drawButtons();
    // 处理按钮点击事件
    int handleButtonClick(int mouseX, int mouseY, vector<Button>& buttons, int layer, AccountSystem& account_system, AccountOperation& account_operation, JosephGame& Joseph_game, int& flag);
};
