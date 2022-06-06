#ifndef PARSE
#define PARSE
#include <string>
#include <vector>
using namespace std;
#include "def.h"
extern int Parse(const string input, struct GLOBAL& temp, struct GLOBAL* varHead, struct GLOBAL* funcHead);
extern void Def(struct GLOBAL*& head, struct GLOBAL*& tail, struct GLOBAL& temp);
extern void TakeApart(string expr, vector<pair<string, string>>& toks);
#endif
