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
	AccountSystem account_system;
    AccountOperation account_operation(&account_system);
    JosephGame Joseph_game(&account_system);

    initgraph(800, 450); // ������ͼ����
    IMAGE img;           // ����ϵͳ����
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

    int sys_flag = 1;   // ϵͳ�Ƿ��˳�
    int sys2_flag = 0;  // �Ƿ���ϵͳ�����˺�
    int acc_flag = 1;   // �˺��Ƿ��˳�/ע��
    int acc2_flag = 0;  // �Ƿ����˺Żص�ϵͳ

    while (sys_flag) {
        // ��������Ϣ
        if (MouseHit()) {
            msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN) {
                putimage(0, 0, &img);
                button_op.drawButtons();
                // ����ť����¼�
                int sys_button = button_op.handleButtonClick(msg.x, msg.y,button_op.buttons,1, account_system, account_operation, Joseph_game, sys2_flag);
                // ��ѡ���¼��������ȷ��ID������
                if (sys_button == 1 && sys2_flag == 1) {   // �����˻�
                    initgraph(800, 450);         // ������ͼ����

                    IMAGE img2;
                    loadimage(&img2, _T("back2.jpg"));
                    putimage(0, 0, &img2);

                    // ��ʼ����ť
                    ButtonOperation button_op2;
                    int ButtonCount2 = 6;
                    button_op2.initButtons(ButtonCount2, 2);

                    // ���ư�ť
                    button_op2.drawButtons();
                    acc_flag = 1;

                    while (acc_flag) {
                        msg = GetMouseMsg();
                        if (msg.uMsg == WM_LBUTTONDOWN) {
                            putimage(0, 0, &img2);
                            button_op2.drawButtons();
                            acc2_flag = 0;
                            // ����ť����¼�
                            int acc_button = button_op2.handleButtonClick(msg.x, msg.y, button_op2.buttons, 2, account_system, account_operation, Joseph_game, acc2_flag);
                            // ��ѡ���˳��˺� �� ȷ��ע���˺�
                            if (acc_button == 5||(acc_button == 2 && acc2_flag == 1)) {
                                acc_flag = 0;
                                putimage(0, 0, &img);
                                button_op.drawButtons();
                                break;
                            }
                            if (acc_button == 3 || acc_button == 4) {
                                initgraph(800, 450);
                                cleardevice();
                                setorigin(0, 0);
                                putimage(0, 0, &img2);
                                button_op2.drawButtons();
                            }
                        }
                    }
                }
                else if (sys_button == 6) { // �˳�ϵͳ
                    sys_flag = 0; 
                    break;
                }
            }
        }
    }
	return 0;
}