#pragma once

#include <iostream>
using namespace std;
#include <string>
#include <vector>

#include "account.h"

class AccountSystem{
	private:
		vector<account> aSystem;  // �˻�ϵͳ
	public:
		void createAccount();			// ����
		vector<account>& getAccounts(); // ��ȡ�˻���Ϣ
};

