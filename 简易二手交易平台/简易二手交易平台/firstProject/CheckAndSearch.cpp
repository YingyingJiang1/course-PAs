#include "map.h"
#include <iostream>
#include <iomanip>
#include "File.h"
using namespace std;
extern  string cur_id;
void _Evaluate();
void _Accept();
void _CheckGoods(const string& identity)
{
	int flag = 1;
	bool is_existed = false;
	auto it = all_goods.begin();
	if (identity == "adm")
	{
		cout << "******************************************************************************************************************************************************************" << endl;
		if (it != all_goods.end())
		{
			cout << "ID                  ����                          �۸�          �ϼ�ʱ��            ����ID      ��Ʒ״̬     ��Ʒ���� ��Ʒ���� " << endl;
			for (; it != all_goods.end(); ++it)
			{
				cout << left << setw(20) << it->first << left << setw(30) << it->second.name << fixed<<setprecision(1)<<left << setw(15) << it->second.price << left << setw(20) << it->second.time_issued << left << setw(10) << it->second.seller << left << setw(10) << it->second.condition <<left<<setw(10)<<it->second.amount;
				for (auto iter = it->second.goods_evaluation.begin(); iter != it->second.goods_evaluation.end(); ++iter)
				{
					char c;
					cout << "��";
					for (auto it1 = iter->second.begin(); it1 != iter->second.end(); ++it1)
					{
						if (*it1 == '|')
							c = ' ';
						else if (*it1 == '$')
							c = '\n';
						else
							c = *it1;
						cout << c;
					}
					cout << "��" << endl;

				}
				
			}
		}
		else
			cout << "���ѷ�����Ʒ��" << endl;
		cout << "******************************************************************************************************************************************************************" << endl;
	}
	else if (identity == "buyer")
	{
		cout << "******************************************************************************************************************************************************************" << endl;
		if (it != all_goods.end())
		{
			for (; it != all_goods.end(); ++it)
			{
				if (it->second.condition == "������" && it->second.seller != cur_id)
				{
					is_existed = true;
					if (flag)
						cout << "ID                  ����                     �۸�           �ϼ�ʱ��          ����ID      ��Ʒ���� ��Ʒ����  " << endl;
					flag = 0;
					cout << left << setw(20) << it->first << left << setw(25) << it->second.name << fixed << setprecision(1) << left << setw(15) << it->second.price << left << setw(20) << it->second.time_issued << left << setw(10) << it->second.seller <<left<<setw(10)<<it->second.amount;
					for (auto iter = it->second.goods_evaluation.begin(); iter != it->second.goods_evaluation.end(); ++iter)
					{
						char c;
						cout << "��";
						for (auto it1 = iter->second.begin(); it1 != iter->second.end(); ++it1)
						{
							if (*it1 == '|')
								c = ' ';
							else if (*it1 == '$')
								c = '\n';
							else
								c = *it1;
							cout << c;
						}
						cout << "��" << endl;

					}
					
				}
			}
		}
		if(!is_existed)
			cout << "��������Ʒ��" << endl;
		cout << "******************************************************************************************************************************************************************" << endl;
	}
	else if (identity == "seller")
	{
		cout << "******************************************************************************************************************************************************************" << endl;
		if (it != all_goods.end())
		{
			for (; it != all_goods.end(); ++it)
			{
				if (cur_id == it->second.seller)
				{
					is_existed = true;
					if (flag)
					{
						cout << "����������Ʒ�嵥���£�" << endl << endl;
						cout << "ID                  ����                          �۸�                �ϼ�ʱ��             ��Ʒ״̬     ��Ʒ����  ��Ʒ����" << endl;
					}
					flag = 0;
					
					cout << left << setw(20) << it->first << left << setw(30) << it->second.name << left << setw(20) << it->second.price << left << setw(20) << it->second.time_issued << left << setw(12) << it->second.condition <<left<<setw(10)<<it->second.amount;
					for (auto iter = it->second.goods_evaluation.begin(); iter != it->second.goods_evaluation.end(); ++iter)
					{
						char c;
						cout << "��";
						for (auto it1 = iter->second.begin(); it1 != iter->second.end(); ++it1)
						{
							if (*it1 == '|')
								c = ' ';
							else if (*it1 == '$')
								c = '\n';
							else
								c = *it1;
							cout << c;
						}
						cout << "��" << endl;

					}
					
				}
			}
		}
		if(!is_existed)
			cout << "��û�з����κ���Ʒ��" << endl;
		cout << "******************************************************************************************************************************************************************" << endl;

	}
	cout << endl << endl;

}

