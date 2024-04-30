#pragma once

#include <iostream>
using namespace std;
#include <string>
#include <vector>

#include "account.h"
#include "AccountSystem.h"

class JosephGame{
	private:
		AccountSystem* p_aSystem;  // 账户系统指针
		char game_mode;
		int winner;            // 获胜玩家
		vector<int> CreateCircle();
		int NextPlayer_index(int StartPLayer_index, int BOOM_num, int circleSize, bool clockwise);
		void StartGame();         // 进入游戏
	public:
		
		JosephGame(AccountSystem* p) { // 初始化
			p_aSystem = p;
			game_mode = 'a';
			winner = 0;
		}
		void GameAndScores(int challen_mode, int challen);    // 游戏并且结算游戏积分
};

