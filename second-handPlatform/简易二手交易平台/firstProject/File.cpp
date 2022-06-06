#include<iostream>
#include<map>
#include<iomanip>
using namespace std;
#include<fstream>
#include "map.h"
static struct User u1;
static struct Goods goods;
static struct Order order;
static struct Report report;
string str;



void _ReadFile(const string& s, const string& judg)
{

	fstream fs;
	fs.open(s);
	if (!fs)
	{
		ofstream out_data;
		out_data.open(s, ios::app);
		out_data.close();
	}

	else
	{
		getline(fs, str);
		fs >> str;
		while (!fs.eof())
		{
			if (judg == "users")
			{
				fs >> u1.name >> u1.password >> u1.tel >> u1.adr >> u1.balance>>u1.exist;
				fs >> u1.on_punishment;
				users[str] = u1;
				fs >> str;
			}
			else if (judg == "all_goods")
			{
				fs >> goods.name >> goods.price >> goods.description >> goods.seller >> goods.time_issued >> goods.condition>>goods.amount>>goods.num;
				if (0 == goods.num)
					fs>>goods.goods_evaluation[1];
				else
					for (int i = 1; i <= goods.num; ++i)
					{
						fs >> goods.goods_evaluation[i];
					}
				all_goods[str] = goods;
				fs >> str;
			}
			else if(judg == "orders")
			{
				fs >> order.goods_id >> order.money >> order.time_dealed >> order.seller >> order.buyer>>order.eval_condition>>order.ord_condition>>order.amount;
				orders[str] = order;
				fs >> str;
			}
			else if (judg == "reported")
			{
				fs >> report.num>>report.on_punishment >> report.start_time >> report.end_time>>report.m;
				if (report.num == 0)
					fs >> report.reported_reason["0"];
				else
				{
					string s;
					for (int i = 1; i <= report.num; ++i)
					{
						fs >> s;
						fs >> report.reported_reason[s];

					}
				}
				reported_users[str] = report;
				fs >> str;
			}
		}

	}
	fs.close();
}

void _DateFile(const string& s, const string &judg)
{

	ofstream f(s);
	if (!f.is_open())
		cout << "打开失败";
	if(judg == "users")
	{
		f << left << setw(10) << "用户ID" << left << setw(30) << "用户名" << left << setw(20) << "密码" << left << setw(20) << "联系方式" << left << setw(40) << "地址" << left << setw(10) << "钱包余额"<<' '<<"评价数量"<<' ' << left << setw(40) <<"用户评价"<<' '<<"是否处罚中"<< endl;
		for (map<string, struct User>::iterator it = users.begin(); it != users.end(); ++it)
		{
			f << left << setw(10) << it->first<<' ' << left << setw(30) << it->second.name <<' ';
			f << left << setw(20) << it->second.password << ' ' << left << setw(20) << it->second.tel << ' ' << left << setw(40) << it->second.adr << ' ' << fixed << setprecision(1) << left << setw(5) << it->second.balance << ' ' << left << setw(2) << it->second.exist << ' ';
			f << it->second.on_punishment << ' ' << endl;
			
		}
	}
	else if (judg == "all_goods")
	{
		f << left << setw(8) << "商品ID" << left << setw(12) << "名称" << left << setw(20) << "价格" << left << setw(100) << "描述" << left << setw(8) << "卖家ID" << left << setw(12) << "上架时间" << left << setw(10) << "商品状态"<<left<<setw(10) << "商品数量" <<left<<setw(9)<<"评价数量"<<left<<setw(40)<<"用户评价"<<' ' << endl;
		for (map<string, struct Goods>::iterator it = all_goods.begin(); it != all_goods.end(); ++it)
		{
			goods = it->second;
			f << left << setw(8) << it->first << ' ' << left << setw(12) << goods.name << ' ' << fixed << setprecision(1) << left << setw(20) << goods.price << ' ' << left << setw(100) << goods.description << ' ' << left << setw(8) << goods.seller << ' ' << left << setw(12) << goods.time_issued << ' ' << left << setw(8) << goods.condition << ' ' << left << setw(10) << goods.amount << ' ' << left << setw(10) << goods.num << ' ';
			if (goods.num == 0)
			{
				f << goods.goods_evaluation[1]<<' ';
			}
			else
				for (int i = 1; i <= goods.num; ++i)
					f << goods.goods_evaluation[i]<<' '<<endl;
		}
	}
	else if(judg == "orders")
	{
		f << left << setw(8) << "订单ID" << left << setw(8) << "商品ID" << left << setw(20) << "交易金额" << left << setw(12) << "交易时间" << left << setw(8) << "卖家ID" << left << setw(8) << "买家ID" << left<<setw(6)<<"订单评价状态" << left << setw(10) << "订单状态" <<' '<<"商品数量"<<endl;
		for (map<string, struct Order>::iterator it = orders.begin(); it != orders.end(); ++it)
		{
			order = it->second;
			f << left << setw(8) << it->first<<' ' << left << setw(8) << order.goods_id <<' '<< fixed<<setprecision(1)<< left << setw(20) << order.money <<' '<< left << setw(12) << order.time_dealed <<' '<< left << setw(8) << order.seller <<' '<< left << setw(8) << order.buyer<<' '<<left<<setw(6)<<order.eval_condition<<' ' <<left<<setw(8)<<order.ord_condition<<' '<<left<<setw(2)<<order.amount<<' '<< endl;
		}
	}
	else if (judg == "reported")
	{
		f << "被举报用户ID" << ' ' << "被举报次数" << ' '  << "是否受罚中" << ' ' << "处罚开始时间" << ' ' << "处罚结束时间" << ' ' <<"举报者ID" << ' ' << "举报原因" << ' ' <<endl;
		for (auto it = reported_users.begin(); it != reported_users.end(); ++it)
		{
			f << left << setw(13) << it->first << ' ' << left << setw(12) << it->second.num << ' ';
			f <<left<<setw(12)<< it->second.on_punishment << ' ' <<left<<setw(14)<< it->second.start_time << ' ' << left << setw(14) << it->second.end_time << ' ' <<it->second.m<<' '<< endl;
			for (auto iter = it->second.reported_reason.begin(); iter != it->second.reported_reason.end(); ++iter)
			{
				f << left << setw(10) << iter->first << ' ';
				f<< iter->second << ' ' << endl;
			}

		}
	}

	f.close();
}
