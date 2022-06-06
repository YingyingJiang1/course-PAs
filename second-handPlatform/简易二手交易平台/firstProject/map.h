#pragma once
#ifndef MAP_H
#define MAP_H
#include <map>
#include<string>
using namespace std;
struct User
{
	string	name;//�û���
	string	password;//�˺�����
	string    tel;//��ϵ��ʽ
	string   adr;  //��ַ
	float     balance = 0.0;//���
	bool	exist = true;//�û���������ж�
	std::map<int, std::string> buyer_eval ; // ��Ҷ����ҵ�����
	bool on_punishment = false;
	int num = 0;
};

struct Goods
{
	string name;	     //��Ʒ��
	float	price;	    //�۸�
	string	description;//��Ʒ����
	string 	seller;	  //����ID
	string	time_issued;//�ϼ�ʱ��
	string	condition = "������";   //��Ʒ״̬
	std::map<int, std::string> goods_evaluation ;                //�û�����Ʒ������
	int amount;
	int num = 0;
};

struct Order
{
	string	goods_id;	      //��ƷID
	float	money;	     //���׽��
	string	time_dealed; //����ʱ��
	string	seller;	     //����ID
	string	buyer;	    //���ID
	string  eval_condition = "δ����";        //����״̬�������ۡ�δ���ۣ�
	string ord_condition = "������"; //����״̬
	int amount;//������Ʒ����
};


struct Report
{
	std::map<string, std::string> reported_reason;//���ٱ�ԭ��
	string start_time = "0";
	string end_time = "0";
	int     num= 0; //���ٱ�����
	int m;  //�����жϾٱ������Ƿ�ﵽ��������
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





