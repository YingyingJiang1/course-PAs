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
	cout << "��������Ҫ�������ƷID�� ";
	string goods_id;
	cin >> goods_id;
	cin.ignore();
	auto it = all_goods.find(goods_id);
	if (it == all_goods.end() || it->second.condition != "������")
	{
		cout << endl;
		cout << "*****************************************************************" << endl;
		cout << "û���ҵ�����Ʒ������ƷID�����ڻ���Ʒ���¼ܻ���Ʒ���۳�����" << endl;
		cout << "*****************************************************************" << endl << endl;

	}
	else if (it->second.seller == cur_id)
	{
		cout << endl;
		cout << "*****************************************************************" << endl;
		cout << "�����ܹ����Լ�����Ʒ��" << endl;
		cout << "*****************************************************************" << endl<<endl;
	}
	else if (it->second.condition == "������")
	{
		struct Order ord;
		auto buyer_it = users.find(cur_id);
		int m;
		cout << "��������Ҫ�������Ʒ������ ";
		cin >> m;
		while (cin.fail())
		{
			cout << "���벻�Ϸ������������룡" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "�����룺 ";
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
						it->second.condition = "���۳�";
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
					cout << "�������ѣ�" << endl;
					cout << "����ʱ�䣺  ";
					cout << ord.time_dealed << endl;
					cout << "��Ʒ������  ";
					cout << m << endl;
					cout << "���׽�  ";
					cout << ord.money << "Ԫ" << endl;
					cout << "����״̬��  ";
					cout << "���׳ɹ�" << endl;
					cout << "�� ";
					cout << buyer_it->second.balance << endl;
					cout << "*****************************************************************" << endl << endl;
				}
				else
				{
					cout << endl;
					cout << "*****************************************************************" << endl;
					cout << "���㣬����ʧ�ܣ�" << endl;
					cout << "*****************************************************************" << endl << endl;
					cout << "��ѡ��1����ֵ����������   2��ȡ������" << endl;
					cout << "�����룺";
					cin >> flag;
					while (cin.fail())
					{
						cout << "�밴Ҫ��������Ҫ���еĲ�������ţ�" << endl;
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "�����룺 ";
						cin >> flag;
					}
					cin.ignore();
					if (flag != 1 && flag != 2)
					{
						cout << endl;
						cout << "*****************************************************************" << endl;
						cout << "���벻�Ϸ��������˳�����" << endl;
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
			cout << "������Ʒ��������������ʧ�ܣ�" << endl;
			cout << "*****************************************************************" << endl<<endl;
		}
	}
}