void _CheckDetailedGoods()
{
	cout << "����������鿴����ƷID:";
	string s;
	cin.ignore();
	getline(cin, s);
	auto it = all_goods.find(s);
	cout << "***********************************************************************" << endl;
	if(it != all_goods.end())
	{
		if (it->second.condition == "������")
		{
			cout << "���ƣ�      ";
			cout << it->second.name << endl;
			cout << "������      ";
			for (auto iter = it->second.description.begin(); iter != it->second.description.end(); ++iter)
			{
				if (*iter == '|')
					*iter = ' ';
				cout << *iter;
			}
			cout << endl;
			cout << "�ϼ�ʱ�䣺  ";
			cout << it->second.time_issued << endl;
			cout << "����ID��    ";
			cout << it->second.seller << endl;
			cout << "��Ʒ״̬��  ";
			cout << it->second.condition << endl;
			cout << "��Ʒ������ ";
			cout << it->second.amount << endl;
			cout << "�û����ۣ� ";
			for (auto iter = it->second.goods_evaluation.begin(); iter != it->second.goods_evaluation.end(); ++iter)
			{
				char c;
				cout << "��";
				for (auto it1 = iter->second.begin(); it1 != iter->second.end(); ++it1)
				{
					if (*it1 == '|')
						c = ' ';
					else if (*it1 == '$')
						c = '\n';
					else
						c = *it1;
					cout << c;
				}
				cout << "��" << endl;

			}
			cout << endl;
			
		}
		else
			cout << "δ�ҵ�����Ʒ��" << endl;
	}
	else
		cout << "δ�ҵ�����Ʒ��" << endl;
	cout << "***********************************************************************" << endl;
	cout << endl << endl;

}


void _CheckOrders(const string& identity)
{
	int flag = 1;
	bool is_existed = false;
	cout << "******************************************************************************************" << endl;
	auto it = orders.begin();
	if (it != orders.end())
	{
		if ("adm" == identity)
		{
			cout << "ID         ��ƷID       ���׽��          ����ʱ��           ���ID       ����ID  " << endl;
			for (; it != orders.end(); ++it)
				cout << left << setw(10) << it->first << left << setw(14) << it->second.goods_id << fixed<<setprecision(1)<<left << setw(18) << it->second.money << left << setw(20) << it->second.time_dealed << left << setw(10) << it->second.buyer << left << setw(12) << it->second.seller << endl;
		}
		else if ("seller" == identity)
		{
			for (; it != orders.end(); ++it)
				if (it->second.seller == cur_id)
				{
					is_existed = true;
					if (flag)
						cout << "ID         ��ƷID       ���׽��          ����ʱ��           ���ID    ����״̬  " << endl;
					flag = 0;
					cout << left << setw(10) << it->first << left << setw(14) << it->second.goods_id << fixed << setprecision(1) << left << setw(20) << it->second.money << left << setw(20) << it->second.time_dealed << left << setw(10) << it->second.buyer<<left<<setw(8)<<it->second.ord_condition<<endl;
				}
			if (!is_existed)
				cout << "����ʷ������" << endl;
		}
		else if ("buyer" == identity)
		{
		
			for (; it != orders.end(); ++it)
				if (it->second.buyer == cur_id)
				{
					is_existed = true;
					if (flag)
						cout << "ID         ��ƷID       ���׽��          ����ʱ��           ����ID     ����״̬  ��������״̬ " << endl;
					flag = 0;
					cout << left << setw(10) << it->first << left << setw(14) << it->second.goods_id << fixed << setprecision(1) << left << setw(20) << it->second.money << left << setw(20) << it->second.time_dealed << left << setw(10) << it->second.seller <<left<<setw(8)<<it->second.ord_condition<<left<<setw(6)<<it->second.eval_condition<< endl;
				}
			if (!is_existed)
				cout << "����ʷ������" << endl;
		}
	}
	else
		cout << "���ѳɽ��Ķ�����" << endl;
	cout << "******************************************************************************************" << endl;
	cout << endl << endl;
	if (is_existed && identity == "buyer")
	{
		_Accept();
		_Evaluate();
	}
}

