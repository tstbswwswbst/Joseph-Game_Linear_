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
    void initButtons(int button_num,int layer) {

        int startX = WindowWidth - ButtonWidth - 80; // ��ʼ x ��������Ļ�Ҳ�
        int startY = (WindowHeight - button_num * (ButtonHeight + 20)) / 2; // ���㰴ť��ʼ y ����

        if (layer == 1) {
            // ����7����ť
            for (int i = 0; i < button_num; ++i) {
                Button btn;
                btn.x = startX;
                btn.y = startY + i * (ButtonHeight + 20); // ���㵱ǰ��ť�� y ����
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
                btn.normalColor = RGB(200, 200, 200);      // ������ɫ
                btn.highlightColor = RGB(0, 225, 225);      // ������ɫ
                btn.highlighted = false;                  // ��ʼ״̬Ϊ�Ǹ���
                buttons.push_back(btn);
            }
        }
        else if (layer == 2) {
            // ����6����ť
            for (int i = 0; i < button_num; ++i) {
                Button btn;
                btn.x = startX;
                btn.y = startY + i * (ButtonHeight + 20); // ���㵱ǰ��ť�� y ����
                switch (i) {
                case 0:btn.label = "Query Account"; break;
                case 1:btn.label = "Modify Account"; break;
                case 2:btn.label = "Cancel Account"; break;
                case 3:btn.label = "Start Game"; break;
                case 4:btn.label = "Chanllenge Game"; break;
                case 5:btn.label = "Exit Account"; break;
                default:break;
                }
                btn.normalColor = RGB(200, 200, 200);      // ������ɫ
                btn.highlightColor = RGB(0, 225, 225);      // ������ɫ
                btn.highlighted = false;                  // ��ʼ״̬Ϊ�Ǹ���
                buttons.push_back(btn);
            }
        }
    }

    // �������а�ť
    void drawButtons() {
        for (const auto& btn : buttons) {
            btn.draw();
        }
    }


    // ����ť����¼�
    int handleButtonClick(int mouseX, int mouseY, vector<Button>& buttons,int layer, AccountSystem& account_system, AccountOperation& account_operation, JosephGame& Joseph_game,int& flag) {
        int i = 0;
        flag = 0;
        for (i = 0; i < buttons.size(); ++i) {
            if (buttons[i].isClicked(mouseX, mouseY)) {
                // �л���ť״̬
                for (auto& btn : buttons) {
                    btn.highlighted = false;
                }
                buttons[i].highlighted = true;
                for (const auto& btn : buttons) {
                    btn.draw();
                }
                // ���ð�ť����¼�������
                flag = buttons[i].onClick(i,layer, account_system, account_operation, Joseph_game);

                return i; // ֻ����һ����ť�ĵ���¼�
            }
        }
    }
};
