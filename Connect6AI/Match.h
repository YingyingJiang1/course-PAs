#ifndef MATCH
#define MATCH
#include <iostream>
using namespace std;
pair<pair<int, int>, pair<int, int>> CanWin(int row, int col, bool& existed);
pair<pair<int, int>, pair<int, int>> NeedDefense(int row, int col, bool& existed);
pair<pair<int, int>, pair<int, int>> Attack(int row, int col, bool& existed);

#endif
