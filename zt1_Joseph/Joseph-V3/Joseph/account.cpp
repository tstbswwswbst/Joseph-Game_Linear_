#include "account.h"
#include <iostream>
using namespace std;

#include <string>
#include <graphics.h>
#include <conio.h>
#include <cstring>
#include <iostream>
#include <sstream>

account::account() {
    player_num = 0;
    ID = "wrong";
    name = "wrong";
    tell = "wrong";
    email = "wrong";
	score = 0; //初始化积分为0
    password = rand() % 20 - 10; // 密码随机产生 0-20随机数 第1位代表正负
    if (password == 0) { //消除0
        int flag = rand() % 1;
        if (flag) {
            password = 10;
        }
        else {
            password = -10;
        }
    }
}

account::account(int PLAYER_NUM, string _ID, string NAME, string TELL, string EMAIL, int PASSWORD, int SCORE) {
    player_num = PLAYER_NUM;
    ID = _ID;
    name = NAME;
    tell = TELL;
    email = EMAIL;
    password = PASSWORD;
    score = SCORE;
}

void account::displayAccount()const {  // 弹窗打印玩家信息
    char char_num = '0' + player_num;
    string str = "Player number in the game system:";
    str = str + char_num;
    str = str + "\nID: " + ID + "\t\tName: " + name;
    str = str + "\nPhone number: " + tell + "\tEmail: " + email;
    ostringstream oss;
    oss << password;           // 将整数写入字符串流
    string result = oss.str(); // 返回字符串流中的字符串
    str = str + "\nPassword: " + result;
    char_num = '0' + score;
    str = str + "\tScore: " + char_num;
    MessageBox(GetHWnd(), str.c_str(), _T("Account Created Successfully"), MB_OK);
}
