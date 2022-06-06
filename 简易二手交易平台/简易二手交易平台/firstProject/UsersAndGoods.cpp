#include <iostream>
#include <sstream>
#include <ctime>
#include <string>
using namespace std;
#include "map.h"
#include "Creat.h"
#include"File.h"
extern void _Recharge();
extern string cur_id;
extern string _GetTime();
void _Buy()
{
	cout << "请输入您要购买的商品ID： ";
	string goods_id;
	cin >> goods_id;
	cin.ignore();
	auto it = all_goods.find(goods_id);
	if (it == all_goods.end() || it->second.condition != "销售中")
	{
		cout << endl;
		cout << "*****************************************************************" << endl;
		cout << "没有找到该商品（该商品ID不存在或商品已下架或商品已售出）！" << endl;
		cout << "*****************************************************************" << endl << endl;

	}
	else if (it->second.seller == cur_id)
	{
		cout << endl;
		cout << "*****************************************************************" << endl;
		cout << "您不能购买自己的商品！" << endl;
		cout << "*****************************************************************" << endl<<endl;
	}
	else if (it->second.condition == "销售中")
	{
		struct Order ord;
		auto buyer_it = users.find(cur_id);
		int m;
		cout << "请输入您要购买的商品数量： ";
		cin >> m;
		while (cin.fail())
		{
			cout << "输入不合法！请重新输入！" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "请输入： ";
			cin >> m;
		}
		cin.ignore();
		if (m <= it->second.amount)
		{
			int flag = 1;
			while (flag == 1)
			{
				if (buyer_it->second.balance >= it->second.price * m)
				{
					flag = 2;
					buyer_it->second.balance -= it->second.price * m;
					auto seller_it = users.find(it->second.seller);
					seller_it->second.balance += it->second.price;
					it->second.amount -= m;
					if (it->second.amount == 0)
						it->second.condition = "已售出";
					_ForCreat('T', count_orders);
					++count_orders;
					ord.buyer = buyer_it->first;
					ord.goods_id = goods_id;
					ord.money = it->second.price * m;
					ord.seller = seller_it->first;
					ord.time_dealed = _GetTime();
					ord.amount = m;
					orders[id] = ord;
					_DateFile("orders.txt", "orders");
					_DateFile("users.txt", "users");
					_DateFile("goods.txt", "all_goods");
					cout << endl;
					cout << "*****************************************************************" << endl;
					cout << "交易提醒！" << endl;
					cout << "交易时间：  ";
					cout << ord.time_dealed << endl;
					cout << "商品数量：  ";
					cout << m << endl;
					cout << "交易金额：  ";
					cout << ord.money << "元" << endl;
					cout << "交易状态：  ";
					cout << "交易成功" << endl;
					cout << "余额： ";
					cout << buyer_it->second.balance << endl;
					cout << "*****************************************************************" << endl << endl;
				}
				else
				{
					cout << endl;
					cout << "*****************************************************************" << endl;
					cout << "余额不足，购买失败！" << endl;
					cout << "*****************************************************************" << endl << endl;
					cout << "请选择：1、充值，继续购买   2、取消购买" << endl;
					cout << "请输入：";
					cin >> flag;
					while (cin.fail())
					{
						cout << "请按要求输入您要进行的操作的序号！" << endl;
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "请输入： ";
						cin >> flag;
					}
					cin.ignore();
					if (flag != 1 && flag != 2)
					{
						cout << endl;
						cout << "*****************************************************************" << endl;
						cout << "输入不合法！即将退出购买！" << endl;
						cout << "*****************************************************************" << endl<<endl;
						break;
					}
					if (flag == 1)
						_Recharge();

				}
			}
		}
		else
		{
			cout << endl;
			cout << "*****************************************************************" << endl;
			cout << "在售商品数量不够，购买失败！" << endl;
			cout << "*****************************************************************" << endl<<endl;
		}
	}
}

