#include<iostream>
#include<sstream>
#include <iomanip>
using namespace std;
#include "CheckAndSearch.h"
#include"map.h"
#include "UsersAndGoods.h"
#include "Creat.h"
#include "File.h"
extern void _MainMenu(int i);
extern void _Send();
extern void _Punish(const string reported_id);
extern void _Deblock();
void _Report();
string name;
string pass;
string id;
string cur_id;
static struct Report report;
void _Register()
{
	int flag = 1;
	while (1 == flag)
	{
		bool is_existed = false;
		cin.ignore();
		cout << "�������û�����ע�⣺��Ҫ����ո񣡣���";
		getline(cin, name);
		for (auto it = name.begin(); it != name.end();)
		{
			if (*it == ' ')
			{
				cout << "�벻Ҫ����ո����������룺 ";
				getline(cin, name);
				it = name.begin();
			}
			else
				++it;
		}
		for (auto it = users.begin(); it != users.end(); ++it)
		{
			if (it->second.exist)
			{
				if (it->second.name == name)
				{
					is_existed = true;
					cout << "�û����Ѵ���, �޷�ע�ᣡ ��ѡ��1������ע��  2��ȡ��ע�ᣩ"<<endl;
					cout << "�����룺";
					cin >> flag;
					while (cin.fail())
					{
						cout << "�밴Ҫ��������Ҫ���еĲ�������ţ�" << endl;
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "�����룺";
						cin >> flag;
					}
					cin.ignore();
					if (flag != 1 && flag != 2)
					{
						cout <<endl<< "���벻�Ϸ��������˳�ע�ᣡ" << endl;
						flag = 2;
					}
				}
			}
		}
		if (!is_existed)
		{
			cout << "���������루������20���ַ�������������Ӣ���ַ������֣���";
			getline(cin, pass);
			for (auto it = pass.begin(); it != pass.end(); )
			{
				if (*it == ' ')
				{
					cout << "�벻Ҫ����ո����������룺 ";
					getline(cin, pass);
					it = pass.begin();
				}
				else
					++it;
			}
			struct User u;
			u.name = name;
			u.password = pass;
			cout << "��������ϵ��ʽ��";
			getline(cin, u.tel);
			for (auto it = u.tel.begin(); it != u.tel.end(); )
			{
				if (*it == ' ')
				{
					it = u.tel.erase(it);
				}
				else
					++it;
			}
			cout << "�������ַ��";
			getline(cin, u.adr);
			for (auto it = u.adr.begin(); it != u.adr.end(); )
			{
				if (*it == ' ')
				{
					it = u.adr.erase(it);
				}
				else
					++it;
			}		
			u.buyer_eval[1] = "��δ�յ��κ����ۣ�";
			_ForCreat('U', count_users);
			users[id] = u;
			++count_users;
			_DateFile("users.txt", "users");
			flag = 2;
		}
	}
}

void _UserEnter()
{
	cout << "�������û�����";
	cin.ignore();
	getline(cin, name);
	cout << "���������룺";
	getline(cin, pass);
	auto it = users.begin();
	for (; it != users.end(); ++it)
	{
		if (it ->second.exist && it->second.name == name)
			break;
	}
	if (it != users.end())
	{
		auto it1 = reported_users.find(it->first);
		if (it1 != reported_users.end() &&  it1->second.on_punishment)
		{
			time_t now = time(0);
			tm* ltm = localtime(&now);
			int cur_year, cur_mon, cur_day;
			cur_year = ltm->tm_year + 1900;
			cur_mon = ltm->tm_mon + 1;
			cur_day = ltm->tm_mday;
			int y, m, d;
			sscanf(it1->second.end_time.c_str(), "%d-%d-%d", &y, &m, &d);
			if (cur_year > y)
			{
				it1->second.on_punishment = false;
				_DateFile("reported_users.txt", "reported");
			}
			else
				if (cur_year == y)
				{
					if (cur_mon > m)
					{
						it1->second.on_punishment = false;
						_DateFile("reported_users.txt", "reported");
					}
					else
						if(cur_mon == m)
							{
							if (cur_day >= d)
							{
								it1->second.on_punishment = false;
								_DateFile("reported_users.txt", "reported");
							}
							}
				}
		}
		if (it1 == reported_users.end() || !it1->second.on_punishment)
		{
			if (it->second.password == pass)
			{
				cur_id = it->first;
				cout << "***************************   ��¼�ɹ�����ӭ�����û�����!   ***************************" << endl << endl;
				while (true)
				{
					cout << endl << endl;
					cout << "-------------------------------------------------------------------------------------------------------------" << endl;
					cout << "   1��ע����¼	    2���������       3����������       4��������Ϣ����    5���ٱ��û�    6���鿴�ٱ���Ϣ" << endl;
					cout << "-------------------------------------------------------------------------------------------------------------" << endl;
					int i;
					cout << "��������Ҫ���еĲ�����ѡ� ";
					cin >> i;
					while (cin.fail())
					{
						cout << "�밴Ҫ��������Ҫ���еĲ�������ţ�" << endl;
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "�����룺 ";
						cin >> i;
					}
					if (i == 1)
						break;
					else
						_MainMenu(i);
				}
			}
			else
			{
				cout << "********************   ������󣬵�¼ʧ��!   ********************" << endl << endl;
			}
		}
		else
		{
			
			cout << "*****************************************************************************" << endl;
			cout << "���ھٱ��������ޣ� �����˺ű���ʱ���ᣡ" << endl;
			cout << "�������Ϊ��"<<it1->second.end_time<<endl;
			cout << "*****************************************************************************" << endl<<endl;
		}
	}
	else
		cout << "********************   �û������ڣ�����ע�ᣡ   ********************" << endl<<endl;
	
}

