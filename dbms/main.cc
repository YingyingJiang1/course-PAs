#include <iostream>
#include <string>
#include <map>
#include <list>
#include "Func.h"
#include "Parse.h"
using namespace std;
#include "extern.h"
#include "File.h"
string tname;          //name of every table;
string cname = "";          //name of every column;
map<string, list<string>>con;   //to record the content of every table
map<string, int>pos;   //to record where every column is, that's to say a specific column is the first column or the second column or other.
list<string> lst;      // to record the content when you use "INSERT" command;
list<string>condition;   // to record limitaitions which behind "WHERE"
int pkey = 0;                 //to record where the PRIMARY_KEY is;
int columns;           // how many columns;
int tables = 0;  //how many tables;
string nopkey = "";
int main()
{
    Table* head = NULL;
    Table* tail = NULL;
    char str[101];
    _FromFile("tables.txt", head, tail);
    _FromFile("contents.txt", head, tail);
    while(true)
    {
        cout<<"sql>";
        cin.getline(str, 300);
        if(str == "exit")
            break;
        int n ;
        n = _Parse(str);
        switch(n)
        {
            case 1:
            {
                _Creat(head, tail);
                break;
            }
            case 2:
            {
                _ShowTables(head, tail);
                break;
            }
            case 3:
            {
                _Drop(head, tail);
                break;
            }
            case 4:
            {
                _Insert(head);
                break;
            }
            case 5:
            {
                _Select(head);
                break;
            }
            case 6:
            {
                _Update(head);
                break;
            }
            case 7:
            {
                _Delete(head);
                break;
            }
            case 8:
            {
                _Alter(head,tail);
                break;
            }
            case 9:
            {
                _Count(head);
                break;
            }
            case 10:
            {
                _MyMax(head);
                break;
            }
            case 11:
            {
                _MyMin(head);
                break;
            }
            default:cout<<"Invalid instruction!"<<endl;
        }
    }
    return 0;
}