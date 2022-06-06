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
			cout << "ID                  名称                          价格          上架时间            卖家ID      商品状态     商品数量 商品评价 " << endl;
			for (; it != all_goods.end(); ++it)
			{
				cout << left << setw(20) << it->first << left << setw(30) << it->second.name << fixed<<setprecision(1)<<left << setw(15) << it->second.price << left << setw(20) << it->second.time_issued << left << setw(10) << it->second.seller << left << setw(10) << it->second.condition <<left<<setw(10)<<it->second.amount;
				for (auto iter = it->second.goods_evaluation.begin(); iter != it->second.goods_evaluation.end(); ++iter)
				{
					char c;
					cout << "“";
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
					cout << "”" << endl;

				}
				
			}
		}
		else
			cout << "无已发布商品！" << endl;
		cout << "******************************************************************************************************************************************************************" << endl;
	}
	else if (identity == "buyer")
	{
		cout << "******************************************************************************************************************************************************************" << endl;
		if (it != all_goods.end())
		{
			for (; it != all_goods.end(); ++it)
			{
				if (it->second.condition == "销售中" && it->second.seller != cur_id)
				{
					is_existed = true;
					if (flag)
						cout << "ID                  名称                     价格           上架时间          卖家ID      商品数量 商品评价  " << endl;
					flag = 0;
					cout << left << setw(20) << it->first << left << setw(25) << it->second.name << fixed << setprecision(1) << left << setw(15) << it->second.price << left << setw(20) << it->second.time_issued << left << setw(10) << it->second.seller <<left<<setw(10)<<it->second.amount;
					for (auto iter = it->second.goods_evaluation.begin(); iter != it->second.goods_evaluation.end(); ++iter)
					{
						char c;
						cout << "“";
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
						cout << "”" << endl;

					}
					
				}
			}
		}
		if(!is_existed)
			cout << "无在售商品！" << endl;
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
						cout << "您发布的商品清单如下：" << endl << endl;
						cout << "ID                  名称                          价格                上架时间             商品状态     商品数量  商品评价" << endl;
					}
					flag = 0;
					
					cout << left << setw(20) << it->first << left << setw(30) << it->second.name << left << setw(20) << it->second.price << left << setw(20) << it->second.time_issued << left << setw(12) << it->second.condition <<left<<setw(10)<<it->second.amount;
					for (auto iter = it->second.goods_evaluation.begin(); iter != it->second.goods_evaluation.end(); ++iter)
					{
						char c;
						cout << "“";
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
						cout << "”" << endl;

					}
					
				}
			}
		}
		if(!is_existed)
			cout << "您没有发布任何商品！" << endl;
		cout << "******************************************************************************************************************************************************************" << endl;

	}
	cout << endl << endl;

}

void _CheckDetailedGoods()
{
	cout << "请输入你想查看的商品ID:";
	string s;
	cin.ignore();
	getline(cin, s);
	auto it = all_goods.find(s);
	cout << "***********************************************************************" << endl;
	if(it != all_goods.end())
	{
		if (it->second.condition == "销售中")
		{
			cout << "名称：      ";
			cout << it->second.name << endl;
			cout << "描述：      ";
			for (auto iter = it->second.description.begin(); iter != it->second.description.end(); ++iter)
			{
				if (*iter == '|')
					*iter = ' ';
				cout << *iter;
			}
			cout << endl;
			cout << "上架时间：  ";
			cout << it->second.time_issued << endl;
			cout << "卖家ID：    ";
			cout << it->second.seller << endl;
			cout << "商品状态：  ";
			cout << it->second.condition << endl;
			cout << "商品数量： ";
			cout << it->second.amount << endl;
			cout << "用户评价： ";
			for (auto iter = it->second.goods_evaluation.begin(); iter != it->second.goods_evaluation.end(); ++iter)
			{
				char c;
				cout << "“";
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
				cout << "”" << endl;

			}
			cout << endl;
			
		}
		else
			cout << "未找到该商品！" << endl;
	}
	else
		cout << "未找到该商品！" << endl;
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
			cout << "ID         商品ID       交易金额          交易时间           买家ID       卖家ID  " << endl;
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
						cout << "ID         商品ID       交易金额          交易时间           买家ID    订单状态  " << endl;
					flag = 0;
					cout << left << setw(10) << it->first << left << setw(14) << it->second.goods_id << fixed << setprecision(1) << left << setw(20) << it->second.money << left << setw(20) << it->second.time_dealed << left << setw(10) << it->second.buyer<<left<<setw(8)<<it->second.ord_condition<<endl;
				}
			if (!is_existed)
				cout << "无历史订单！" << endl;
		}
		else if ("buyer" == identity)
		{
		
			for (; it != orders.end(); ++it)
				if (it->second.buyer == cur_id)
				{
					is_existed = true;
					if (flag)
						cout << "ID         商品ID       交易金额          交易时间           卖家ID     订单状态  订单评价状态 " << endl;
					flag = 0;
					cout << left << setw(10) << it->first << left << setw(14) << it->second.goods_id << fixed << setprecision(1) << left << setw(20) << it->second.money << left << setw(20) << it->second.time_dealed << left << setw(10) << it->second.seller <<left<<setw(8)<<it->second.ord_condition<<left<<setw(6)<<it->second.eval_condition<< endl;
				}
			if (!is_existed)
				cout << "无历史订单！" << endl;
		}
	}
	else
		cout << "无已成交的订单！" << endl;
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
		cout << "用户ID    用户名              联系方式            地址           钱包余额   " << endl;
		for (; it != users.end(); ++it)
		{
			if (it->second.exist)
				cout << left << setw(10) << it->first << left << setw(20) << it->second.name << left << setw(20) << it->second.tel << left << setw(20) << it->second.adr << fixed<<setprecision(1)<<left << setw(5) << it->second.balance << endl;
		}
	}
	else
		cout << "无用户！" << endl;
	cout << "**********************************************************************************************" << endl;
	cout << endl << endl;
}

