#pragma once

#include <graphics.h>
#include <iostream>
using namespace std;
#include <string>
#include <vector>

#include "AccountSystem.h"
#include "AccountOperation.h"
#include "JosephGame.h"


// ���崰�ڴ�С
const int WindowWidth = 800;   // ���ڿ��
const int WindowHeight = 450;  // ���ڸ߶�
// ��ť��ض���
const int ButtonWidth = 120;   // ��ť���
const int ButtonHeight = 35;   // ��ť�߶�

class Button {
    public:
        int x, y;                // ��ť���Ͻ�����
        string label;            // ��ť����
        COLORREF normalColor;    // ����״̬��ɫ
        COLORREF highlightColor; // ����״̬��ɫ
        bool highlighted;        // �Ƿ����
        Button();
        // ����¼�������
        int onClick(int i, int layer, AccountSystem& account_system, AccountOperation& account_operation, JosephGame& Joseph_game);
        // ���ư�ť
        void draw() const;
        // ����Ƿ����ڰ�ť��Χ��
        bool isClicked(int mouseX, int mouseY) const;
};