void _AdmEnter()
{
	cout << "�������û�����";
	cin >> name;
	cout << "���������룺";
	cin >> pass;
	auto it = adm.begin();
	if (name == it->first)
	{
		if (pass == it->second)
		{
			cout << "***************************   ��¼�ɹ�����ӭ��������Ա����!   ***************************" << endl << endl;
			int m;
			while (true)
			{
				cout << endl;
				cout << "------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
				cout << "         1���鿴������Ʒ  2��������Ʒ  3���鿴���ж���  4���鿴�����û�  5��ɾ���û�  6���¼���Ʒ 7���鿴�ٱ���Ϣ 8���ⶳ�û��˻�  9��ע��" << endl;
				cout << "------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
				cout << "��������Ҫ���еĲ�������ţ�";
				cin >> m;
				while (cin.fail())
				{
					cout << "�밴Ҫ��������Ҫ���еĲ�������ţ�" << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "�����룺 ";
					cin >> m;
				}
				if (9 == m)
					break;
				switch (m)
				{
				case 1:
				{
					_CheckGoods("adm");
					break;
				}
				case 2:
				{
					_SearchGoods("adm");
					break;
				}
				case 3:
				{
					_CheckOrders("adm");
					break;
				}
				case 4:
				{
					_CheckAllUsers();
					break;
				}
				case 5:
				{
					_DeleteUser();
					break;
				}
				case 6:
				{
					_RemoveGoods("adm");
					break;
				}
				case 7:
				{
					_AdmCheckReportedInf();
					break;
				}
				case 8:
				{
					_Deblock();
					break;
				}
				default: cout << "���벻�Ϸ������������룡" << endl << endl;
				}

			}

		}
		else
			cout << "�û������������벻��ȷ����½ʧ�ܣ�" << endl<<endl;
	}
	else
		cout << "�û������������벻��ȷ����½ʧ�ܣ�" << endl<<endl;

}
void _MainMenu(int i)
{
	
	switch (i)
	{
	case 2:
	{
		int n;
		while (true)
		{
			cout << endl;
			cout << "--------------------------------------------------------------------------------------------------------" << endl;
			cout << "  1���鿴��Ʒ�б�  2��������Ʒ  3��������Ʒ  4���鿴��ʷ����  5���鿴��Ʒ��ϸ��Ϣ  6�������û�������" << endl;
			cout << "--------------------------------------------------------------------------------------------------------" << endl;
			cout << "��������Ҫ���еĲ�������ţ�";
			cin >> n;
			while (cin.fail())
			{
				cout << "�밴Ҫ��������Ҫ���еĲ�������ţ�" << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "�����룺 ";
				cin >> n;
			}
			if (6 == n)
			{
				break;
			}
			switch (n)
			{
			case 1:
			{
				_CheckGoods("buyer");
				break;
			}
			case 2:
			{
				_Buy();
				break;
			}
			case 3:
			{
				_SearchGoods("buyer");
				break;
			}
			case 4:
			{
				_CheckOrders("buyer");
				break;
			}
			case 5:
			{
				_CheckDetailedGoods();
				break;
			}
			default:cout << "***********************   �밴Ҫ�����룡   ***********************" << endl << endl;
			}
		}
		break;
	}
	case 3:
	{
		int m;
		while (true)
		{
			cout << endl;
			cout << "----------------------------------------------------------------------------------------------------------------------------" << endl;
			cout << "      1��������Ʒ  2���鿴������Ʒ  3���޸���Ʒ��Ϣ  4���¼���Ʒ  5���鿴��ʷ����  6�� ����    7�������û�������" << endl;
			cout << "----------------------------------------------------------------------------------------------------------------------------" << endl;
			cout << "��������Ҫ���еĲ�������ţ�";
			cin >> m;
			while (cin.fail())
			{
				cout << "�밴Ҫ��������Ҫ���еĲ�������ţ�" << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "�����룺 ";
				cin >> m;
			}
			cin.ignore();
			if (7 == m)
				break;
			else
			{
				switch (m)
				{
				case 1:
				{
					_LanchGoods();
					break;
				}
				case 2:
				{
					_CheckGoods("seller");
					break;
				}
				case 3:
				{
					_ChangeGoodsInf();
					break;
				}
				case 4:
				{
					_RemoveGoods("seller");
					break;
				}
				case 5:
				{
					_CheckOrders("seller");
					break;
				}
				case 6:
				{
					_Send();
					break;
				}
				default:cout << "************************   �밴Ҫ�����룡   ************************" << endl<<endl;
				}
			}
		}
		break;
	}
	case 4:
	{
		int q;
		while (true)
		{
			cout << endl;
			cout << "-------------------------------------------------------------------------------------------------------------" << endl;
			cout << "            1�������û�������       2���޸���Ϣ          3���鿴��Ϣ          4����ֵ" << endl;
			cout << "-------------------------------------------------------------------------------------------------------------" << endl;
			cout << "��������Ҫ���еĲ��������:";
			cin >> q;
			while (cin.fail())
			{
				cout << "�밴Ҫ��������Ҫ���еĲ�������ţ�" << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "�����룺 ";
				cin >> q;
			}
			if (1 == q)
				break;
			else
			{
				switch (q)
				{
				case 2:
				{
					_ChangeUserInf();
					break;
				}
				case 3:
				{
					_CheckUserInf();
					break;
				}
				case 4:
				{
					_Recharge();
					break;
				}
				default: cout << "*********************   �밴Ҫ������!   **************************" << endl << endl;
				}
			}
		}
		break;
	}
	case 5:
	{
		_Report();
		break;
	}
	case 6:
	{
		_CheckReportedInf();
		break;
	}
	default:cout << "*************************   �밴Ҫ�����룡   ************************" << endl << endl;
	}
}

