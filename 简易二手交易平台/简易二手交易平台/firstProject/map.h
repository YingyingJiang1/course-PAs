#pragma once
#ifndef MAP_H
#define MAP_H
#include <map>
#include<string>
using namespace std;
struct User
{
	string	name;//用户名
	string	password;//账号密码
	string    tel;//联系方式
	string   adr;  //地址
	float     balance = 0.0;//余额
	bool	exist = true;//用户存在与否判断
	std::map<int, std::string> buyer_eval ; // 买家对卖家的评价
	bool on_punishment = false;
	int num = 0;
};

struct Goods
{
	string name;	     //商品名
	float	price;	    //价格
	string	description;//商品描述
	string 	seller;	  //卖家ID
	string	time_issued;//上架时间
	string	condition = "销售中";   //商品状态
	std::map<int, std::string> goods_evaluation ;                //用户对商品的评价
	int amount;
	int num = 0;
};

struct Order
{
	string	goods_id;	      //商品ID
	float	money;	     //交易金额
	string	time_dealed; //交易时间
	string	seller;	     //卖家ID
	string	buyer;	    //买家ID
	string  eval_condition = "未评价";        //评价状态（已评价、未评价）
	string ord_condition = "待发货"; //订单状态
	int amount;//购买商品数量
};


struct Report
{
	std::map<string, std::string> reported_reason;//被举报原因
	string start_time = "0";
	string end_time = "0";
	int     num= 0; //被举报次数
	int m;  //用于判断举报次数是否达到处罚条件
	bool on_punishment = false;

};

extern std::map<std::string, struct User>users;
extern std::map<std::string, struct Goods>all_goods;
extern std::map<std::string, struct Order>orders;
extern std::map<std::string, std::string>adm;
extern std::map<std::string, struct Report>reported_users;
extern int count_users;
extern int count_goods;
extern int count_orders;
extern string name;
extern string pass;
extern string id;
#endif





