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
    initgraph(800, 450); // 创建绘图窗口

	AccountSystem account_system;
    AccountOperation account_operation(&account_system);
    JosephGame Joseph_game(&account_system);

    IMAGE img;
    loadimage(&img, _T("background.jpg"));
    putimage(0, 0, &img);

    // 初始化按钮
    ButtonOperation button_op;
    int ButtonCount = 7;
    button_op.initButtons(ButtonCount,1);

    // 绘制按钮
    button_op.drawButtons();

    // 监听鼠标消息
    MOUSEMSG msg;

    // 监听鼠标消息
    int sys_flag = 1;
    int sys2_flag = 0;
    int acc2_flag = 0;
    while (sys_flag) {
        // 检测鼠标消息
        if (MouseHit()) {
            msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN) {
                // 处理按钮点击事件
                putimage(0, 0, &img);
                button_op.drawButtons();
                int sys_button = button_op.handleButtonClick(msg.x, msg.y,button_op.buttons,1, account_system, account_operation, Joseph_game, sys2_flag);
                cout << "sys_button " << sys_button << "    sys2_flag " << sys2_flag << endl;
                if (sys_button && sys2_flag) {   // 进入账户
                    initgraph(800, 450); // 创建绘图窗口

                    IMAGE img2;
                    loadimage(&img2, _T("back2.jpg"));
                    putimage(0, 0, &img2);

                    // 初始化按钮
                    ButtonOperation button_op2;
                    int ButtonCount2 = 6;
                    button_op2.initButtons(ButtonCount2, 2);

                    // 绘制按钮
                    button_op2.drawButtons();
                    int acc_flag = 1;
                    while (acc_flag) {
                        msg = GetMouseMsg();
                        if (msg.uMsg == WM_LBUTTONDOWN) {
                            // 处理按钮点击事件
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