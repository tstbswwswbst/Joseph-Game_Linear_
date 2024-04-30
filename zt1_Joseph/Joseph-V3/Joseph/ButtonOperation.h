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
    // ��ť����
    vector<Button> buttons;
    // ��ʼ����ť
    void initButtons(int button_num, int layer);
    // �������а�ť
    void drawButtons();
    // ����ť����¼�
    int handleButtonClick(int mouseX, int mouseY, vector<Button>& buttons, int layer, AccountSystem& account_system, AccountOperation& account_operation, JosephGame& Joseph_game, int& flag);
};
