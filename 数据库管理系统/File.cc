#include <iostream>
#include <string.h>
#include <fstream>
#include <iomanip>
using namespace std;
#include "extern.h"
void _FromFile(const string fname, struct Table* &head, struct Table *&tail)
{
    bool have_no_pkey = false;
    fstream fs;
    fs.open(fname);
    if(!fs)
    {
        ofstream ofs;
        ofs.open(fname, ios::app);
        ofs.close();
    }
    else
    {
        struct Table a_table;
        if(fname == "tables.txt")
        {
            string str, str1;
            int m;
            fs >> a_table.table_name >> a_table.column_name;
            for(auto it = a_table.column_name.begin(); it != a_table.column_name.end(); ++it)
            {
                if(*it == ')')
                    have_no_pkey = true;

            }
            if(!have_no_pkey)
            {
                a_table.column_name.append(" ");
                fs >> str;
                a_table.column_name.append(str);
                str.clear();
            }
            fs >> str1 >> m;
            str1.clear();
            fs >> str1 >> m;
            while(!fs.eof() && str1 != "##########################################################################")
            {                
                a_table.position[str1] = m;
                str1.clear();
                fs >> str1 >> m;
            }
            while(!fs.eof())
            {
                Table *p = new Table; 
                *p = a_table;
                p->next = NULL;
                if(head == NULL)
                    head = p;
                else
                    tail->next = p;
                tail = p;
                ++tables;       
                have_no_pkey = false; 
                a_table.position.clear();                      //need to clear map!!!(because use the same struct a_table)
                fs >> a_table.table_name >> a_table.column_name;
                for(auto it = a_table.column_name.begin(); it != a_table.column_name.end(); ++it)
                {
                if(*it == ')')
                    have_no_pkey = true;

                }
                if(!have_no_pkey)
                {
                    a_table.column_name.append(" ");
                    fs >> str;
                    a_table.column_name.append(str);
                }
                
                str.clear();
                fs >> str1 >> m;
                str1.clear();
                fs >> str1 >> m;
                while(!fs.eof() &&str1 != "##########################################################################")
                {                
                    a_table.position[str1] = m;
                    str1.clear();
                    fs >> str1 >> m;
                    
                }
            }
        }
        else if(fname == "contents.txt")
        {
            Table* h = head;
            string str1, str2;
            list<string>l;
            fs >> h->primary_key >> h->camount;
            fs >> str2;
            while(!fs.eof())
            {
                while(strcmp(str2.c_str(),"########################################################################") != 0 )
                {
                    if(h->primary_key != 0)
                    {
                        for(int i = 1; i <= h->camount; ++i)
                        {
                            if(i == h->primary_key)
                                str1 = str2;
                            else
                                l.push_back(str2);
                            if(i == h->camount)
                                break;
                            fs >> str2;
                        }
                        h->content[str1] = l;
                        l.clear();
                        fs >> str2;
                    }
                    else
                    {
                        for(int i = 1; i <= h->camount; ++i)
                        {
                            l.push_back(str2);
                            if(i == h->camount)
                                break;
                            fs >> str2;
                        }
                        nopkey.append("0");
                        h->content[nopkey] = l;
                        l.clear();
                        fs >> str2;
                    }
                }
                h = h->next;
                fs >> h->primary_key >> h->camount;
                fs >> str2;
            }
        }
    }
    fs.close();
}

void _IntoFile(const string fname, struct Table* head)
{
    ofstream fs;
    fs.open(fname);
    if(!fs)
    {
        ofstream ofs;
        ofs.open(fname, ios::app);
        ofs.close();
    }
    else
    {
        if(fname == "tables.txt")
        {
            while(head)
            {
                fs << head->table_name << ' ' << head->column_name << endl;
                fs << "##########################################################################" << ' '<<   0  << endl;
                for(auto it = head->position.begin(); it != head->position.end(); ++it)
                {
                    fs << it->first << ' ' << it->second <<' ';
                }
                fs << endl;
                fs << "##########################################################################" << ' ' <<  0 << endl;
                fs << endl;
                head = head->next;
            }
        }
        else if(fname == "contents.txt")
        {
            while(head)
            {
                fs << head->primary_key << ' ' << head->camount << endl;
                if(head->primary_key != 0)
                {
                    if(!head->content.empty())
                    {
                        for(auto it = head->content.begin(); it != head->content.end(); ++it)
                        {
                            int i = 1;         
                            auto it1 = it->second.begin();
                            while(i <= head->camount)    
                            {
                                if(i == head->primary_key)
                                    fs << setw(25) << left << it->first << ' ';
                                else
                                {
                                    fs << setw(25) << left << *it1 << ' ';
                                    ++it1;
                                }   
                                ++i;
                            }
                            fs << endl;
                        }
                        
                    }
                }
                else
                {
                    if(!head->content.empty())
                    {
                        for(auto it = head->content.begin(); it != head->content.end(); ++it)
                        {
                            for(auto it1 = it->second.begin(); it1 != it->second.end(); ++it1)
                            {
                                fs << setw(25) << left << *it1 << ' ';
                            }
                            fs << endl;
                        }
                    }
                }
                fs << "########################################################################" << endl;
                fs << endl;
                head = head->next;
            }
        }
    }
    fs.close();
}