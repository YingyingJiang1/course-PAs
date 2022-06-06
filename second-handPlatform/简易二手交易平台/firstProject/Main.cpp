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
	count_users = users.size();                                                 //����Ա�˺ţ�pity           ���룺abc6666
	count_goods = all_goods.size();
	count_orders = orders.size();
	_Entry();
	return 0;
	
}

void _Entry()
{
	while (true)
	{
		cout << "***********************************************  ��ӭ��������  **********************************************" << endl;
		cout << endl<<endl;
		cout << "-------------------------------------------------------------------------------------------------------------" << endl;
		cout << "                     1���û�ע��      2���û���¼      3������Ա��¼      4���˳�����" << endl;
		cout << "-------------------------------------------------------------------------------------------------------------" << endl;
		cout << endl;
		cout << "����������Ҫ���еĲ�������ţ�";
		int i;
		cin >> i;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "�밴Ҫ��������Ҫ���еĲ�����ѡ� ";
			cin >> i;
		}
		if (4 == i)
		{
			users.clear();
			all_goods.clear();
			orders.clear();
			cout << endl;
			cout << "�˳��ɹ���";
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
		default:cout << "�밴Ҫ�����룡"<<endl<<endl;
		}
	}
}