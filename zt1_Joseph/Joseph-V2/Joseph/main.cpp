#include <iostream>
using namespace std;
#include <string>
#include <graphics.h>
#include <conio.h>
#include <windows.h> 

#include "AccountSystem.h"
#include "AccountOperation.h"
#include "JosephGame.h"
#include "button.h"
#include "ButtonOperation.h"


int main() {
    initgraph(800, 450); // ������ͼ����

	AccountSystem account_system;
    AccountOperation account_operation(&account_system);
    JosephGame Joseph_game(&account_system);

    IMAGE img;
    loadimage(&img, _T("background.jpg"));
    putimage(0, 0, &img);

    // ��ʼ����ť
    ButtonOperation button_op;
    int ButtonCount = 7;
    button_op.initButtons(ButtonCount,1);

    // ���ư�ť
    button_op.drawButtons();

    // ���������Ϣ
    MOUSEMSG msg;

    // ���������Ϣ
    int sys_flag = 1;
    int sys2_flag = 0;
    int acc2_flag = 0;
    while (sys_flag) {
        // ��������Ϣ
        if (MouseHit()) {
            msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN) {
                // ����ť����¼�
                putimage(0, 0, &img);
                button_op.drawButtons();
                int sys_button = button_op.handleButtonClick(msg.x, msg.y,button_op.buttons,1, account_system, account_operation, Joseph_game, sys2_flag);
                cout << "sys_button " << sys_button << "    sys2_flag " << sys2_flag << endl;
                if (sys_button && sys2_flag) {   // �����˻�
                    initgraph(800, 450); // ������ͼ����

                    IMAGE img2;
                    loadimage(&img2, _T("back2.jpg"));
                    putimage(0, 0, &img2);

                    // ��ʼ����ť
                    ButtonOperation button_op2;
                    int ButtonCount2 = 6;
                    button_op2.initButtons(ButtonCount2, 2);

                    // ���ư�ť
                    button_op2.drawButtons();
                    int acc_flag = 1;
                    while (acc_flag) {
                        msg = GetMouseMsg();
                        if (msg.uMsg == WM_LBUTTONDOWN) {
                            // ����ť����¼�
                            putimage(0, 0, &img2);
                            button_op2.drawButtons();
                            acc2_flag = 0;
                            int acc_button = button_op2.handleButtonClick(msg.x, msg.y, button_op2.buttons, 2, account_system, account_operation, Joseph_game, acc2_flag);
                            if (acc_button == 5||(acc_button == 2 && acc2_flag == 1)) {
                                acc_flag = 0;
                                putimage(0, 0, &img);
                                button_op.drawButtons();
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
	return 0;
}