void _CheckAllUsers()
{
	auto it = users.begin();
	cout << "**********************************************************************************************" << endl;
	if (it != users.end())
	{
		cout << "�û�ID    �û���              ��ϵ��ʽ            ��ַ           Ǯ�����   " << endl;
		for (; it != users.end(); ++it)
		{
			if (it->second.exist)
				cout << left << setw(10) << it->first << left << setw(20) << it->second.name << left << setw(20) << it->second.tel << left << setw(20) << it->second.adr << fixed<<setprecision(1)<<left << setw(5) << it->second.balance << endl;
		}
	}
	else
		cout << "���û���" << endl;
	cout << "**********************************************************************************************" << endl;
	cout << endl << endl;
}

void _CheckUserInf()
{
	auto it = users.find(cur_id);
	cout << "*********************************************************************************" << endl;
	cout << "�û���:    ";
	cout << it->second.name << endl;
	cout << "��ϵ��ʽ�� ";
	cout << it->second.tel << endl;
	cout << "��ַ��     ";
	cout << it->second.adr << endl;
	cout << "Ǯ���� ";
	cout <<fixed<<setprecision(1)<< it->second.balance << endl;
	cout << "*********************************************************************************" << endl;
	cout << endl << endl;
}

void _SearchGoods(const string& identity)
{
	int flag = 0;
	bool judg = true;
	string s;
	auto it = all_goods.begin();
	cout << "��������Ʒ���ƣ�";
	cin >> s;
	cout << "*****************************************************************************************************************" << endl;
	if (it != all_goods.end())
	{
		if (identity == "adm")
		{
			for (; it != all_goods.end(); ++it)
			{
				if (it->second.name == s)
				{
					if (judg)
						cout << "ID          ����               �۸�         �ϼ�ʱ��         ����ID      ��Ʒ״̬      ��Ʒ����" << endl;
					judg = false;
					flag = 1;
					cout << left << setw(10) << it->first << left << setw(20) << it->second.name <<fixed<<setprecision(1)<< left << setw(15) << it->second.price << left << setw(15) << it->second.time_issued << left << setw(15) << it->second.seller << left << setw(10) << it->second.condition;
					for (auto iter = it->second.goods_evaluation.begin(); iter != it->second.goods_evaluation.end(); ++iter)
					{
						char c;
						cout << "��";
						for (auto it1 = iter->second.begin(); it1 != iter->second.end(); ++it1)
						{
							if (*it1 == '|')
								c = ' ';
							else if (*it1 == '$')
								c = '\n';
							else
								c = *it1;
							cout << c;
						}
						cout << "��" << endl;

					}
					for (int i = 0; i < it->second.num; ++i)
						cout << endl;

				}
			}
		}
		if (identity == "buyer")
		{
			for (; it != all_goods.end(); ++it)
			{
				if (it->second.name == s   && it->second.condition == "������")
				{
					if(judg)
						cout << "ID            ����                �۸�          �ϼ�ʱ��            ����ID        ��Ʒ����    " << endl;
					judg = false;
					flag = 1;
					cout << left << setw(14) << it->first << left << setw(20) << it->second.name << fixed<<setprecision(1)<<left << setw(15) << it->second.price << left << setw(20) << it->second.time_issued << left << setw(10) << it->second.seller;
					for (auto iter = it->second.goods_evaluation.begin(); iter != it->second.goods_evaluation.end(); ++iter)
					{
						char c;
						cout << "��";
						for (auto it1 = iter->second.begin(); it1 != iter->second.end(); ++it1)
						{
							if (*it1 == '|')
								c = ' ';
							else if (*it1 == '$')
								c = '\n';
							else
								c = *it1;
							cout << c;
						}
						cout << "��" << endl;

					}
					for (int i = 0; i < it->second.num; ++i)
						cout << endl;
				}
			}
		}
	}
	if (0 == flag)
		cout << "δ�ҵ�����Ҫ����Ʒ! �������س�ʼ���棡" << endl;
	cout << "*****************************************************************************************************************" << endl;
	cout << endl << endl;
}