void _ChangeUserInf()
{
	int m;
	int is_existed = 0;
	string content;
	cout << "请选择需要修改的属性序号（1、用户名  2、联系方式   3、地址）：  ";
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
	auto cur_it = users.find(cur_id);
	switch(m)
	{
	case 1:
	{
		cout << "请输入修改后的用户名(用户名不能含有空格)：";
		getline(cin, content);
		for (auto it = content.begin(); it != content.end(); ++it)
		{
			if(*it == ' ')
			{
				cout << "用户名不能含有空格，请重新输入！" << endl;
				getline(cin, content);
				it = content.begin();
			}
		}
		cout << endl;
		cout << "*****************************************************************" << endl;
		for (auto it = users.begin(); it != users.end(); ++it)
		{
			if (it->first != cur_id && it->second.exist && it->second.name == content)
			{
				is_existed = 1;
				cout << "用户名已存在，修改失败!"<<endl;
			}
		}
		if (!is_existed)
		{
			cur_it->second.name = content;
			cout << "修改成功！" << endl;
			cout << "当前用户名为： ";
			cout << content << endl;
		}
		cout << "*****************************************************************" << endl << endl;
		break;
	}
	case 2:
	{
		cout << "请输入修改后的联系方式：" ;
		getline(cin, content);
		for (auto it = content.begin(); it != content.end(); ++it)
		{
			if (*it == ' ')
				cin.get();
		}
		cout << endl;
		cout << "*****************************************************************" << endl;
		cur_it->second.tel = content;
		cout << "修改成功！" << endl;
		cout << "当前联系方式为： ";
		cout << content << endl;
		cout << "*****************************************************************" << endl<<endl;

		break;
	}
	case 3:
	{
		cout << "请输入修改后的地址：";
		getline(cin, content);
		for (auto it = content.begin(); it != content.end(); ++it)
		{
			if (*it == ' ')
				cin.get();
		}
		cur_it->second.adr = content;
		cout << endl;
		cout << "*****************************************************************" << endl;
		cout << "修改成功！" << endl;
		cout << "当前地址为： ";
		cout << content << endl;
		cout << "*****************************************************************" << endl<<endl;
		break;
	}
	default:
		cout << endl;
		cout << "*****************************************************************" << endl;
		cout << "没有该属性，修改失败！" << endl;
		cout << "*****************************************************************" << endl<<endl;
	}
	cout << endl;
	if(!is_existed)
		_DateFile("users.txt", "users");
}

void _DeleteUser()
{
	string user_id;
	char ch;
	cout << "请输入要删除用户的ID: ";
	getline(cin, user_id);
	auto it = users.find(user_id);
	if (it != users.end() && it->second.exist)
	{
		cout << "确认要删除该用户吗？" << endl;
		cout << endl << endl;
		cout << "*****************************************************************" << endl;
		cout << "用户ID:    " << it->first << endl;
		cout << "用户名：   " << it->second.name << endl;
		cout << "联系方式： " << it->second.tel << endl;
		cout << "*****************************************************************" << endl;
		cout << endl << endl;
		cout << "请选择 （y/n）:";
		cin >> ch;
		if ('y' == ch)
		{
			it->second.exist = false;
			for (auto goods_it = all_goods.begin(); goods_it != all_goods.end(); ++goods_it)
			{
				if (goods_it->second.seller == user_id && goods_it->second.condition == "销售中")
					goods_it->second.condition = "已下架";
			}
			_DateFile("users.txt", "users");
			_DateFile("goods.txt", "all_goods");
			cout << endl;
			cout << "**************   成功删除用户！   ****************" << endl<<endl;
		}
		else if ('n' == ch)
		{
			cout << "*****************   您已取消删除，删除失败！   ******************" << endl<<endl;
		}
		else
			cout << "*****************   删除失败，请按要求输入！   ******************" << endl<<endl;
	}
	else
		cout << "*********************   用户不存在，删除失败！   *************************" << endl<<endl;
	
}

