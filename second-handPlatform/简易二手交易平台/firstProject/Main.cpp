#include <iostream>
using namespace std;
#include <map>
#include "map.h"
#include "File.h"
#include "RegisterAndEnter.h"
extern void _Entry();
std::map<std::string, struct User>users;
std::map<std::string, struct Goods>all_goods;
std::map<std::string, struct Order>orders;
std::map<std::string, std::string>adm;
std::map<std::string, struct Report>reported_users;
int count_users;
int count_goods;
int count_orders;

int main()
{
	adm["pity"] = "abc6666";
	_ReadFile("users.txt", "users");
	_ReadFile("goods.txt", "all_goods");
	_ReadFile("orders.txt", "orders");
	_ReadFile("Reported_users.txt", "reported");
	count_users = users.size();                                                 //管理员账号：pity           密码：abc6666
	count_goods = all_goods.size();
	count_orders = orders.size();
	_Entry();
	return 0;
	
}

void _Entry()
{
	while (true)
	{
		cout << "***********************************************  欢迎进入咸鱼  **********************************************" << endl;
		cout << endl<<endl;
		cout << "-------------------------------------------------------------------------------------------------------------" << endl;
		cout << "                     1、用户注册      2、用户登录      3、管理员登录      4、退出程序" << endl;
		cout << "-------------------------------------------------------------------------------------------------------------" << endl;
		cout << endl;
		cout << "请输入您想要进行的操作的序号：";
		int i;
		cin >> i;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "请按要求输入您要进行的操作的选项： ";
			cin >> i;
		}
		if (4 == i)
		{
			users.clear();
			all_goods.clear();
			orders.clear();
			cout << endl;
			cout << "退出成功！";
			break;
		}
		switch (i)
		{
		case 1:
		{
			_Register();
			break;
		}
		case 2:
		{
			_UserEnter();
			break;
		}
		case 3:
		{
			_AdmEnter();
			break;
		}
		default:cout << "请按要求输入！"<<endl<<endl;
		}
	}
}