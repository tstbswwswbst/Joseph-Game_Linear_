#pragma once

#include <iostream>
using namespace std;
#include <string>
#include <vector>
#include <graphics.h>
#include <math.h>
#include <conio.h>

#include "account.h"
#include "AccountSystem.h"
#define PI 3.1415926

typedef struct node
{
	int num;//编号
	int x;//圆心的x坐标
	int y;//圆心的y坐标
	int r;//当前圆的半径大小
	string ID;
	int BOOM_num;
	node* next;
	node* last;
}node, * link;

class JosephGame{
	private:
		int RR;
		int rr;
		AccountSystem* p_aSystem;	// 账户系统指针
		int BOOM_num;			    // 报数值
		char game_mode;				// 游戏模式
		string winner_ID;			// 获胜玩家ID
		int winner;					// 获胜玩家编号
		void StartGame();			// 进入游戏
		node* createJoselink(int t);// 创建约瑟夫双向链表
		node* move(node* p, int n, int step, int direction);             // 报数过程可视化
		int deleteNextnode(node*& pre, int n, int& step, int& direction);// 淘汰玩家可视化
		void printcircle(node* h, int direction);// 打印代表玩家的圆圈
		void printtext(node* p, int n);		     // 打印代表玩家ID
	public:
		JosephGame(AccountSystem* p);
		void GameAndScores(int challen_mode, int challen);    // 游戏并结算游戏积分
};