void _Send()
{
	cout << "�������ѷ�����Ʒ�Ķ���ID��";
	string ord_id;
	getline(cin, ord_id);
	auto it = orders.find(ord_id);
	if (it != orders.end())
	{
		if (it->second.ord_condition == "������")
		{
			it->second.ord_condition = "���ջ�";
			_DateFile("orders.txt", "orders");
			cout << endl;
			cout << "******************************************************" << endl;
			cout << "�����ɹ�!" << endl;
			cout << "******************************************************" << endl << endl;
		}
		else
		{
			cout << endl;
			cout << "******************************************************" << endl;
			cout << "��Ʒ�ѷ�����" << endl;
			cout << "******************************************************" << endl<<endl;
		}
	}
	else
	{
		cout << endl;
		cout << "******************************************************" << endl;
		cout << "���������ڣ�" << endl;
		cout << "******************************************************" << endl<<endl;

	}
}

void _Report()
{
	bool has_reported = false;
	cout << "��������Ҫ�ٱ����û�ID: ";
	string reported_id;
	cin.ignore();
	getline(cin, reported_id);
	auto users_it = users.find(reported_id);
	if (users_it!= users.end() && users_it->second.exist)
	{
		if (reported_id != cur_id)
		{
			if (!users_it->second.on_punishment)
			{
				
				auto it1 = reported_users.find(reported_id);
				if (it1 != reported_users.end())
				{
					auto it2 = it1->second.reported_reason.find(cur_id);
					if (it2 != it1->second.reported_reason.end())
					{
						has_reported = true;
					}
				}
				if (it1 != reported_users.end())
				{
					if (!has_reported)
					{

						cout << "������ٱ�ԭ�� " << endl;
						getline(cin, it1->second.reported_reason[cur_id]);
						for (auto iter = it1->second.reported_reason[cur_id].begin(); iter != it1->second.reported_reason[cur_id].end(); ++iter)
						{
							if (*iter == ' ')
								*iter = '|';
						}
						++it1->second.num;
						++it1->second.m;
						if (it1->second.m >= 3)
						{
							_Punish(reported_id);
						}
						_DateFile("reported_users.txt", "reported");
					}
					else if (has_reported)
					{
						auto it2 = it1->second.reported_reason.find(cur_id);
						cout << "������ٱ�ԭ�� " << endl;
						string s;
						cin.ignore();
						getline(cin, s);
						for (auto iter = s.begin(); iter != s.end(); ++iter)
						{
							if (*iter == ' ')
								*iter = '|';
						}
						it2->second.append('$' + s);
						++it1->second.num;
						++it1->second.m;
						if (it1->second.m >= 3)
						{
							_Punish(reported_id);
						}
						_DateFile("reported_users.txt", "reported");
					}
				}
				else
				{
					cout << "������ٱ�ԭ�� " << endl;
					getline(cin, report.reported_reason[cur_id]);
					for (auto iter = report.reported_reason[cur_id].begin(); iter != report.reported_reason[cur_id].end(); ++iter)
					{
						if (*iter == ' ')
							*iter = '|';
					}
					++report.num;
					++report.m;
					reported_users[reported_id] = report;
					if (report.m >= 3)
					{
						_Punish(reported_id);
					}
					_DateFile("reported_users.txt", "reported");
				}
			}
			else
			{
				cout << endl;
				cout << "***************************************************************************************" << endl;
				cout << "���û����ڱ��ٱ��������࣬�����ܴ����У����ܴ����ڼ䲻�ܱ��ٱ���" << endl;
				cout << "***************************************************************************************" << endl << endl;
			}
		}
		else
		{
			cout << "******************************************************************" << endl;
			cout << "�Ƿ����룬 �����ܾٱ��Լ���" << endl;
			cout << "******************************************************************" << endl;
		}
	}
	else
	{
		cout << "******************************************************************" << endl;
		cout << "δ�ҵ����û���" << endl;
		cout << "******************************************************************" << endl;
		
	}
}


