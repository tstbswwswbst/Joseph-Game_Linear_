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
	score = 0; //��ʼ������Ϊ0
    password = rand() % 200 - 100; // ����������� 0-200����� ��1λ��������
    if (password == 0) { //����0
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
