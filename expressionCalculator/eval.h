#ifndef EVALH
#define EVALH
#include <list>
#include "def.h"
using namespace std;
extern string Eval(vector<pair<string, string>>toks, struct GLOBAL* varHead, struct GLOBAL* funcHead, string env, bool& error);
extern string EvalTaylorFormula(int sequence, int  expanPoint, int power , bool &error, char ch);
#endif