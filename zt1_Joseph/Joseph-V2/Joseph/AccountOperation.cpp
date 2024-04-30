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
#include <graphics.h>
#include <cstring>
#include <conio.h>

int AccountOperation::SigninAccount() {  //登陆账户

    char str1[20] = { '\0' };
    InputBox(str1, 20, "** Sign in an Account **\nPlease enter your ID:");
    string ID(str1);

    char str2[20] = { '\0' };
    InputBox(str2, 20, "** Sign in an Account **\nPlease enter your password:");
    int password = stoi(str2);;

    account accout_wrong;
    auto& aSystem = p_aSystem->getAccounts();
    for (auto& account : aSystem) { //遍历查找
        if (account.ID == ID) {
            if (account.password == password) {
                current_player = account.player_num;
                cout << "current_player " << current_player << endl;
                return 1;
            }
            else {
                MessageBox(GetHWnd(), "!!!!!Wrong password!!!!!", _T("WARNING"), MB_OK);
                return 0;
            }
        }
    }
    MessageBox(GetHWnd(), "!!!!!Account does not exist!!!!!", _T("WARNING"), MB_OK);
    return 0;
}

void AccountOperation::QueryAccount() {  //查询账户信息
    p_aSystem->getAccounts()[current_player - 1].displayAccount();

}

void AccountOperation::ModifyAccount() {  //修改账户信息

    char str1[20] = { '\0' };
    InputBox(str1, 20, "** Modify Account **\nPlease enter new phone number:");
    p_aSystem->getAccounts()[current_player - 1].tell.assign(str1);

    char str2[20] = { '\0' };
    InputBox(str2, 20, "** Modify Account **\nPlease enter new email:");
    p_aSystem->getAccounts()[current_player - 1].email.assign(str2);

    p_aSystem->getAccounts()[current_player - 1].displayAccount();
}

int AccountOperation::CancelAccount(){  //注销账户
    char str2[20] = { '\0' };
    InputBox(str2, 20, "** Cancel Account **\nSure to cancel your account?(Y/N)");
    char cancel_choice = str2[0]; 

    if (cancel_choice == 'Y') {
        string str = "Account with ID " + p_aSystem->getAccounts()[current_player - 1].ID+ " has been cancelled.";
        MessageBox(GetHWnd(), str.c_str(), _T("Cancel Account"), MB_OK);
        p_aSystem->getAccounts().erase(p_aSystem->getAccounts().begin() + current_player - 1);
        return 1;
    }
    else {
        MessageBox(GetHWnd(), "Fail to Cancel Account", _T("WARNING"), MB_OK);
        return 0;
    }
}

void AccountOperation::BrowseSystem () {
    if (!p_aSystem->getAccounts().size()) {
        MessageBox(GetHWnd(), "!!!!!No player!!!!!", _T("WARNING"), MB_OK);
    }
    else {

        // 定义表格的起始位置和大小
        int startX = 50;
        int startY = 30;
        int cellWidth = 100;
        int cellHeight = 25;
        int numRows = p_aSystem->getAccounts().size() + 1; // 包括表头所以加1

        // 绘制实心白色填充的矩形框
        int rectX = startX;
        int rectY = startY;
        int rectWidth = 400;
        int rectHeight = cellHeight * numRows;
        setfillcolor(WHITE); // 设置填充颜色为白色
        solidrectangle(rectX, rectY, rectX + rectWidth, rectY + rectHeight); // 绘制实心矩形

        // 绘制表格的外框
        rectangle(startX, startY, startX + cellWidth * 3, startY + cellHeight * numRows);


        // 输出表头
        outtextxy(startX + 10, startY + 10, "Rank");
        outtextxy(startX + cellWidth + 10, startY + 10, "ID");
        outtextxy(startX + cellWidth * 2 + 10, startY + 10, "Name");
        outtextxy(startX + cellWidth * 3 + 10, startY + 10, "Score");

        vector<account> sortedAccounts = p_aSystem->getAccounts();
        sort(sortedAccounts.begin(), sortedAccounts.end(),
            [](const account& a, const account& b) { return a.score > b.score; });

        // 输出玩家信息
        int i = 0;
        for (const auto& account : sortedAccounts) {
            int rowY = startY + (i + 1) * cellHeight; // 计算当前行的Y坐标

            // 输出排名
            string rankStr = to_string(i + 1);
            outtextxy(startX + 10, rowY + 10, rankStr.c_str());

            // 输出ID
            outtextxy(startX + cellWidth + 10, rowY + 10, account.ID.c_str());

            // 输出姓名
            outtextxy(startX + cellWidth * 2 + 10, rowY + 10, account.name.c_str());

            // 输出分数
            string scoreStr = to_string(account.score);
            outtextxy(startX + cellWidth * 3 + 10, rowY + 10, scoreStr.c_str());

            i++;
        }
    }
}