void _ChangeUserInf()
{
	int m;
	int is_existed = 0;
	string content;
	cout << "��ѡ����Ҫ�޸ĵ�������ţ�1���û���  2����ϵ��ʽ   3����ַ����  ";
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
	auto cur_it = users.find(cur_id);
	switch(m)
	{
	case 1:
	{
		cout << "�������޸ĺ���û���(�û������ܺ��пո�)��";
		getline(cin, content);
		for (auto it = content.begin(); it != content.end(); ++it)
		{
			if(*it == ' ')
			{
				cout << "�û������ܺ��пո����������룡" << endl;
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
				cout << "�û����Ѵ��ڣ��޸�ʧ��!"<<endl;
			}
		}
		if (!is_existed)
		{
			cur_it->second.name = content;
			cout << "�޸ĳɹ���" << endl;
			cout << "��ǰ�û���Ϊ�� ";
			cout << content << endl;
		}
		cout << "*****************************************************************" << endl << endl;
		break;
	}
	case 2:
	{
		cout << "�������޸ĺ����ϵ��ʽ��" ;
		getline(cin, content);
		for (auto it = content.begin(); it != content.end(); ++it)
		{
			if (*it == ' ')
				cin.get();
		}
		cout << endl;
		cout << "*****************************************************************" << endl;
		cur_it->second.tel = content;
		cout << "�޸ĳɹ���" << endl;
		cout << "��ǰ��ϵ��ʽΪ�� ";
		cout << content << endl;
		cout << "*****************************************************************" << endl<<endl;

		break;
	}
	case 3:
	{
		cout << "�������޸ĺ�ĵ�ַ��";
		getline(cin, content);
		for (auto it = content.begin(); it != content.end(); ++it)
		{
			if (*it == ' ')
				cin.get();
		}
		cur_it->second.adr = content;
		cout << endl;
		cout << "*****************************************************************" << endl;
		cout << "�޸ĳɹ���" << endl;
		cout << "��ǰ��ַΪ�� ";
		cout << content << endl;
		cout << "*****************************************************************" << endl<<endl;
		break;
	}
	default:
		cout << endl;
		cout << "*****************************************************************" << endl;
		cout << "û�и����ԣ��޸�ʧ�ܣ�" << endl;
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
	cout << "������Ҫɾ���û���ID: ";
	getline(cin, user_id);
	auto it = users.find(user_id);
	if (it != users.end() && it->second.exist)
	{
		cout << "ȷ��Ҫɾ�����û���" << endl;
		cout << endl << endl;
		cout << "*****************************************************************" << endl;
		cout << "�û�ID:    " << it->first << endl;
		cout << "�û�����   " << it->second.name << endl;
		cout << "��ϵ��ʽ�� " << it->second.tel << endl;
		cout << "*****************************************************************" << endl;
		cout << endl << endl;
		cout << "��ѡ�� ��y/n��:";
		cin >> ch;
		if ('y' == ch)
		{
			it->second.exist = false;
			for (auto goods_it = all_goods.begin(); goods_it != all_goods.end(); ++goods_it)
			{
				if (goods_it->second.seller == user_id && goods_it->second.condition == "������")
					goods_it->second.condition = "���¼�";
			}
			_DateFile("users.txt", "users");
			_DateFile("goods.txt", "all_goods");
			cout << endl;
			cout << "**************   �ɹ�ɾ���û���   ****************" << endl<<endl;
		}
		else if ('n' == ch)
		{
			cout << "*****************   ����ȡ��ɾ����ɾ��ʧ�ܣ�   ******************" << endl<<endl;
		}
		else
			cout << "*****************   ɾ��ʧ�ܣ��밴Ҫ�����룡   ******************" << endl<<endl;
	}
	else
		cout << "*********************   �û������ڣ�ɾ��ʧ�ܣ�   *************************" << endl<<endl;
	
}

void _Recharge()
{
	int amount;
	while (true)
	{
		cout << "�������ֵ��";
		cin >> amount;
		if (amount > 0)
		{
			auto it = users.find(cur_id);
			it->second.balance += amount;
			cout << endl;
			cout << "************************************" << endl;
			cout << "��ֵ�ɹ���" << endl;
			cout << "��ǰ���Ϊ:  " << it->second.balance << endl;
			cout << "************************************" << endl << endl;
			break;
		}
		else
		{
			cout << endl;
			cout << "***************************************************************" << endl;
			cout << "��ֵʧ�ܣ���ֵ��������0��" << endl;
			cout << "***************************************************************" << endl;
			cout << endl;
		}
	}
}


void _RemoveGoods(const string& identity)
{
	string goods_id;
	char ch;
	cout << "��������Ҫ�¼ܵ���ƷID��";
	getline(cin, goods_id);
	auto it = all_goods.find(goods_id);
	if (it != all_goods.end())
	{
		if (identity == "seller" )
		{
			if (it->second.seller == cur_id)
			{
				cout << "��ȷ��Ҫ�¼ܸ���Ʒ��";
				cout << endl << endl;
				cout << "*****************************************************************" << endl;
				cout << "��ƷID��   " << goods_id << endl;
				cout << "��Ʒ���ƣ� " << it->second.name << endl;
				cout << "��Ʒ�� " << it->second.price << endl;
				cout << "��Ʒ������ " << it->second.description << endl;
				cout << "*****************************************************************" << endl;
				cout << endl << endl;
				cout << "��ѡ��y/n):";
				cin >> ch;
				if (ch == 'y')
				{
					if (it->second.condition == "������")
					{
						it->second.condition = "���¼�";
						_DateFile("goods.txt", "all_goods");
						cout << "*****************   �¼ܳɹ���   ****************" << endl;
					}
					else if (it->second.condition == "���۳�")
						cout << "��Ʒ���۳����¼�ʧ�ܣ�" << endl;
					else if (it->second.condition == "���¼�")
						cout << "��Ʒ�����¼ܣ�" << endl;
				}
				else if (ch == 'n')
					cout << "****************   ����ȡ���¼���Ʒ���¼�ʧ�ܣ�   *****************" << endl;
			}
			else
				cout << "****************   ��û�з�������Ʒ���¼�ʧ�ܣ�   *******************" << endl;
		}
		else if (identity == "adm")
		{
			cout << "��ȷ��Ҫ�¼ܸ���Ʒ��";
			cout << endl << endl;
			cout << "*****************************************************************" << endl;
			cout << "��ƷID��   " << goods_id << endl;
			cout << "��Ʒ���ƣ� " << it->second.name << endl;
			cout << "��Ʒ�� " << it->second.price << endl;
			cout << "��Ʒ������ " << it->second.description << endl;
			cout << "*****************************************************************" << endl;
			cout << endl << endl;
			cout << "��ѡ��y/n):";
			cin >> ch;
			if (ch == 'y')
			{
				if (it->second.condition == "������")
				{
					it->second.condition = "���¼�";
					_DateFile("goods.txt", "all_goods");
					cout << "*****************   �¼ܳɹ���   ****************" << endl;
				}
				else if (it->second.condition == "���۳�")
					cout << "��Ʒ���۳����¼�ʧ�ܣ�" << endl;
				else if (it->second.condition == "���¼�")
					cout << "��Ʒ�����¼ܣ�" << endl;
			}
			else if (ch == 'n')
				cout << "****************   ����ȡ���¼���Ʒ���¼�ʧ�ܣ�   *****************" << endl;
		}
	}
	else
		cout << "********************   �¼�ʧ�ܣ�û���ҵ�����Ʒ��   ***********************"<<endl;


}

void _LanchGoods()
{
	struct Goods goods;
	goods.seller = cur_id;
	goods.time_issued = _GetTime();
	goods.num = 0;
	goods.goods_evaluation[1] = "������";
	cout << "��������Ʒ���ƣ�  ";
	getline(cin, goods.name);
	for (auto iter = goods.name.begin(); iter != goods.name.end();)
	{
		if (*iter == ' ')
			iter = goods.name.erase(iter);
		else
			++iter;
	}
	cout << "��������Ʒ�۸�  ";
	cin >> goods.price;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "��������ȷ����Ʒ�۸� ";
		cin >> goods.price;
	}
	cin.ignore();
	cout << "��������Ʒ������  ";
	getline(cin, goods.description);
	for (auto iter = goods.description.begin(); iter != goods.description.end(); ++iter)
	{
		if (*iter == ' ')
			*iter = '|';
	}
	cout << "��������Ҫ��������Ʒ������ ";
	cin >> goods.amount;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "������������Ʒ������ ";
		cin >> goods.amount;
	}
	cin.ignore();
	cout << endl << endl<<"��ȷ�Ϸ�������Ʒ��Ϣ����"<<endl;
	cout << "*****************************************************************" << endl;
	cout << "��Ʒ���ƣ�  " << goods.name << endl;
	cout << "��Ʒ�۸�  " << goods.price << endl;
	cout << "��Ʒ������  " ;
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
	cout << "��Ʒ������  " << goods.amount << endl;
	cout << "*****************************************************************" << endl;
	cout << endl << endl<<"��ȷ���Ƿ񷢲� ��y/n��:"<<endl;
	char ch;
	cin >> ch;
	cin.ignore();
	if ('y' == ch)
	{
		
		_ForCreat('M', count_goods);
		all_goods[id] = goods;
		++count_goods;
		_DateFile("goods.txt", "all_goods");
		cout << "************************   �����ɹ���   **********************" << endl;
	}
	else if ('n' == ch)
	{
		cout << "***********************   ����ȡ������������ʧ�ܣ�   *************************" << endl;
	}
	else
		cout << "***********************   ����ʧ��!�밴Ҫ�����룡   **************************" << endl;

}

