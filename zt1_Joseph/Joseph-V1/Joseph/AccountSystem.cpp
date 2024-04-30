#include "AccountSystem.h"
#include "account.h"

void AccountSystem::createAccount(){ //开户
    account newPlayer;

    // 用户设定ID、姓名、电话、邮箱
    cout << endl << "-------------Create an Account----------" << endl;
    cout << "Please enter your ID:";
    string ID_temp;
    cin >> ID_temp;
    //迭代器：vector<int>::iterator
    //保证ID为玩家的唯一标识符
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
            cout << "This ID already exists！ Please change and try again." << endl;
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

    // 设定玩家序号
    newPlayer.player_num = static_cast<int>(aSystem.size()) + 1;
    // 尾插法插入玩家账户
    aSystem.push_back(newPlayer);

    cout << "-------Account Created Successfully-----" << endl;
    newPlayer.displayAccount();
}

vector<account>& AccountSystem::getAccounts(){
    return aSystem;
}