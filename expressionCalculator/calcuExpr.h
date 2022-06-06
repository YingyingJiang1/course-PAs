#ifndef CALCUEXPR
#define CALCUEXPR
#include <string>
#include <vector>
#include <map>
using namespace std;
extern string Calculate(bool &error);
extern void Init();
extern string GetStr(vector<pair<string, string>>toks);
extern void change(string str);
extern map<char, int> p;
#endif