void _CheckUserInf()
{
	auto it = users.find(cur_id);
	cout << "*********************************************************************************" << endl;
	cout << "用户名:    ";
	cout << it->second.name << endl;
	cout << "联系方式： ";
	cout << it->second.tel << endl;
	cout << "地址：     ";
	cout << it->second.adr << endl;
	cout << "钱包余额： ";
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
	cout << "请输入商品名称：";
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
						cout << "ID          名称               价格         上架时间         卖家ID      商品状态      商品评价" << endl;
					judg = false;
					flag = 1;
					cout << left << setw(10) << it->first << left << setw(20) << it->second.name <<fixed<<setprecision(1)<< left << setw(15) << it->second.price << left << setw(15) << it->second.time_issued << left << setw(15) << it->second.seller << left << setw(10) << it->second.condition;
					for (auto iter = it->second.goods_evaluation.begin(); iter != it->second.goods_evaluation.end(); ++iter)
					{
						char c;
						cout << "“";
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
						cout << "”" << endl;

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
				if (it->second.name == s   && it->second.condition == "销售中")
				{
					if(judg)
						cout << "ID            名称                价格          上架时间            卖家ID        商品评价    " << endl;
					judg = false;
					flag = 1;
					cout << left << setw(14) << it->first << left << setw(20) << it->second.name << fixed<<setprecision(1)<<left << setw(15) << it->second.price << left << setw(20) << it->second.time_issued << left << setw(10) << it->second.seller;
					for (auto iter = it->second.goods_evaluation.begin(); iter != it->second.goods_evaluation.end(); ++iter)
					{
						char c;
						cout << "“";
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
						cout << "”" << endl;

					}
					for (int i = 0; i < it->second.num; ++i)
						cout << endl;
				}
			}
		}
	}
	if (0 == flag)
		cout << "未找到您想要的商品! 即将返回初始界面！" << endl;
	cout << "*****************************************************************************************************************" << endl;
	cout << endl << endl;
}

void _Evaluate()
{
	cout << "请选择是否对商品进行评价" << endl;
	cout << "----------------------------------------------------------------" << endl;
	cout << "1.对商品进行评价  2.不进行评价" << endl;
	cout << "----------------------------------------------------------------" << endl;
	cout << "请选择您要进行的操作的选项： ";
	int n;
	cin >> n;
	while (cin.fail())
	{
		cout << "请按要求输入您要进行的操作的序号！" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "请输入： ";
		cin >> n;
	}
	switch (n)
	{
	case 1:
	{
		cout << "请输入您要评价的商品的订单号：";
		string s;
		cin.ignore();
		getline(cin,s);
		auto it = orders.find(s);
		if (it != orders.end())
		{
			if (it->second.buyer == cur_id)
			{
				if (it->second.eval_condition == "未评价")
				{
					if (it->second.ord_condition == "已收货")
					{
						auto goods_it = all_goods.find(it->second.goods_id);
						cout << "请输入您对该商品的评价，按回车键结束：" << endl;
						++goods_it->second.num;
						getline(cin, goods_it->second.goods_evaluation[goods_it->second.num]);
						for (auto iter = goods_it->second.goods_evaluation[goods_it->second.num].begin(); iter != goods_it->second.goods_evaluation[goods_it->second.num].end(); ++iter)
						{
							if (*iter == ' ')
								*iter = '|';
						}
						it->second.eval_condition = "已评价";
						_DateFile("goods.txt", "all_goods");
					}
					else
					{
						cout << "确认收货后方可评价，是否确认收货？" << endl;
						cout << "请选择 y/n：";
						char ch;
						cin >> ch;
						if (ch == 'y')
						{
							it->second.ord_condition = "已收货";
							auto goods_it = all_goods.find(it->second.goods_id);
							cout << "请输入您对该商品的评价，按回车键结束：" << endl;
							++goods_it->second.num;
							cin.ignore();
							getline(cin, goods_it->second.goods_evaluation[goods_it->second.num]);
							for (auto iter = goods_it->second.goods_evaluation[goods_it->second.num].begin(); iter != goods_it->second.goods_evaluation[goods_it->second.num].end(); ++iter)
							{
								if (*iter == ' ')
									*iter = '|';
							}
							it->second.eval_condition = "已评价";
							_DateFile("goods.txt", "all_goods");
							_DateFile("orders.txt", "orders");
							cout << "评价成功！评价如下：" << endl;
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
							cout << "确认收货失败！" << endl;
							cout << "******************************************************************************************" << endl;
						}
					}
				}
				else if (it->second.eval_condition == "已评价")
				{
					cout << "您已评价过该订单！ 是否需要追加评论？" << endl;
					cout << "请选择（y/n）: ";
					char ch;
					cin >> ch;
					if (ch == 'y')
					{
						string s;
						cout << "请输入您需要追加的评价："<<endl;
						cin.ignore();
						getline(cin, s);
						auto goods_it = all_goods.find(it->second.goods_id);
						for (auto iter = s.begin(); iter != s.end(); ++iter)
						{
							if (*iter == ' ')
								*iter = '|';
						}
						goods_it->second.goods_evaluation[goods_it->second.num].append("$追加评论："+ s);
						cout << "追加评价成功！评价如下：" << endl;
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
						cout << "追加评价失败！" << endl;
						cout << "******************************************************************************************" << endl<<endl;
					}
				}
			}
			
		}
		else
		{
			cout << "******************************************************************************************" << endl;
			cout << "未找到该订单！" << endl;
			cout << "******************************************************************************************" << endl<<endl;
		}
		break;
	}
		case 2:
	{
		cout << "******************************************************************************************" << endl;
		cout << "即将退出评价！" << endl;
		cout << "******************************************************************************************" << endl<<endl;
		break;
	}
	default:
		cout << endl;
		cout << "****************************   没有该操作选项，即将退出评价！   ******************************" << endl<<endl;
	}
}

