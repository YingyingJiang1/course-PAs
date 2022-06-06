#ifndef DEFH
#define DEFH
#include <string>
#include <vector>
using namespace std;
struct GLOBAL
{
    vector<pair<string, string >> toks;   //take apart expressions; 
    vector<pair<string, string>> args;  // concrete variables values; first string is name, second string is value
    char name[13];    //the name of functions or variable values
    string type;    //func or var
    GLOBAL* next;

};

#endif
