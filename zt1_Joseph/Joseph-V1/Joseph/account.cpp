#include "account.h"
#include <iostream>
using namespace std;
#include <string>

account::account() {
    player_num = 0;
    ID = " ";
    name = " ";
    tell = " ";
    email = " ";
	score = 0; //初始化积分为0
    password = rand() % 200 - 100; // 密码随机产生 0-200随机数 第1位代表正负
    if (password == 0) { //消除0
        int flag = rand() % 1;
        if (flag) {
            password = 100;
        }
        else {
            password = -100;
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

void account::displayAccount()const {
    cout << "Player number in the game system:" << player_num << endl;
    cout << "ID:" << ID << "\t\tName: " << name << "\tPhone number: " << tell << endl;
    cout << "Email: " << email << "\tPassword: " << password << "\tScore: " << score << endl;
}
