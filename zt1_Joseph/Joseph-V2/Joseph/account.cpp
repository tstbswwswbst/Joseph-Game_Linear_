
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
    char char_num = '0' + player_num;
    string str = "Player number in the game system:";
    str = str + char_num;
    str = str + "\nID: " + ID + "\t\tName: " + name;
    str = str + "\nPhone number: " + tell + "\tEmail: " + email;
    ostringstream oss;
    oss << password;           // ������д���ַ�����
    string result = oss.str(); // �����ַ������е��ַ���
    str = str + "\nPassword: " + result;
    char_num = '0' + score;
    str = str + "\tScore: " + char_num;
    MessageBox(GetHWnd(), str.c_str(), _T("Account Created Successfully"), MB_OK);
    
}