void AccountOperation::SearchSystem () {
    vector<account> foundAccounts;
    auto& accounts = p_aSystem->getAccounts(); // 获取账户信息

    char str1[20] = { '\0' };
    InputBox(str1, 20, "** Search Accounts **\nPlease enter your search keyword:");
    string keyword(str1);

    for (const auto& account : accounts) {
        if (account.name.find(keyword) != std::string::npos ||
            account.tell.find(keyword) != std::string::npos ||
            account.email.find(keyword) != std::string::npos ||
            account.ID.find(keyword) != std::string::npos) {
            foundAccounts.push_back(account);
        }
    }
    if (foundAccounts.empty()) {
        MessageBox(GetHWnd(), "!!!!!No matching accounts found!!!!!", _T("WARNING"), MB_OK);
    }
    else {
        std::cout << "Matching accounts:" << std::endl;
        for (const auto& account : foundAccounts) {
            std::cout << "ID: " << account.ID << "\t\tName: " << account.name << std::endl;
        }

        // 定义表格的起始位置和大小
        int startX = 50;
        int startY = 30;
        int cellWidth = 100;
        int cellHeight = 25;
        int numRows = foundAccounts.size() + 1; // 包括表头所以加1

        // 绘制实心白色填充的矩形框
        int rectX = startX;
        int rectY = startY;
        int rectWidth = 400;
        int rectHeight = cellHeight * numRows;
        setfillcolor(WHITE); // 设置填充颜色为白色
        solidrectangle(rectX, rectY, rectX + rectWidth, rectY + rectHeight); // 绘制实心矩形

        // 绘制表格的外框
        rectangle(startX, startY, startX + cellWidth * 3, startY + cellHeight * numRows);


        // 输出表头
        outtextxy(startX + 10, startY + 10, "NUM");
        outtextxy(startX + cellWidth + 10, startY + 10, "ID");
        outtextxy(startX + cellWidth * 2 + 10, startY + 10, "Name");
        outtextxy(startX + cellWidth * 3 + 10, startY + 10, "Tell");

        int i = 0;
        for (const auto& account : foundAccounts) {
            int rowY = startY + (i + 1) * cellHeight; // 计算当前行的Y坐标

            // 输出排名
            string rankStr = to_string(i + 1);
            outtextxy(startX + 10, rowY + 10, rankStr.c_str());

            // 输出ID
            outtextxy(startX + cellWidth + 10, rowY + 10, account.ID.c_str());

            // 输出姓名
            outtextxy(startX + cellWidth * 2 + 10, rowY + 10, account.name.c_str());

            // 输出分数
            string scoreStr = to_string(account.score);
            outtextxy(startX + cellWidth * 3 + 10, rowY + 10, account.tell.c_str());

            i++;
        }
    }
}

int AccountOperation::ExportData () {
    char str1[20] = { '\0' };
    InputBox(str1, 20, "** Export Accounts **\nEnter filename to export data:");
    string filename(str1);

    filename.append(".txt");
    ofstream outfile(filename, std::ios::out | std::ios::trunc);
    if (!outfile.is_open()) {
        MessageBox(GetHWnd(), "Failed to open file for export.", _T("WARNING"), MB_OK);
        return 1;
    }

    // 将账户信息先清空再写入
    auto& accounts = p_aSystem->getAccounts(); // 获取账户信息
    for (const auto& account : accounts) {
        outfile << account.player_num << "\t" << account.ID << "\t" << account.name << "\t";
        outfile << account.tell << "\t" << account.email << "\t" << account.password << "\t" << account.score << endl;
    }
    outfile.close();
    string str = "Account information exported to " + filename;
    MessageBox(GetHWnd(), str.c_str(), _T("WARNING"), MB_OK);
    return 0;
}

int AccountOperation::ImportData () {
    char str1[20] = { '\0' };
    InputBox(str1, 20, "** Import Accounts **\nEnter filename to import data:");
    string filename(str1);
    filename.append(".txt");

    ifstream infile(filename);
    if (!infile.is_open()) {
        MessageBox(GetHWnd(), "Failed to open file for import.", _T("WARNING"), MB_OK);
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
    string str = "Account information imported from " + filename;
    MessageBox(GetHWnd(), str.c_str(), _T("WARNING"), MB_OK);
    infile.close(); // 关闭文件
    return 0;

}
