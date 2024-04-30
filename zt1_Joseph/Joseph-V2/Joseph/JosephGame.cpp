#include "JosephGame.h"

#include <iostream>
using namespace std;
#include <string>
#include <vector>
#include <graphics.h>
#include <cstring>
#include <conio.h>

vector<int> JosephGame::CreateCircle() { // 创建约瑟夫环
    vector<int> circle;
    auto& accounts = p_aSystem->getAccounts();
    for (size_t i = 0; i < accounts.size(); ++i) {
        circle.push_back(static_cast<int>(i));
    }
    return circle;
}

int JosephGame::NextPlayer_index(int StartPLayer_index, int BOOM_num, int circleSize, bool clockwise) {
    if (clockwise) {  // 正向约瑟夫游戏
        return (StartPLayer_index + BOOM_num - 1 + circleSize) % circleSize; // 返回0->（circleSize-1）
    }
    else {  // 反向约瑟夫游戏
        int nextIndex = StartPLayer_index - (BOOM_num - 1 + circleSize) % circleSize;
        if (nextIndex < 0) {
            return circleSize + nextIndex;
        }
        else {
            return nextIndex;
        }
    }
}

void JosephGame::StartGame() {
    char str2[20] = { '\0' };
    InputBox(str2, 20, "** Game Start Now! **\nPlease choose a game mode (a.simple; b.medium):");
    char game_mode = str2[0];

    // 游戏初始化
    int StartPLayer_index = 0;  // 按照开户顺序默认首发为1号玩家
    // 报数值
    char str3[20] = { '\0' };
    InputBox(str3, 20, "** Game Start Now! **\nPlease choose a BOOM_num");
    int BOOM_num = atoi(str3);

    bool clockwise = true;      // 报数初始顺序为顺时针
    int out_password = 1;       // 中等模式需要保存中途淘汰者的密码
    int round = 1;              // 回合数
    int OutPLayer_index = 0;          // 当前场次出局玩家序号

    vector<int> circle = CreateCircle();
    int circleSize = static_cast<int>(circle.size());
    auto& accounts = p_aSystem->getAccounts(); // 获取账户信息

    while (circle.size() > 1) {
        // 简单模式或中等模式第一轮
        if (game_mode == 'a' || (game_mode == 'b' && round == 1)) {
            StartPLayer_index = NextPlayer_index(StartPLayer_index, BOOM_num, circleSize, clockwise);
        }
        // 中等模式第二轮及以后
        else if (game_mode == 'b') {
            if (out_password < 0) {
                clockwise = false;   // 密码为负报数顺序反向
            }
            else {
                clockwise = true;
            }
            BOOM_num = abs(out_password);
            StartPLayer_index = NextPlayer_index(StartPLayer_index, BOOM_num, circleSize, clockwise);
        }
        else {
            MessageBox(GetHWnd(), "!!!!!Invalid Game Mode!!!!", _T("WARNING"), MB_OK);
            InputBox(str2, 20, "** Game Start Now! **\nPlease choose a game mode (a.simple; b.medium):");
            game_mode = str2[0];
            continue;
        }

        out_password = accounts[circle[StartPLayer_index]].password;
        circle.erase(circle.begin() + StartPLayer_index);
        circleSize--;
        if (clockwise == false) {
            StartPLayer_index = (StartPLayer_index - 1 + circleSize) % circleSize;
        }
        else if (clockwise == true) {
            StartPLayer_index = StartPLayer_index % circleSize;
        }
        round++;
    }
    string str = p_aSystem->getAccounts()[circle[0]].ID + " wins!\nThe score board is updated.";
    MessageBox(GetHWnd(), str.c_str(), _T("GAME OVER"), MB_OK);
    winner = p_aSystem->getAccounts()[circle[0]].player_num;
}

void JosephGame::GameAndScores(int challen_mode,int challen) {
    StartGame();
    if (!challen_mode) {  // 非挑战模式
        auto& aSystem = p_aSystem->getAccounts();
        for (auto& account : aSystem) { //遍历查找
            if (account.player_num == winner) {
                if (game_mode == 'a') {
                    account.score += 1;
                    cout << "account.score += 1;" << endl;
                }
                else if (game_mode == 'b') {
                    account.score += 2;
                }
            }
        }
    }
    else { // 挑战模式
        int same = 0;
        if (challen == winner) {
            same = 1;
        }
        if (same) { // 挑战者获胜
            auto& aSystem = p_aSystem->getAccounts();
            for (auto& account : aSystem) { //遍历查找
                if (account.player_num == winner) {
                    if (game_mode == 'a') {
                        account.score *= 2;
                    }
                    else if (game_mode == 'b') {
                        account.score *= 3;
                    }
                }
            }
        }
        else { // 挑战者失败
            auto& aSystem = p_aSystem->getAccounts();
            for (auto& account : aSystem) { //遍历查找
                if (account.player_num == winner) {
                    if (game_mode == 'a') {
                        account.score += 1;
                        cout << "account.score += 1;" << endl;
                    }
                    else if (game_mode == 'b') {
                        account.score += 2;
                    }
                }
                else if (account.player_num == challen) {
                    if (game_mode == 'a') {
                        account.score -= 2;
                    }
                    else if (game_mode == 'b') {
                        account.score -= 4;
                    }
                }
            }
        }
    }
}