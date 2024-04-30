#pragma once

#include <iostream>
using namespace std;
#include <string>
#include <vector>

#include "account.h"
#include "AccountSystem.h"

class AccountOperation{
	private:
		AccountSystem* p_aSystem;  // �˻�ϵͳָ��
	public:
		int current_player;
		AccountOperation(AccountSystem* p) :p_aSystem(p), current_player(0){}; // ��ʼ��
		int SigninAccount();	  // ��¼�˻�
		void QueryAccount();      // ��ѯ�˻���Ϣ
		void ModifyAccount();     // �޸��˻���Ϣ
		int CancelAccount();     // ע���˻�
		void BrowseSystem();      // ����˻�ϵͳ
		void SearchSystem();      // �����˻�ϵͳ
		int ExportData();         // �����˻���Ϣ  ע���������
		int ImportData();         // �����˻���Ϣ
};

