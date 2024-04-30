#include <iostream>
using namespace std;
#include <string>
#include "AccountSystem.h"
#include "AccountOperation.h"
#include "JosephGame.h"

int main() {
	AccountSystem account_system;
    AccountOperation account_operation(&account_system);
    JosephGame Joseph_game(&account_system);

    int sys_choice;
    int acc_choice;
    do {
        cout << "\n1. Sign up\n2. Sign in\n3. Browse Accounts\n4. Search Accounts\n5. Import Data\n6. Export Data\n0. Exit\n";
        cout << "Enter your choice: ";
        cin >> sys_choice;
        switch (sys_choice) {
        case 1:
            account_system.createAccount();
            break;
        case 2:
            if (account_operation.SigninAccount() != 0) {
                cout << "----------Signed in Successfully---------" << endl;
                do {
                    cout << "\n1. Query Account\n2. Modify Account\n3. Cancel Account\n4. Start Game\n5. Chanllenge Game\n0. Exit Account\n";
                    cout << "Enter your choice: ";
                    cin >> acc_choice;
                    switch (acc_choice) {
                    case 1:
                        account_operation.QueryAccount();
                        break;
                    case 2:
                        account_operation.ModifyAccount();
                        break;
                    case 3:
                        account_operation.CancelAccount();
                        acc_choice = 0;
                        break;
                    case 4:
                        Joseph_game.GameAndScores(0, account_operation.current_player);
                        break;
                    case 5:
                        Joseph_game.GameAndScores(1, account_operation.current_player);
                        break;
                    case 0:
                        break;
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                    }
                }while(acc_choice != 0);
            }
            break;
        case 3:
            account_operation.BrowseSystem();
            break;
        case 4:
            account_operation.SearchSystem();
            break;
        case 5:
            account_operation.ImportData();
            break;
        case 6:
            account_operation.ExportData();
            break;
        case 0:
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (sys_choice != 0);
	return 0;
}