#include "AccountSystem.h"
#include "account.h"

void AccountSystem::createAccount(){ //����
    account newPlayer;

    // �û��趨ID���������绰������
    cout << endl << "-------------Create an Account----------" << endl;
    cout << "Please enter your ID:";
    string ID_temp;
    cin >> ID_temp;
    //��������vector<int>::iterator
    //��֤IDΪ��ҵ�Ψһ��ʶ��
    int ID_flag = 1;
    do {
        ID_flag = 1;
        for (vector<account>::iterator it = aSystem.begin(); it != aSystem.end(); it++)
        {
            if (it->ID == ID_temp) {
                ID_flag = 0;
            }
        }
        if (!ID_flag) {
            cout << "This ID already exists�� Please change and try again." << endl;
            cout << "Please enter your ID:";
            cin >> ID_temp;
        }
    } while (!ID_flag);
    newPlayer.ID = ID_temp;
    cout << "Please enter your name: ";
    cin >> newPlayer.name;
    cout << "Please enter your phone number: ";
    cin >> newPlayer.tell;
    cout << "Please enter your email: ";
    cin >> newPlayer.email;

    // �趨������
    newPlayer.player_num = static_cast<int>(aSystem.size()) + 1;
    // β�巨��������˻�
    aSystem.push_back(newPlayer);

    cout << "-------Account Created Successfully-----" << endl;
    newPlayer.displayAccount();
}

vector<account>& AccountSystem::getAccounts(){
    return aSystem;
}