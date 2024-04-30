#include "JosephGame.h"

#include <iostream>
using namespace std;
#include <string>
#include <vector>

vector<int> JosephGame::CreateCircle() { // ����Լɪ��
    vector<int> circle;
    auto& accounts = p_aSystem->getAccounts();
    for (size_t i = 0; i < accounts.size(); ++i) {
        circle.push_back(static_cast<int>(i));
    }
    return circle;
}

int JosephGame::NextPlayer_index(int StartPLayer_index, int BOOM_num, int circleSize, bool clockwise) {
    if (clockwise) {  // ����Լɪ����Ϸ
        return (StartPLayer_index + BOOM_num - 1 + circleSize) % circleSize; // ����0->��circleSize-1��
    }
    else {  // ����Լɪ����Ϸ
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
	cout << endl << "--------------Game Start Now!------------" << endl;
	cout << "Please choose a game mode (a.simple; b.medium):";
	cin >> game_mode;

    // ��Ϸ��ʼ��
    int StartPLayer_index = 0;  // ���տ���˳��Ĭ���׷�Ϊ1�����
    int BOOM_num = 2;           // ����ֵ��ʼ��Ϊ2
    bool clockwise = true;      // ������ʼ˳��Ϊ˳ʱ��
    int out_password = 1;       // �е�ģʽ��Ҫ������;��̭�ߵ�����
    int round = 1;              // �غ���
    int OutPLayer_index = 0;          // ��ǰ���γ���������

    vector<int> circle = CreateCircle();
    int circleSize = static_cast<int>(circle.size());
    auto& accounts = p_aSystem->getAccounts(); // ��ȡ�˻���Ϣ

    while (circle.size() > 1) {
        // ��ģʽ���е�ģʽ��һ��
        if (game_mode == 'a' || (game_mode == 'b' && round == 1)) {
            StartPLayer_index = NextPlayer_index(StartPLayer_index, BOOM_num, circleSize, clockwise);
        }
        // �е�ģʽ�ڶ��ּ��Ժ�
        else if (game_mode == 'b') {
            if (out_password < 0) {
                clockwise = false;   // ����Ϊ������˳����
            }
            else {
                clockwise = true;
            }
            BOOM_num = abs(out_password);
            StartPLayer_index = NextPlayer_index(StartPLayer_index, BOOM_num, circleSize, clockwise);
        }
        else {
            cout << "!!!!!Invalid Game Mode!!!!" << endl;
            cout << "Please choose a right game mode (a.simple; b.medium):";
            cin >> game_mode;
            continue;
        }

        cout << "Round " << round << ":  " << accounts[circle[StartPLayer_index]].name << " is out." << endl;
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
    cout << p_aSystem->getAccounts()[circle[0]].ID << " wins!" << endl;
    winner = p_aSystem->getAccounts()[circle[0]].player_num;
}

void JosephGame::GameAndScores(int challen_mode,int challen) {
    StartGame();
    if (!challen_mode) {  // ����սģʽ
        auto& aSystem = p_aSystem->getAccounts();
        for (auto& account : aSystem) { //��������
            if (account.player_num == winner) {
                if (game_mode == 'a') {
                    account.score += 1;
                }
                else if (game_mode == 'b') {
                    account.score += 2;
                }
            }
        }
    }
    else { // ��սģʽ
        int same = 0;
        if (challen == winner) {
            same = 1;
        }
        if (same) { // ��ս�߻�ʤ
            auto& aSystem = p_aSystem->getAccounts();
            for (auto& account : aSystem) { //��������
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
        else { // ��ս��ʧ��
            auto& aSystem = p_aSystem->getAccounts();
            for (auto& account : aSystem) { //��������
                if (account.player_num == winner) {
                    if (game_mode == 'a') {
                        account.score += 1;
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