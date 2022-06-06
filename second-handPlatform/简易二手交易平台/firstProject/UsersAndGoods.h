#pragma once
#ifndef HG_H
#define HG_H
#include "map.h"
#include <string>
using namespace std;
extern void _Buy();
extern void _ChangeUserInf();
extern void _DeleteUser();
extern void _Recharge();
extern void _RemoveGoods(const string& identity);
extern void _LanchGoods();
extern void _ChangeGoodsInf();
extern void _Helper(int i, string& str);
extern string _GetTime();
#endif