void _Recharge()
{
	int amount;
	while (true)
	{
		cout << "请输入充值金额：";
		cin >> amount;
		if (amount > 0)
		{
			auto it = users.find(cur_id);
			it->second.balance += amount;
			cout << endl;
			cout << "************************************" << endl;
			cout << "充值成功！" << endl;
			cout << "当前余额为:  " << it->second.balance << endl;
			cout << "************************************" << endl << endl;
			break;
		}
		else
		{
			cout << endl;
			cout << "***************************************************************" << endl;
			cout << "充值失败，充值金额需大于0！" << endl;
			cout << "***************************************************************" << endl;
			cout << endl;
		}
	}
}


void _RemoveGoods(const string& identity)
{
	string goods_id;
	char ch;
	cout << "请输入需要下架的商品ID：";
	getline(cin, goods_id);
	auto it = all_goods.find(goods_id);
	if (it != all_goods.end())
	{
		if (identity == "seller" )
		{
			if (it->second.seller == cur_id)
			{
				cout << "你确认要下架该商品吗？";
				cout << endl << endl;
				cout << "*****************************************************************" << endl;
				cout << "商品ID：   " << goods_id << endl;
				cout << "商品名称： " << it->second.name << endl;
				cout << "商品金额： " << it->second.price << endl;
				cout << "商品描述： " << it->second.description << endl;
				cout << "*****************************************************************" << endl;
				cout << endl << endl;
				cout << "请选择（y/n):";
				cin >> ch;
				if (ch == 'y')
				{
					if (it->second.condition == "销售中")
					{
						it->second.condition = "已下架";
						_DateFile("goods.txt", "all_goods");
						cout << "*****************   下架成功！   ****************" << endl;
					}
					else if (it->second.condition == "已售出")
						cout << "商品已售出，下架失败！" << endl;
					else if (it->second.condition == "已下架")
						cout << "商品早已下架！" << endl;
				}
				else if (ch == 'n')
					cout << "****************   您已取消下架商品，下架失败！   *****************" << endl;
			}
			else
				cout << "****************   您没有发布该商品，下架失败！   *******************" << endl;
		}
		else if (identity == "adm")
		{
			cout << "你确认要下架该商品吗？";
			cout << endl << endl;
			cout << "*****************************************************************" << endl;
			cout << "商品ID：   " << goods_id << endl;
			cout << "商品名称： " << it->second.name << endl;
			cout << "商品金额： " << it->second.price << endl;
			cout << "商品描述： " << it->second.description << endl;
			cout << "*****************************************************************" << endl;
			cout << endl << endl;
			cout << "请选择（y/n):";
			cin >> ch;
			if (ch == 'y')
			{
				if (it->second.condition == "销售中")
				{
					it->second.condition = "已下架";
					_DateFile("goods.txt", "all_goods");
					cout << "*****************   下架成功！   ****************" << endl;
				}
				else if (it->second.condition == "已售出")
					cout << "商品已售出，下架失败！" << endl;
				else if (it->second.condition == "已下架")
					cout << "商品早已下架！" << endl;
			}
			else if (ch == 'n')
				cout << "****************   您已取消下架商品，下架失败！   *****************" << endl;
		}
	}
	else
		cout << "********************   下架失败！没有找到该商品！   ***********************"<<endl;


}