void _Evaluate()
{
	cout << "��ѡ���Ƿ����Ʒ��������" << endl;
	cout << "----------------------------------------------------------------" << endl;
	cout << "1.����Ʒ��������  2.����������" << endl;
	cout << "----------------------------------------------------------------" << endl;
	cout << "��ѡ����Ҫ���еĲ�����ѡ� ";
	int n;
	cin >> n;
	while (cin.fail())
	{
		cout << "�밴Ҫ��������Ҫ���еĲ�������ţ�" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "�����룺 ";
		cin >> n;
	}
	switch (n)
	{
	case 1:
	{
		cout << "��������Ҫ���۵���Ʒ�Ķ����ţ�";
		string s;
		cin.ignore();
		getline(cin,s);
		auto it = orders.find(s);
		if (it != orders.end())
		{
			if (it->second.buyer == cur_id)
			{
				if (it->second.eval_condition == "δ����")
				{
					if (it->second.ord_condition == "���ջ�")
					{
						auto goods_it = all_goods.find(it->second.goods_id);
						cout << "���������Ը���Ʒ�����ۣ����س���������" << endl;
						++goods_it->second.num;
						getline(cin, goods_it->second.goods_evaluation[goods_it->second.num]);
						for (auto iter = goods_it->second.goods_evaluation[goods_it->second.num].begin(); iter != goods_it->second.goods_evaluation[goods_it->second.num].end(); ++iter)
						{
							if (*iter == ' ')
								*iter = '|';
						}
						it->second.eval_condition = "������";
						_DateFile("goods.txt", "all_goods");
					}
					else
					{
						cout << "ȷ���ջ��󷽿����ۣ��Ƿ�ȷ���ջ���" << endl;
						cout << "��ѡ�� y/n��";
						char ch;
						cin >> ch;
						if (ch == 'y')
						{
							it->second.ord_condition = "���ջ�";
							auto goods_it = all_goods.find(it->second.goods_id);
							cout << "���������Ը���Ʒ�����ۣ����س���������" << endl;
							++goods_it->second.num;
							cin.ignore();
							getline(cin, goods_it->second.goods_evaluation[goods_it->second.num]);
							for (auto iter = goods_it->second.goods_evaluation[goods_it->second.num].begin(); iter != goods_it->second.goods_evaluation[goods_it->second.num].end(); ++iter)
							{
								if (*iter == ' ')
									*iter = '|';
							}
							it->second.eval_condition = "������";
							_DateFile("goods.txt", "all_goods");
							_DateFile("orders.txt", "orders");
							cout << "���۳ɹ����������£�" << endl;
							cout << "******************************************************************************************" << endl;
							for (auto it = goods_it->second.goods_evaluation[goods_it->second.num].begin(); it != goods_it->second.goods_evaluation[goods_it->second.num].end(); ++it)
							{
								char c;
								if (*it == '|')
									c = ' ';
								else  if (*it == '$')
									c = '\n';
								else
									c = *it;
								cout << c;

							}
							cout << endl;
							cout << endl;
							cout << "******************************************************************************************" << endl << endl;
						}
						else
						{
							cout << "******************************************************************************************" << endl;
							cout << "ȷ���ջ�ʧ�ܣ�" << endl;
							cout << "******************************************************************************************" << endl;
						}
					}
				}
				else if (it->second.eval_condition == "������")
				{
					cout << "�������۹��ö����� �Ƿ���Ҫ׷�����ۣ�" << endl;
					cout << "��ѡ��y/n��: ";
					char ch;
					cin >> ch;
					if (ch == 'y')
					{
						string s;
						cout << "����������Ҫ׷�ӵ����ۣ�"<<endl;
						cin.ignore();
						getline(cin, s);
						auto goods_it = all_goods.find(it->second.goods_id);
						for (auto iter = s.begin(); iter != s.end(); ++iter)
						{
							if (*iter == ' ')
								*iter = '|';
						}
						goods_it->second.goods_evaluation[goods_it->second.num].append("$׷�����ۣ�"+ s);
						cout << "׷�����۳ɹ����������£�" << endl;
						cout << "******************************************************************************************" << endl;
						for (auto it = goods_it->second.goods_evaluation[goods_it->second.num].begin(); it != goods_it->second.goods_evaluation[goods_it->second.num].end(); ++it)
						{
							char c;
							if (*it == '|')
								c = ' ';
						 else if (*it == '$')
								c = '\n';
							else
								c = *it;
							cout << c;

						}
						cout << endl;
						cout << "******************************************************************************************" << endl << endl;
						_DateFile("goods.txt", "all_goods");
					}
					else
					{
						cout << "******************************************************************************************" << endl;
						cout << "׷������ʧ�ܣ�" << endl;
						cout << "******************************************************************************************" << endl<<endl;
					}
				}
			}
			
		}
		else
		{
			cout << "******************************************************************************************" << endl;
			cout << "δ�ҵ��ö�����" << endl;
			cout << "******************************************************************************************" << endl<<endl;
		}
		break;
	}
		case 2:
	{
		cout << "******************************************************************************************" << endl;
		cout << "�����˳����ۣ�" << endl;
		cout << "******************************************************************************************" << endl<<endl;
		break;
	}
	default:
		cout << endl;
		cout << "****************************   û�иò���ѡ������˳����ۣ�   ******************************" << endl<<endl;
	}
}

