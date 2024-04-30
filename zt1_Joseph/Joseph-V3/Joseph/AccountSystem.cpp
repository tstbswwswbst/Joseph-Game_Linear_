#include "AccountSystem.h"
#include "account.h"

#include <graphics.h>
#include <string>
#include <conio.h>

void AccountSystem::createAccount(){ //����
    account newPlayer;

    // �û��趨ID���������绰������
    char str1[20] = {'\0'};
    InputBox(str1, 20, "** Create an Account **\nPlease enter your ID:");
    string ID_temp(str1);

    //��������vector<int>::iterator
    //��֤IDΪ��ҵ�Ψһ��ʶ��
    int ID_flag = 1;
    do {
        ID_flag = 1;
        for (vector<account>::iterator it = aSystem.begin(); it != aSystem.end(); it++)
        {
            if (it->ID == ID_temp|| it->ID == "") {
                ID_flag = 0;
                break;
            }
        }
        if (!ID_flag) { //ID�Ѵ���
            MessageBox(GetHWnd(), _T("This ID already exists�� Please change and try again."), _T("WARNING"), MB_OK);
            cout << "This ID already exists�� Please change and try again." << endl;
            InputBox(str1, 10, "** Create an Account **\nPlease enter your ID:");
            ID_temp.assign(str1);
        }
    } while (!ID_flag);
    newPlayer.ID = ID_temp;

    char str2[20] = { '\0' };
    InputBox(str2, 20, "** Create an Account **\nPlease enter your name:");
    newPlayer.name.assign(str2);

    char str3[20] = { '\0' };
    InputBox(str3, 20, "** Create an Account **\nPlease enter your phone number:");
    newPlayer.tell.assign(str3);

    char str4[20] = { '\0' };
    InputBox(str4, 20, "** Create an Account **\nPlease enter your email:");
    newPlayer.email.assign(str4);

    // �趨������
    newPlayer.player_num = static_cast<int>(aSystem.size()) + 1;

    // β�巨��������˻�
    aSystem.push_back(newPlayer);

    newPlayer.displayAccount();
}

vector<account>& AccountSystem::getAccounts(){ // ��ȡ�˻���Ϣ
    return aSystem;
}