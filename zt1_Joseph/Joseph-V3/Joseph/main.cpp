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

    initgraph(800, 450); // 创建绘图窗口
    IMAGE img;           // 绘制系统背景
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

    int sys_flag = 1;   // 系统是否退出
    int sys2_flag = 0;  // 是否由系统进入账号
    int acc_flag = 1;   // 账号是否退出/注销
    int acc2_flag = 0;  // 是否由账号回到系统

    while (sys_flag) {
        // 检测鼠标消息
        if (MouseHit()) {
            msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN) {
                putimage(0, 0, &img);
                button_op.drawButtons();
                // 处理按钮点击事件
                int sys_button = button_op.handleButtonClick(msg.x, msg.y,button_op.buttons,1, account_system, account_operation, Joseph_game, sys2_flag);
                // 若选择登录并输入正确的ID和密码
                if (sys_button == 1 && sys2_flag == 1) {   // 进入账户
                    initgraph(800, 450);         // 创建绘图窗口

                    IMAGE img2;
                    loadimage(&img2, _T("back2.jpg"));
                    putimage(0, 0, &img2);

                    // 初始化按钮
                    ButtonOperation button_op2;
                    int ButtonCount2 = 6;
                    button_op2.initButtons(ButtonCount2, 2);

                    // 绘制按钮
                    button_op2.drawButtons();
                    acc_flag = 1;

                    while (acc_flag) {
                        msg = GetMouseMsg();
                        if (msg.uMsg == WM_LBUTTONDOWN) {
                            putimage(0, 0, &img2);
                            button_op2.drawButtons();
                            acc2_flag = 0;
                            // 处理按钮点击事件
                            int acc_button = button_op2.handleButtonClick(msg.x, msg.y, button_op2.buttons, 2, account_system, account_operation, Joseph_game, acc2_flag);
                            // 若选择退出账号 或 确认注销账号
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
                else if (sys_button == 6) { // 退出系统
                    sys_flag = 0; 
                    break;
                }
            }
        }
    }
	return 0;
}