void _CheckReportedInf()
{
	bool b = true;
	auto it = reported_users.find(cur_id);
	if (it == reported_users.end())
	{
		cout << "*****************************************************************************************************" << endl;
		cout << "�����������ã�û���յ��κξٱ���Ϣ��" << endl;
		cout << "*****************************************************************************************************" << endl << endl << endl;
	}
	else
	{
		cout << "�����յ�"<<it->second.num<<"���ٱ���Ϣ�� ������Ϣ���£�" << endl;
		cout << "*****************************************************************************************************" << endl;
		for (auto it1 = it->second.reported_reason.begin(); it1 != it->second.reported_reason.end(); ++it1)
		{
			if (it1->first != "0")
			{
				for (auto iter = it1->second.begin(); iter != it1->second.end(); ++iter)
				{
					if(b)
						cout << "��";
					b = false;
					char c;
					if (*iter == '|')
						c = ' ';
					else if (*iter == '$')
					{
						c = '\n';
						b = true;
					}
					else
						c = *iter;
					if(b)
						cout << "��" << endl;
					cout << c;

				}
				cout << "��" << endl;

			}
		}
		cout << "*****************************************************************************************************" << endl << endl;

	}
}
void _AdmCheckReportedInf()
{
	bool b = true;
	auto it = reported_users.begin();
	if (it != reported_users.end())
	{
		cout << "�ٱ���Ϣ���£�" << endl;
		cout << "*****************************************************************************************************" << endl;
		cout << left << setw(12) << "���ٱ���ID" << left << setw(10) << "�ٱ���ID" << left << setw(40) << "�ٱ�ԭ��" << endl;
		for (; it != reported_users.end(); ++it)
		{
			for (auto it1 = it->second.reported_reason.begin(); it1 != it->second.reported_reason.end(); ++it1)
			{
				cout << left << setw(12) << it->first << left << setw(10) << it1->first ;
				for (auto iter = it1->second.begin(); iter != it1->second.end(); ++iter)
				{
					if (b)
						cout << "��";
					b = false;
					char c;
					if (*iter == '|')
						c = ' ';
					else if (*iter == '$')
					{
						c = '\n';
						b = true;
					}
					else
						c = *iter;
					if (b)
						cout << "��" << endl;
					cout << c;

				}
				cout << "��" << endl;
			}
		}
		cout << "*****************************************************************************************************" << endl << endl;

	}
	else
	{
		cout << "*****************************************************************************************************" << endl;
		cout << "û�оٱ���Ϣ��" << endl;
		cout << "*****************************************************************************************************" << endl << endl;
	}
}

void _Accept()
{
	cout << "��ȷ���Ƿ���Ҫ�ջ���";
	cout << "��ѡ��y/n����";
	char ch;
	cin.ignore();
	ch = getchar();
	if (ch == 'y')
	{
		cout << "��������Ҫȷ���ջ�����Ʒ�Ķ���ID:";
		string ord_id;
		cin.ignore();
		getline(cin, ord_id);
		auto it = orders.find(ord_id);
		if (it != orders.end())
		{
			if (it->second.ord_condition != "���ջ�")
			{
				it->second.ord_condition = "���ջ�";
				_DateFile("orders.txt", "orders");
				cout << "*****************************************************************************************************" << endl;
				cout << "ȷ���ջ��ɹ���" << endl;
				cout << "*****************************************************************************************************" << endl<<endl;
			}
			else
			{
				cout << "*****************************************************************************************************" << endl;
				cout << "����ȷ���ջ��������ٴ�ȷ�ϣ���" << endl;
				cout << "*****************************************************************************************************" << endl << endl;
			}
		}
		else
		{
			cout << "*****************************************************************************************************" << endl;
			cout << "û���ҵ��ö�����" << endl;
			cout << "*****************************************************************************************************" << endl<<endl;
		}

	}
	else
	{
		cout << "*****************************************************************************************************" << endl;
		cout << "��û��ȷ���ջ��� �����յ������ʱȷ���ջ���" << endl;
		cout << "*****************************************************************************************************" << endl<<endl;
	}
}