#ifndef EXTERN
#define EXTERN
#include <string>
#include <map>
#include <list>
using namespace std;
struct Table
{
    string table_name;              
    string column_name;
    map<string, list<string>> content;      
    map<string, int>position;       //to record where every column is, that's to say a specific column is the first column or the second column or other.
    int camount;
    int primary_key = 0;
    Table* next;
};
extern string tname;          //name of every table;
extern string cname;          //name of every column;
extern map<string, list<string>>con;   //to record the content of every table
extern map<string, int>pos;   //to record where every column is, that's to say a specific column is the first column or the second column or other.
extern list<string> lst;      // to record the content when you use "INSERT" command;
extern list<string>condition;   // to record limitaitions which behind "WHERE"
extern int pkey;                 //to record where the PRIMARY_KEY is;
extern int columns;           // how many columns;
extern int tables;
extern string nopkey;
#endif