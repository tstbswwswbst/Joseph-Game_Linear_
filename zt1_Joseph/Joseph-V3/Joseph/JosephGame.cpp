#include "JosephGame.h"
#include "AccountSystem.h"

JosephGame::JosephGame(AccountSystem* p) { // 初始化
    p_aSystem = p;
    game_mode = 'a';
    winner = 0;
    RR = 100;
    rr = 40;
    BOOM_num = 3;
}

node* JosephGame::createJoselink(int t) { // 创建约瑟夫双向链表
    node* h = new node;
    node* ph = h;
    node* p;
    for (int i = 0; i < t; i++) {
        p = new node;
        ph->num = i + 1;
        ph->next = p; // 双向
        p->last = ph; // 双向
        ph->r = rr;   // 半径
        ph->x = static_cast<int>((rr + RR) * cos(2 * PI / t * i));
        ph->y = static_cast<int>((rr + RR) * sin(2 * PI / t * i));
        ph->BOOM_num = p_aSystem->getAccounts()[i].password;   // 缓存对应玩家密码
        ph->ID = p_aSystem->getAccounts()[i].ID;               // 缓存对应玩家ID
        if (i != t - 1) ph = p;
        else {
            ph->next = h;
            h->last = ph;
        }
    }
    return h;
}

node* JosephGame::move(node* p, int n, int step, int direction) { // 可视化游戏过程
    int i = step;
    while (--i) {
        p = direction == 1 ? p->next : p->last; // 报数方向
        setbkcolor(RGB(230, 244, 241)); // 背景色
        cleardevice();
        printtext(p, n);
        printcircle(p, direction);
        setfillcolor(RGB(157,68,0));    // 当前报数玩家颜色
        fillcircle(p->x, p->y, rr);
        Sleep(600);
    }
    return p;
}

int JosephGame::deleteNextnode(node*& pre, int n, int& step, int& direction) { // 可视化玩家淘汰过程
    int flag = 1;
    if (pre->last == pre) {  // 只剩一个玩家
        winner_ID = pre->ID; // 该玩家获胜
        flag = 1;
    }
    else {
        flag = 0;
        node* p;
        if (direction == 1) {  // a模式/b模式第一轮 正向报数
            p = pre->next;
            pre->next = p->next;
            p->next->last = pre;
        }
        else {                // a模式/b模式第一轮 反向报数
            p = pre->last;
            pre->last = p->last;
            p->last->next = pre;
        }
        if (game_mode == 'b') {  // b模式后续轮
            step = p->BOOM_num > 0 ? p->BOOM_num : -p->BOOM_num; // 更新报数值
            int last_d = direction;
            direction = p->BOOM_num > 0 ? 1 : 0;                 // 更新报数方向
            // 若报数方向反向 需重新规定起始报数人
            if (direction == 1 && last_d == 0) {
                pre = pre->last;
            }
            else if (direction == 0 && last_d == 1) {
                pre = pre->next;
            }
        }
        free(p);  // 释放内存空间 同时完成玩家淘汰的可视化
    }
    return flag;
}

void JosephGame::printcircle(node* h, int direction) { // 打印代表玩家的圆圈
    setfillcolor(RGB(36, 207, 240));
    node* p = h;
    if (direction == 1) {
        while (p->next != h) {
            fillcircle(p->x, p->y, rr);
            p = p->next;
        }
    }
    else {
        while (p->last != h) {
            fillcircle(p->x, p->y, rr);
            p = p->last;
        }
    }
    fillcircle(p->x, p->y, rr);
}

void JosephGame::printtext(node* p,int n) {     // 打印代表玩家ID
    for (int i = 0; i < n; i++) {
        int x = static_cast<int>((2 * rr + RR + 25) * cos(2 * 3.14159 / n * i));
        int y = static_cast<int>((2 * rr + RR + 25) * sin(2 * 3.14159 / n * i));
        settextcolor(RGB(0,152,184));
        string accountId = p_aSystem->getAccounts()[i].ID;
        outtextxy(x, y, accountId.c_str());
    }
}

void JosephGame::StartGame() { // 进入游戏
    char str2[20] = { '\0' };
    InputBox(str2, 20, "** Game Start Now! **\nPlease choose a game mode (a.simple; b.medium):");
    game_mode = str2[0];

    // 游戏初始化
    int StartPLayer_index = 0;  // 按照开户顺序默认首发为1号玩家
    // 报数值
    char str3[20] = { '\0' };
    InputBox(str3, 20, "** Game Start Now! **\nPlease choose a BOOM_num");
    BOOM_num = atoi(str3);

    int n = static_cast<int>(p_aSystem->getAccounts().size());
    int m = BOOM_num;
    int direction = 1;

    initgraph(800, 450);
    cleardevice();
    setorigin(400, 225);

    node* h = new node;
    h = createJoselink(n);
    node* p = h;

    if (direction == 1) {
        while (p->next != h) {
            p = p->next;
        }//p为h前的一个指针
    }
    else {
        while (p->last != h) {
            p = p->last;
        }//p为后的一个指针
    }

    while (1) {
        p = move(p, n, m, direction);
        if (deleteNextnode(p, n, m, direction)) {
            break;
        }
    }
}

void JosephGame::GameAndScores(int challen_mode,int challen) {  // 游戏并结算游戏积分
    StartGame();

    auto& aSystem = p_aSystem->getAccounts();
    for (auto& account : aSystem) { // 遍历查找出获胜玩家序号
        if (account.ID == winner_ID) {
            winner = account.player_num;
            break;
        }
    }

    if (!challen_mode) {  // 非挑战模式
        auto& aSystem = p_aSystem->getAccounts();
        for (auto& account : aSystem) {
            if (account.player_num == winner) { // 获胜玩家加分
                if (game_mode == 'a') {
                    account.score += 1;
                }
                else if (game_mode == 'b') {
                    account.score += 2;
                }
            }
        }
    }
    else { // 挑战模式
        if (challen == winner) { // 挑战者获胜
            auto& aSystem = p_aSystem->getAccounts();
            for (auto& account : aSystem) {
                if (account.player_num == winner) { // 积分翻倍
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
            for (auto& account : aSystem) {
                if (account.player_num == winner) { // 获胜玩家积分增加
                    if (game_mode == 'a') {
                        account.score += 1;
                    }
                    else if (game_mode == 'b') {
                        account.score += 2;
                    }
                }
                else if (account.player_num == challen) { // 挑战玩家积分减少
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

    string str = winner_ID + " wins!\nThe score board is updated.";
    MessageBox(GetHWnd(), str.c_str(), _T("GAME OVER"), MB_OK);
}