void _CheckReportedInf()
{
	bool b = true;
	auto it = reported_users.find(cur_id);
	if (it == reported_users.end())
	{
		cout << "*****************************************************************************************************" << endl;
		cout << "您的信誉良好，没有收到任何举报信息！" << endl;
		cout << "*****************************************************************************************************" << endl << endl << endl;
	}
	else
	{
		cout << "您共收到"<<it->second.num<<"条举报信息， 具体信息如下：" << endl;
		cout << "*****************************************************************************************************" << endl;
		for (auto it1 = it->second.reported_reason.begin(); it1 != it->second.reported_reason.end(); ++it1)
		{
			if (it1->first != "0")
			{
				for (auto iter = it1->second.begin(); iter != it1->second.end(); ++iter)
				{
					if(b)
						cout << "“";
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
						cout << "”" << endl;
					cout << c;

				}
				cout << "”" << endl;

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
		cout << "举报信息如下：" << endl;
		cout << "*****************************************************************************************************" << endl;
		cout << left << setw(12) << "被举报者ID" << left << setw(10) << "举报者ID" << left << setw(40) << "举报原因" << endl;
		for (; it != reported_users.end(); ++it)
		{
			for (auto it1 = it->second.reported_reason.begin(); it1 != it->second.reported_reason.end(); ++it1)
			{
				cout << left << setw(12) << it->first << left << setw(10) << it1->first ;
				for (auto iter = it1->second.begin(); iter != it1->second.end(); ++iter)
				{
					if (b)
						cout << "“";
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
						cout << "”" << endl;
					cout << c;

				}
				cout << "”" << endl;
			}
		}
		cout << "*****************************************************************************************************" << endl << endl;

	}
	else
	{
		cout << "*****************************************************************************************************" << endl;
		cout << "没有举报信息！" << endl;
		cout << "*****************************************************************************************************" << endl << endl;
	}
}

void _Accept()
{
	cout << "请确认是否需要收货：";
	cout << "请选择（y/n）：";
	char ch;
	cin.ignore();
	ch = getchar();
	if (ch == 'y')
	{
		cout << "请输入您要确认收货的商品的订单ID:";
		string ord_id;
		cin.ignore();
		getline(cin, ord_id);
		auto it = orders.find(ord_id);
		if (it != orders.end())
		{
			if (it->second.ord_condition != "已收货")
			{
				it->second.ord_condition = "已收货";
				_DateFile("orders.txt", "orders");
				cout << "*****************************************************************************************************" << endl;
				cout << "确认收货成功！" << endl;
				cout << "*****************************************************************************************************" << endl<<endl;
			}
			else
			{
				cout << "*****************************************************************************************************" << endl;
				cout << "您已确认收货，无需再次确认！！" << endl;
				cout << "*****************************************************************************************************" << endl << endl;
			}
		}
		else
		{
			cout << "*****************************************************************************************************" << endl;
			cout << "没有找到该订单！" << endl;
			cout << "*****************************************************************************************************" << endl<<endl;
		}

	}
	else
	{
		cout << "*****************************************************************************************************" << endl;
		cout << "您没有确认收货， 请在收到货物后及时确认收货！" << endl;
		cout << "*****************************************************************************************************" << endl<<endl;
	}
}