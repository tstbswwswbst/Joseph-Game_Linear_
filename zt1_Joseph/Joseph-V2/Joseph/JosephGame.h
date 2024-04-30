#pragma once

#include <iostream>
using namespace std;
#include <string>
#include <vector>

#include "account.h"
#include "AccountSystem.h"

class JosephGame{
	private:
		AccountSystem* p_aSystem;  // �˻�ϵͳָ��
		char game_mode;
		int winner;            // ��ʤ���
		vector<int> CreateCircle();
		int NextPlayer_index(int StartPLayer_index, int BOOM_num, int circleSize, bool clockwise);
		void StartGame();         // ������Ϸ
	public:
		
		JosephGame(AccountSystem* p) { // ��ʼ��
			p_aSystem = p;
			game_mode = 'a';
			winner = 0;
		}
		void GameAndScores(int challen_mode, int challen);    // ��Ϸ���ҽ�����Ϸ����
};

