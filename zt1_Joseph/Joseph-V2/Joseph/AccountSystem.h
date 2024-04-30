#pragma once

#include <iostream>
using namespace std;
#include <string>
#include <vector>

#include "account.h"

class AccountSystem{
	private:
		vector<account> aSystem;  // 账户系统
	public:
		void createAccount();			// 开户
		vector<account>& getAccounts(); // 获取账户信息
};