void _Punish(const string reported_id)
{
	string year, mon, day;
	auto iter = reported_users.find(reported_id);
	time_t now = time(0);
	tm* ltm = localtime(&now);
	_Helper(ltm->tm_year + 1900, year);
	_Helper(ltm->tm_mon + 1, mon);
	_Helper(ltm->tm_mday, day);
	report.start_time = year + '-' + mon + '-' + day;
	int y, m, d;
	d = ltm->tm_mday + iter->second.num;
	m = ltm->tm_mon + 1;
	y = ltm->tm_year + 1900;
	switch (ltm->tm_mon)
	{
	case 1:case3:case 5:case 7:case 9:case 10:case 11:case 12:
		if (d > 31)
		{
			d -= 31;
			m += 1;
			if (m > 12)
			{
				m -= 12;
				y += 1;
			}
		}
		break;
	case 2:
		if ((ltm->tm_year + 1900) % 4 == 0)
		{
			if (d > 29)
			{
				d -= 29;
				m += 1;
				if (m > 12)
				{
					m -= 12;
					y += 1;
				}
			}
		}
		else
		{
			if (d > 28)
			{
				d -= 28;
				m += 1;
				if (m > 12)
				{
					m -= 12;
					y += 1;
				}
			}
		}
		break;
	case 4:case 6:case 8:
		if (d > 31)
		{
			d -= 30;
			m += 1;
			if (m > 12)
			{
				m -= 12;
				y += 1;
			}
		}
		break;

	}
	_Helper(y, year);
	_Helper(m, mon);
	_Helper(d, day);
	report.end_time = year + '-' + mon + '-' + day;
	iter->second.on_punishment = true;
	report.m = 0;
	iter->second.start_time = report.start_time;
	iter->second.end_time = report.end_time;
	iter->second.m = 0;
	_DateFile("reported_users.txt", "reported");
}

void _Deblock()
{
	cout << "������Ҫ�ⶳ���û���ID��" << endl;
	string u_id;
	cin.ignore();
	getline(cin, u_id);
	auto it = reported_users.find(u_id);
	if (it != reported_users.end())
	{
		if (it->second.on_punishment)
		{
			it->second.on_punishment = false;
			it->second.start_time = "0";
			it->second.end_time = "0";
			_DateFile("reported_users.txt", "reported");
			cout << "**************************************************" << endl;
			cout << "�ⶳ�ɹ���" << endl;
			cout << "**************************************************" << endl << endl;

		}
		else
		{
			cout << "**************************************************" << endl;
			cout << "���û����ڶ����û��У�" << endl;
			cout << "**************************************************" << endl << endl;
		}
	}
	else
	{
		cout << "**************************************************" << endl;
		cout << "���û����ڶ����û��У�" << endl;
		cout << "**************************************************" << endl<<endl;
	}
}