void _ChangeGoodsInf()
{
	string goods_id;
	int m;
	char ch;
	cout << "���������޸ĵ���ƷID�� ";
	getline(cin, goods_id);
	auto it = all_goods.find(goods_id);
	if (it != all_goods.end())
	{
		if (it->second.seller == cur_id)
		{

			cout << "���������޸ĵ���Ʒ���� ��1���۸�  2����������";
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
			if (m != 1 && m != 2)
			{
				cout << "*****************************************************************" << endl;
				cout << "û�и����ԣ��޸�ʧ�ܣ�" << endl;
				cout << "*****************************************************************" << endl;

			}
			else
			{
				if (1 == m)
				{
					int p;
					cout << "�������޸ĺ����Ʒ�۸� ";
					cin >> p;
					while (cin.fail())
					{
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "��������ȷ����Ʒ�۸� ";
						cin >> p;
					}
					cin.ignore();
					it->second.price = p;
					cout << endl << endl;
					cout << "*****************************************************************" << endl;
					cout << "�޸ĺ����Ʒ�۸�Ϊ��" << it->second.price << endl;
					cout << "*****************************************************************" << endl;

				}
				else if (2 == m)
				{
					string str;
					cout << "��������Ʒ������";
					cin >> str;
					cin.ignore();
					for (auto str_it = str.begin(); str_it != str.end(); ++str_it)
					{
						if (*str_it == ' ')
							*str_it = '|';
					}
					it->second.description = str;
					cout << "*****************************************************************" << endl;
					cout << "�޸ĺ����Ʒ����Ϊ�� " ;
					for (auto str_it = str.begin(); str_it != str.end(); ++str_it)
					{
						if (*str_it == '|')
							*str_it = ' ';
						cout << *str_it;
					}
					cout << endl;
					cout << "*****************************************************************" << endl;
				}
				cout << "��ȷ���Ƿ��޸� ��y/n��:";
				cin >> ch;
				cin.ignore();
				if ('y' == ch)
				{
					_DateFile("goods.txt", "all_goods");
					cout << "**************************   �޸ĳɹ�   *************************" << endl << endl;
				}

				else if ('n' == ch)
					cout << "***********************   ��ȡ���޸ģ��޸�ʧ�ܣ�   *************************" << endl;
				else
					cout << "***********************   �޸�ʧ�ܣ��밴Ҫ�����룡   ***********************" << endl;
			}
		}
		else
			cout << "**************************   ��û�з�������Ʒ���޸�ʧ�ܣ�   *******************************" << endl << endl;
	}
	else
	{
		cout << "*****************************************************************" << endl;
		cout << "û���ҵ�����Ʒ��" << endl;
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