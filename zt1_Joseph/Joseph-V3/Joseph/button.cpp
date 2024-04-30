#include "button.h"

Button::Button() {  //��ʼ��
    x = 0;
    y = 0;
    label = "wrong";
    normalColor = RGB(200, 200, 200);   // ������ɫ
    highlightColor = RGB(0, 225, 225);  // ������ɫ
    highlighted = false;                // ��ʼ״̬Ϊ�Ǹ���
}

// ����¼�������
int Button::onClick(int i, int layer, AccountSystem& account_system, AccountOperation& account_operation, JosephGame& Joseph_game) {
    int re = 0; // ���ر�ʶ��
    if (layer == 1) {
        switch (i) {
            case 0:account_system.createAccount(); break;
            case 1:if (account_operation.SigninAccount() != 0) {
                        MessageBox(GetHWnd(), "Signed in Successfully", _T("YOUR ACCOUNT"), MB_OK);
                        re = 1;
                   } break;
            case 2:account_operation.BrowseSystem(); break;
            case 3:account_operation.SearchSystem(); break;
            case 4:account_operation.ImportData(); break;
            case 5:account_operation.ExportData(); break;
            case 6:closegraph(); break;
            default:cout << "Invalid choice. Please try again." << endl; break;
        }
    }
    else if (layer == 2) {
        switch (i) {
            case 0: account_operation.QueryAccount(); break;
            case 1:account_operation.ModifyAccount(); break;
            case 2:if (account_operation.CancelAccount()) {
                        re = 1;
                   }
                   break;
            case 3:Joseph_game.GameAndScores(0, account_operation.current_player); break;
            case 4:Joseph_game.GameAndScores(1, account_operation.current_player); break;
            case 5: break;
            default:cout << "Invalid choice. Please try again." << endl; break;
        }
    }
    return re;
}

// ���ư�ť
void Button::draw() const {
    setfillcolor(highlighted ? highlightColor : normalColor);
    setbkmode(TRANSPARENT); // ���ñ���͸��
    settextstyle(15, 0, _T("Arial")); // ��ȷָ������Ϊ Arial
    fillrectangle(x, y, x + ButtonWidth, y + ButtonHeight);
    settextcolor(BLACK);

    LOGFONT font;
    gettextstyle(&font); // ��ȡ��ǰ��������
    font.lfWeight = FW_BOLD; // ��������Ӵ�
    settextstyle(&font); // Ӧ���µ���������

    outtextxy(x + 10, y + 10, label.c_str());
}

// ����Ƿ����ڰ�ť��Χ��
bool Button::isClicked(int mouseX, int mouseY) const {
    return (mouseX >= x && mouseX <= x + ButtonWidth && mouseY >= y && mouseY <= y + ButtonHeight);
}