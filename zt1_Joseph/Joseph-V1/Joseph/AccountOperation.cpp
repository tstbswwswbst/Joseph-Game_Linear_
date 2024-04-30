#include "AccountOperation.h"
#include "account.h"
#include "AccountSystem.h"

#include <iostream>
using namespace std;
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>

int AccountOperation::SigninAccount() {  //登陆账户
    cout << endl << "------------Sign in an Account-----------" << endl;
    cout << "Please enter your account ID:";
    string ID;
    cin >> ID; //ID作为玩家身份唯一标识符

    cout << "Please enter your password:";
    int password;
    cin >> password;

    account accout_wrong;
    auto& aSystem = p_aSystem->getAccounts();
    for (auto& account : aSystem) { //遍历查找
        if (account.ID == ID) {
            if (account.password == password) {
                current_player = account.player_num;
                return 1;
            }
            else {
                cout << "!!!!!Wrong password!!!!!" << endl;
                return 0;
            }
        }
    }
    cout << "!!!!!Account does not exist!!!!!" << endl;
    return 0;
}

void AccountOperation::QueryAccount() {  //查询账户信息
    cout << endl << "---------------Query Result-------------" << endl;
    p_aSystem->getAccounts()[current_player-1].displayAccount();
}

void AccountOperation::ModifyAccount() {  //修改账户信息
    cout << "Enter new phone number: ";
    cin >> p_aSystem->getAccounts()[current_player - 1].tell;
    cout << "Enter new email: ";
    cin >> p_aSystem->getAccounts()[current_player - 1].email;
    cout << endl << "----------Updated Successfully----------" << endl;
    p_aSystem->getAccounts()[current_player - 1].displayAccount();
}

void AccountOperation::CancelAccount(){  //注销账户
    cout << "Sure to cancel your account?(Y/N)" << endl;
    char cancel_choice;
    cin >> cancel_choice;
    if (cancel_choice == 'Y') {
        cout << "Account with ID " << p_aSystem->getAccounts()[current_player - 1].ID << " has been cancelled." << endl;
        p_aSystem->getAccounts().erase(p_aSystem->getAccounts().begin() + current_player - 1);
    }
    else {
        cout << endl << "---------Fail to Cancel Account---------" << endl;
    }
}

void AccountOperation::BrowseSystem () {
    if (!p_aSystem->getAccounts().size()) {
        cout << "!!!!!No player!!!!!" << endl;
    }
    else {
        vector<account> sortedAccounts = p_aSystem->getAccounts();
        sort(sortedAccounts.begin(), sortedAccounts.end(),
            [](const account& a, const account& b) { return a.score > b.score; });
        cout << endl << "----------------Scoreboard---------------" << endl;
        cout << "Rank in the score descending order:" << endl;
        for (const auto& account : sortedAccounts) {
            cout << "ID: " << account.ID << "\t\tName: " << account.name << "\t\tScore: " << account.score << endl;
        }
        cout << "Total number of players: " << p_aSystem->getAccounts().size() << endl;
    }
}

void AccountOperation::SearchSystem () {
    string keyword;
    vector<account> foundAccounts;
    auto& accounts = p_aSystem->getAccounts(); // 获取账户信息

    cout << endl << "------------Search Accounts-------------" << endl;
    cout << "Please enter your search keyword:";
    cin >> keyword;
    for (const auto& account : accounts) {
        if (account.name.find(keyword) != std::string::npos ||
            account.tell.find(keyword) != std::string::npos ||
            account.email.find(keyword) != std::string::npos ||
            account.ID.find(keyword) != std::string::npos) {
            foundAccounts.push_back(account);
        }
    }
    if (foundAccounts.empty()) {
        std::cout << "!!!!!No matching accounts found!!!!!" << std::endl;
    }
    else {
        std::cout << "Matching accounts:" << std::endl;
        for (const auto& account : foundAccounts) {
            std::cout << "ID: " << account.ID << "\t\tName: " << account.name << std::endl;
        }
    }
}

int AccountOperation::ExportData () {
    cout << endl << "------------Export Accounts-------------" << endl;
    string filename;
    cout << "Enter filename to export data: ";
    cin >> filename;
    filename.append(".txt");
    ofstream outfile(filename, std::ios::out | std::ios::trunc);
    if (!outfile.is_open()) {
        cerr << "Failed to open file for export." << std::endl;
        return 1;
    }

    // 将账户信息先清空再写入
    auto& accounts = p_aSystem->getAccounts(); // 获取账户信息
    for (const auto& account : accounts) {
        outfile << account.player_num << "\t" << account.ID << "\t" << account.name << "\t";
        outfile << account.tell << "\t" << account.email << "\t" << account.password << "\t" << account.score << endl;
    }
    outfile.close();
    cout << "Account information exported to "<< filename << endl;
    return 0;
}

int AccountOperation::ImportData () {
    cout << endl << "------------Import Accounts-------------" << endl;
    string filename;
    cout << "Enter filename to import data: ";
    cin >> filename;
    filename.append(".txt");
    ifstream infile(filename);
    if (!infile.is_open()) {
        cerr << "Failed to open file for import." << endl;
        return 1;
    }

    vector<account> accounts; // 存储账户信息的容器

    string line;
    p_aSystem->getAccounts().clear();

    while (getline(infile, line)) { // 逐行读取文件内容
        istringstream temp_string(line);
        int PLAYER_NUM; //玩家序号
        string _ID;
        string NAME;
        string TELL;
        string EMAIL;
        int PASSWORD;
        int SCORE;
        temp_string >> PLAYER_NUM >> _ID >> NAME >> TELL >> EMAIL >> PASSWORD >> SCORE;
        // 将解析得到的账户信息存入容器中
        account newaccount(PLAYER_NUM, _ID, NAME, TELL, EMAIL, PASSWORD, SCORE);
        p_aSystem->getAccounts().push_back(newaccount);
    }
    cout << "Account information imported from " << filename << endl;
    infile.close(); // 关闭文件
    return 0;
}
