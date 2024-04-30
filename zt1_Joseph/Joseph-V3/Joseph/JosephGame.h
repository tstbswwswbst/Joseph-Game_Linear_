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
	int num;//���
	int x;//Բ�ĵ�x����
	int y;//Բ�ĵ�y����
	int r;//��ǰԲ�İ뾶��С
	string ID;
	int BOOM_num;
	node* next;
	node* last;
}node, * link;

class JosephGame{
	private:
		int RR;
		int rr;
		AccountSystem* p_aSystem;	// �˻�ϵͳָ��
		int BOOM_num;			    // ����ֵ
		char game_mode;				// ��Ϸģʽ
		string winner_ID;			// ��ʤ���ID
		int winner;					// ��ʤ��ұ��
		void StartGame();			// ������Ϸ
		node* createJoselink(int t);// ����Լɪ��˫������
		node* move(node* p, int n, int step, int direction);             // �������̿��ӻ�
		int deleteNextnode(node*& pre, int n, int& step, int& direction);// ��̭��ҿ��ӻ�
		void printcircle(node* h, int direction);// ��ӡ������ҵ�ԲȦ
		void printtext(node* p, int n);		     // ��ӡ�������ID
	public:
		JosephGame(AccountSystem* p);
		void GameAndScores(int challen_mode, int challen);    // ��Ϸ��������Ϸ����
};

