#pragma once

#include <iostream>
using namespace std;
#include <string>

class account{
    public:
        int player_num;  //���ע���˻����
	    string ID;
	    string name;
        string tell;
        string email;
        int password;
        int score;
        account();
        account(int PLAYER_NUM,string _ID, string NAME,string TELL,string EMAIL,int PASSWORD,int SCORE);
        void displayAccount() const;  //�˻���Ϣ��ʾ
};

