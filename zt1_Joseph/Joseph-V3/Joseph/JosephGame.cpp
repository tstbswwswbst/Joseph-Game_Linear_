#include "JosephGame.h"
#include "AccountSystem.h"

JosephGame::JosephGame(AccountSystem* p) { // ��ʼ��
    p_aSystem = p;
    game_mode = 'a';
    winner = 0;
    RR = 100;
    rr = 40;
    BOOM_num = 3;
}

node* JosephGame::createJoselink(int t) { // ����Լɪ��˫������
    node* h = new node;
    node* ph = h;
    node* p;
    for (int i = 0; i < t; i++) {
        p = new node;
        ph->num = i + 1;
        ph->next = p; // ˫��
        p->last = ph; // ˫��
        ph->r = rr;   // �뾶
        ph->x = static_cast<int>((rr + RR) * cos(2 * PI / t * i));
        ph->y = static_cast<int>((rr + RR) * sin(2 * PI / t * i));
        ph->BOOM_num = p_aSystem->getAccounts()[i].password;   // �����Ӧ�������
        ph->ID = p_aSystem->getAccounts()[i].ID;               // �����Ӧ���ID
        if (i != t - 1) ph = p;
        else {
            ph->next = h;
            h->last = ph;
        }
    }
    return h;
}

node* JosephGame::move(node* p, int n, int step, int direction) { // ���ӻ���Ϸ����
    int i = step;
    while (--i) {
        p = direction == 1 ? p->next : p->last; // ��������
        setbkcolor(RGB(230, 244, 241)); // ����ɫ
        cleardevice();
        printtext(p, n);
        printcircle(p, direction);
        setfillcolor(RGB(157,68,0));    // ��ǰ���������ɫ
        fillcircle(p->x, p->y, rr);
        Sleep(600);
    }
    return p;
}

int JosephGame::deleteNextnode(node*& pre, int n, int& step, int& direction) { // ���ӻ������̭����
    int flag = 1;
    if (pre->last == pre) {  // ֻʣһ�����
        winner_ID = pre->ID; // ����һ�ʤ
        flag = 1;
    }
    else {
        flag = 0;
        node* p;
        if (direction == 1) {  // aģʽ/bģʽ��һ�� ������
            p = pre->next;
            pre->next = p->next;
            p->next->last = pre;
        }
        else {                // aģʽ/bģʽ��һ�� ������
            p = pre->last;
            pre->last = p->last;
            p->last->next = pre;
        }
        if (game_mode == 'b') {  // bģʽ������
            step = p->BOOM_num > 0 ? p->BOOM_num : -p->BOOM_num; // ���±���ֵ
            int last_d = direction;
            direction = p->BOOM_num > 0 ? 1 : 0;                 // ���±�������
            // ������������ �����¹涨��ʼ������
            if (direction == 1 && last_d == 0) {
                pre = pre->last;
            }
            else if (direction == 0 && last_d == 1) {
                pre = pre->next;
            }
        }
        free(p);  // �ͷ��ڴ�ռ� ͬʱ��������̭�Ŀ��ӻ�
    }
    return flag;
}

void JosephGame::printcircle(node* h, int direction) { // ��ӡ������ҵ�ԲȦ
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

void JosephGame::printtext(node* p,int n) {     // ��ӡ�������ID
    for (int i = 0; i < n; i++) {
        int x = static_cast<int>((2 * rr + RR + 25) * cos(2 * 3.14159 / n * i));
        int y = static_cast<int>((2 * rr + RR + 25) * sin(2 * 3.14159 / n * i));
        settextcolor(RGB(0,152,184));
        string accountId = p_aSystem->getAccounts()[i].ID;
        outtextxy(x, y, accountId.c_str());
    }
}

void JosephGame::StartGame() { // ������Ϸ
    char str2[20] = { '\0' };
    InputBox(str2, 20, "** Game Start Now! **\nPlease choose a game mode (a.simple; b.medium):");
    game_mode = str2[0];

    // ��Ϸ��ʼ��
    int StartPLayer_index = 0;  // ���տ���˳��Ĭ���׷�Ϊ1�����
    // ����ֵ
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
        }//pΪhǰ��һ��ָ��
    }
    else {
        while (p->last != h) {
            p = p->last;
        }//pΪ���һ��ָ��
    }

    while (1) {
        p = move(p, n, m, direction);
        if (deleteNextnode(p, n, m, direction)) {
            break;
        }
    }
}

void JosephGame::GameAndScores(int challen_mode,int challen) {  // ��Ϸ��������Ϸ����
    StartGame();

    auto& aSystem = p_aSystem->getAccounts();
    for (auto& account : aSystem) { // �������ҳ���ʤ������
        if (account.ID == winner_ID) {
            winner = account.player_num;
            break;
        }
    }

    if (!challen_mode) {  // ����սģʽ
        auto& aSystem = p_aSystem->getAccounts();
        for (auto& account : aSystem) {
            if (account.player_num == winner) { // ��ʤ��Ҽӷ�
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
        if (challen == winner) { // ��ս�߻�ʤ
            auto& aSystem = p_aSystem->getAccounts();
            for (auto& account : aSystem) {
                if (account.player_num == winner) { // ���ַ���
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
            for (auto& account : aSystem) {
                if (account.player_num == winner) { // ��ʤ��һ�������
                    if (game_mode == 'a') {
                        account.score += 1;
                    }
                    else if (game_mode == 'b') {
                        account.score += 2;
                    }
                }
                else if (account.player_num == challen) { // ��ս��һ��ּ���
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