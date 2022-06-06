#pragma once
#ifndef CAS_H
#define CAS_H
#include <string>
#include<map>
using namespace std;
#include"map.h"
extern void _CheckGoods(const string& identity);
extern void _CheckDetailedGoods();
extern void _CheckOrders(const string& identity);
extern void _CheckAllUsers();
extern void _CheckUserInf();
extern void _SearchGoods(const string& identity);
extern void _CheckReportedInf();
extern void _AdmCheckReportedInf();
#endif
