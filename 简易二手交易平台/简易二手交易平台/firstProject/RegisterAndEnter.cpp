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
		cout << "请输入用户名（注意：不要输入空格！）：";
		getline(cin, name);
		for (auto it = name.begin(); it != name.end();)
		{
			if (*it == ' ')
			{
				cout << "请不要输入空格，请重新输入： ";
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
					cout << "用户名已存在, 无法注册！ 请选择（1、继续注册  2、取消注册）"<<endl;
					cout << "请输入：";
					cin >> flag;
					while (cin.fail())
					{
						cout << "请按要求输入您要进行的操作的序号！" << endl;
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "请输入：";
						cin >> flag;
					}
					cin.ignore();
					if (flag != 1 && flag != 2)
					{
						cout <<endl<< "输入不合法，即将退出注册！" << endl;
						flag = 2;
					}
				}
			}
		}
		if (!is_existed)
		{
			cout << "请输入密码（不超过20个字符，仅允许输入英文字符和数字）：";
			getline(cin, pass);
			for (auto it = pass.begin(); it != pass.end(); )
			{
				if (*it == ' ')
				{
					cout << "请不要输入空格，请重新输入： ";
					getline(cin, pass);
					it = pass.begin();
				}
				else
					++it;
			}
			struct User u;
			u.name = name;
			u.password = pass;
			cout << "请输入联系方式：";
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
			cout << "请输入地址：";
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
			u.buyer_eval[1] = "您未收到任何评价！";
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
	cout << "请输入用户名：";
	cin.ignore();
	getline(cin, name);
	cout << "请输入密码：";
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
				cout << "***************************   登录成功，欢迎来到用户界面!   ***************************" << endl << endl;
				while (true)
				{
					cout << endl << endl;
					cout << "-------------------------------------------------------------------------------------------------------------" << endl;
					cout << "   1、注销登录	    2、我是买家       3、我是卖家       4、个人信息管理    5、举报用户    6、查看举报信息" << endl;
					cout << "-------------------------------------------------------------------------------------------------------------" << endl;
					int i;
					cout << "请输入您要进行的操作的选项： ";
					cin >> i;
					while (cin.fail())
					{
						cout << "请按要求输入您要进行的操作的序号！" << endl;
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "请输入： ";
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
				cout << "********************   密码错误，登录失败!   ********************" << endl << endl;
			}
		}
		else
		{
			
			cout << "*****************************************************************************" << endl;
			cout << "由于举报次数超限， 您的账号被暂时冻结！" << endl;
			cout << "解封日期为："<<it1->second.end_time<<endl;
			cout << "*****************************************************************************" << endl<<endl;
		}
	}
	else
		cout << "********************   用户不存在，请先注册！   ********************" << endl<<endl;
	
}

void _AdmEnter()
{
	cout << "请输入用户名：";
	cin >> name;
	cout << "请输入密码：";
	cin >> pass;
	auto it = adm.begin();
	if (name == it->first)
	{
		if (pass == it->second)
		{
			cout << "***************************   登录成功，欢迎来到管理员界面!   ***************************" << endl << endl;
			int m;
			while (true)
			{
				cout << endl;
				cout << "------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
				cout << "         1、查看所有商品  2、搜索商品  3、查看所有订单  4、查看所有用户  5、删除用户  6、下架商品 7、查看举报信息 8、解冻用户账户  9、注销" << endl;
				cout << "------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
				cout << "请输入您要进行的操作的序号：";
				cin >> m;
				while (cin.fail())
				{
					cout << "请按要求输入您要进行的操作的序号！" << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "请输入： ";
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
				default: cout << "输入不合法，请重新输入！" << endl << endl;
				}

			}

		}
		else
			cout << "用户名或密码输入不正确，登陆失败！" << endl<<endl;
	}
	else
		cout << "用户名或密码输入不正确，登陆失败！" << endl<<endl;

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
			cout << "  1、查看商品列表  2、购买商品  3、搜索商品  4、查看历史订单  5、查看商品详细信息  6、返回用户主界面" << endl;
			cout << "--------------------------------------------------------------------------------------------------------" << endl;
			cout << "请输入您要进行的操作的序号：";
			cin >> n;
			while (cin.fail())
			{
				cout << "请按要求输入您要进行的操作的序号！" << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "请输入： ";
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
			default:cout << "***********************   请按要求输入！   ***********************" << endl << endl;
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
			cout << "      1、发布商品  2、查看发布商品  3、修改商品信息  4、下架商品  5、查看历史订单  6、 发货    7、返回用户主界面" << endl;
			cout << "----------------------------------------------------------------------------------------------------------------------------" << endl;
			cout << "请输入您要进行的操作的序号：";
			cin >> m;
			while (cin.fail())
			{
				cout << "请按要求输入您要进行的操作的序号！" << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "请输入： ";
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
				default:cout << "************************   请按要求输入！   ************************" << endl<<endl;
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
			cout << "            1、返回用户主界面       2、修改信息          3、查看信息          4、充值" << endl;
			cout << "-------------------------------------------------------------------------------------------------------------" << endl;
			cout << "请输入您要进行的操作的序号:";
			cin >> q;
			while (cin.fail())
			{
				cout << "请按要求输入您要进行的操作的序号！" << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "请输入： ";
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
				default: cout << "*********************   请按要求输入!   **************************" << endl << endl;
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
	default:cout << "*************************   请按要求输入！   ************************" << endl << endl;
	}
}

void _Send()
{
	cout << "请输入已发货商品的订单ID：";
	string ord_id;
	getline(cin, ord_id);
	auto it = orders.find(ord_id);
	if (it != orders.end())
	{
		if (it->second.ord_condition == "待发货")
		{
			it->second.ord_condition = "待收货";
			_DateFile("orders.txt", "orders");
			cout << endl;
			cout << "******************************************************" << endl;
			cout << "发货成功!" << endl;
			cout << "******************************************************" << endl << endl;
		}
		else
		{
			cout << endl;
			cout << "******************************************************" << endl;
			cout << "商品已发货！" << endl;
			cout << "******************************************************" << endl<<endl;
		}
	}
	else
	{
		cout << endl;
		cout << "******************************************************" << endl;
		cout << "订单不存在！" << endl;
		cout << "******************************************************" << endl<<endl;

	}
}

void _Report()
{
	bool has_reported = false;
	cout << "请输入您要举报的用户ID: ";
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

						cout << "请输入举报原因： " << endl;
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
						cout << "请输入举报原因： " << endl;
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
					cout << "请输入举报原因： " << endl;
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
				cout << "该用户由于被举报次数过多，正接受处罚中！接受处罚期间不能被举报！" << endl;
				cout << "***************************************************************************************" << endl << endl;
			}
		}
		else
		{
			cout << "******************************************************************" << endl;
			cout << "非法输入， 您不能举报自己！" << endl;
			cout << "******************************************************************" << endl;
		}
	}
	else
	{
		cout << "******************************************************************" << endl;
		cout << "未找到该用户！" << endl;
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
	cout << "请输入要解冻的用户的ID：" << endl;
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
			cout << "解冻成功！" << endl;
			cout << "**************************************************" << endl << endl;

		}
		else
		{
			cout << "**************************************************" << endl;
			cout << "该用户不在冻结用户中！" << endl;
			cout << "**************************************************" << endl << endl;
		}
	}
	else
	{
		cout << "**************************************************" << endl;
		cout << "该用户不在冻结用户中！" << endl;
		cout << "**************************************************" << endl<<endl;
	}
}