void _LanchGoods()
{
	struct Goods goods;
	goods.seller = cur_id;
	goods.time_issued = _GetTime();
	goods.num = 0;
	goods.goods_evaluation[1] = "无评价";
	cout << "请输入商品名称：  ";
	getline(cin, goods.name);
	for (auto iter = goods.name.begin(); iter != goods.name.end();)
	{
		if (*iter == ' ')
			iter = goods.name.erase(iter);
		else
			++iter;
	}
	cout << "请输入商品价格：  ";
	cin >> goods.price;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "请输入正确的商品价格： ";
		cin >> goods.price;
	}
	cin.ignore();
	cout << "请输入商品描述：  ";
	getline(cin, goods.description);
	for (auto iter = goods.description.begin(); iter != goods.description.end(); ++iter)
	{
		if (*iter == ' ')
			*iter = '|';
	}
	cout << "请输入您要发布的商品数量： ";
	cin >> goods.amount;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "请重新输入商品数量： ";
		cin >> goods.amount;
	}
	cin.ignore();
	cout << endl << endl<<"请确认发布的商品信息无误！"<<endl;
	cout << "*****************************************************************" << endl;
	cout << "商品名称：  " << goods.name << endl;
	cout << "商品价格：  " << goods.price << endl;
	cout << "商品描述：  " ;
	char c;
	for (auto it = goods.description.begin(); it != goods.description.end(); ++it)
	{
		if (*it == '|')
			c = ' ';
		else
			c = *it;
		cout << c;
	}
	cout<<endl;
	cout << "商品数量：  " << goods.amount << endl;
	cout << "*****************************************************************" << endl;
	cout << endl << endl<<"请确认是否发布 （y/n）:"<<endl;
	char ch;
	cin >> ch;
	cin.ignore();
	if ('y' == ch)
	{
		
		_ForCreat('M', count_goods);
		all_goods[id] = goods;
		++count_goods;
		_DateFile("goods.txt", "all_goods");
		cout << "************************   发布成功！   **********************" << endl;
	}
	else if ('n' == ch)
	{
		cout << "***********************   您已取消发布，发布失败！   *************************" << endl;
	}
	else
		cout << "***********************   发布失败!请按要求输入！   **************************" << endl;

}

void _ChangeGoodsInf()
{
	string goods_id;
	int m;
	char ch;
	cout << "请输入需修改的商品ID： ";
	getline(cin, goods_id);
	auto it = all_goods.find(goods_id);
	if (it != all_goods.end())
	{
		if (it->second.seller == cur_id)
		{

			cout << "请输入需修改的商品属性 （1、价格  2、描述）：";
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
			if (m != 1 && m != 2)
			{
				cout << "*****************************************************************" << endl;
				cout << "没有该属性，修改失败！" << endl;
				cout << "*****************************************************************" << endl;

			}
			else
			{
				if (1 == m)
				{
					int p;
					cout << "请输入修改后的商品价格： ";
					cin >> p;
					while (cin.fail())
					{
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "请输入正确的商品价格： ";
						cin >> p;
					}
					cin.ignore();
					it->second.price = p;
					cout << endl << endl;
					cout << "*****************************************************************" << endl;
					cout << "修改后的商品价格为：" << it->second.price << endl;
					cout << "*****************************************************************" << endl;

				}
				else if (2 == m)
				{
					string str;
					cout << "请输入商品描述：";
					cin >> str;
					cin.ignore();
					for (auto str_it = str.begin(); str_it != str.end(); ++str_it)
					{
						if (*str_it == ' ')
							*str_it = '|';
					}
					it->second.description = str;
					cout << "*****************************************************************" << endl;
					cout << "修改后的商品描述为： " ;
					for (auto str_it = str.begin(); str_it != str.end(); ++str_it)
					{
						if (*str_it == '|')
							*str_it = ' ';
						cout << *str_it;
					}
					cout << endl;
					cout << "*****************************************************************" << endl;
				}
				cout << "请确认是否修改 （y/n）:";
				cin >> ch;
				cin.ignore();
				if ('y' == ch)
				{
					_DateFile("goods.txt", "all_goods");
					cout << "**************************   修改成功   *************************" << endl << endl;
				}

				else if ('n' == ch)
					cout << "***********************   已取消修改，修改失败！   *************************" << endl;
				else
					cout << "***********************   修改失败，请按要求输入！   ***********************" << endl;
			}
		}
		else
			cout << "**************************   您没有发布该商品，修改失败！   *******************************" << endl << endl;
	}
	else
	{
		cout << "*****************************************************************" << endl;
		cout << "没有找到该商品！" << endl;
		cout << "*****************************************************************" << endl;
	}

}

void _Helper(int i, string &str)
{
	stringstream ss;
	ss << i;
	ss >> str;
}
string _GetTime()
{
	string cur_time, year, mon, day;
	time_t now = time(0);
	tm* ltm = localtime(&now);
	_Helper(ltm->tm_year + 1900, year);
	_Helper(ltm->tm_mon + 1, mon);
	_Helper(ltm->tm_mday, day);
	cur_time = year + '-' + mon + '-' + day;
	return cur_time;
}