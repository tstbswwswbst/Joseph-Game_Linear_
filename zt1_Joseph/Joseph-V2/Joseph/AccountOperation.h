#pragma once

#include <iostream>
using namespace std;
#include <string>
#include <vector>

#include "account.h"
#include "AccountSystem.h"

class AccountOperation{
	private:
		AccountSystem* p_aSystem;  // 账户系统指针
	public:
		int current_player;
		AccountOperation(AccountSystem* p) :p_aSystem(p), current_player(0){}; // 初始化
		int SigninAccount();	  // 登录账户
		void QueryAccount();      // 查询账户信息
		void ModifyAccount();     // 修改账户信息
		int CancelAccount();     // 注销账户
		void BrowseSystem();      // 浏览账户系统
		void SearchSystem();      // 查找账户系统
		int ExportData();         // 导出账户信息  注意在哪里放
		int ImportData();         // 导入账户信息
};

