#include <iostream>
#include <string.h>
#include <iomanip>
using namespace std;
#include "extern.h"
#include "File.h"
bool _ForWhere(map<string, list<string>>::iterator &content_it, struct Table*&h, bool & stop);
void _Creat(Table* &head, Table* &tail)
{
    bool found = false;
    Table* h = head;
    while(h)
    {
        if(strcmp((h->table_name).c_str(), tname.c_str()) == 0)
        {
            found = true;
            break;
        }
        h = h->next;
    }
    if(!found)
    {
        Table* p = new Table;
        p->next = NULL;
        p->camount = columns;
        p->column_name = cname;
        for(auto it = pos.begin(); it != pos.end(); ++it)
        {
            p->position[it->first] = it->second;
        }
        p->primary_key = pkey;
        p->table_name = tname;
        tname.clear();
        cname.clear();
        if(head == NULL)
            head = p;
        else
            tail->next = p;
        tail = p;
        ++tables;
        _IntoFile("tables.txt", head);
        _IntoFile("contents.txt", head);
        cout << "Create successfully!" << endl;
    }
    else 
        cout << "Create failed! The table " << "\"" << tname << "\"" << "is existed!" << endl;
    cname.clear();
    pos.clear();
}

void _ShowTables(struct Table* &head, struct Table* &tail)
{
    Table* h = head;
    if(h == NULL)
        cout << "0 table(s):" << endl;
    else
    {
        cout << tables << "table(s):" << endl;
        while(h)
        {
            cout << h->table_name << h->column_name << endl;
            h = h->next;
        }
    }
}

void _Drop(struct Table* &head, struct Table*& tail)
{
    bool found = false;
    Table* cur = head, *pre = cur;
    if(head == NULL)
        cout << "Drop failed! Because the table isn't existed!" <<endl;
    else
    {
        while(cur)
        {
            if(strcmp((cur->table_name).c_str(), tname.c_str()) == 0)
            {
                if(cur == head)
                {
                    head = cur->next;
                    cur->next = NULL;
                    delete(cur);
                }
                else
                {
                    if(cur == tail)
                        tail = pre;
                    pre->next = cur->next;
                    cur->next = NULL;
                    delete(cur);
                }
                found = true;
                --tables;
                _IntoFile("tables.txt", head);
                _IntoFile("contents.txt", head);
                cout << "Drop successfully!" << endl;
                break;
            }
            pre = cur;
            cur = cur->next;
        }
        if(!found)
            cout << "Drop failed! Because the table isn't existed!" <<endl;
    }
}

void _Insert(struct Table* &head)
{
    bool found = false;
    Table* h = head;
    while(h)
    {
        if(strcmp((h->table_name).c_str(), tname.c_str()) == 0)
        {
            found = true;
            if(lst.size() == h->camount)
            {
                int i = 1;
                for(auto it = lst.begin(); it != lst.end(); ++it)
                {
                    if(h->primary_key != 0)
                    {
                        if(i == h->primary_key)
                        {
                            if(h->content.find(*it) == h->content.end())
                            {
                                string s = *it;
                                lst.erase(it);
                                h->content[s] = lst;
                                _IntoFile("contents.txt", head);
                                cout << "Insert successfully!" << endl;                            
                                break;
                            }
                            else
                            {
                                cout << "Insert failed! The value of the primary key can not repeat!" << endl;                           
                                break;
                            }

                        }
                        ++i;
                    }
                    else
                    {
                        nopkey.append("0");
                        h->content[nopkey] = lst;
                        _IntoFile("contents.txt", head);
                        cout << "Insert successfully!" << endl;                            
                        break;
                    }
                }
            }
            else
            {
                cout << "Insert failed! Because the columns do not match!" << endl;
                break;
            }
        }
        h = h->next;
    }
    if(!found)
        cout << "Insert failed! Because the table isn't existed!" << endl;
    lst.clear();
    
}

void _Select(struct Table* &head)
{
    Table* h = head;
    bool found = false, judg = false, for_and = false, column_head = false, stop = false, have_printed = false;
    int n;
    while(h)
    {
        if(strcmp((h->table_name).c_str(), tname.c_str()) == 0)
        {   
            found = true;
            break;
        }
        h = h->next;
    }
    if(found)
    {
        auto it = lst.begin();
        if(0 == strcmp((*it).c_str(), "DISTINCT"))
        {
            if(!h->content.empty())
            {
                ++it;
                list<string>for_print;
                string mystr; //to record all columns of every row;
                if(strcmp((*it).c_str(), "*") == 0)
                {
                    if(condition.empty())
                    {
                        for(auto content_it = h->content.begin(); content_it != h->content.end(); ++content_it)
                        {
                            int i = 1;
                            auto con_lst_it = content_it->second.begin();
                            while(i <= h->camount)
                            {
                                if(i == h->primary_key)
                                    mystr.append(content_it->first + "\t");
                                else
                                {
                                    mystr.append(*con_lst_it + "\t");
                                    ++con_lst_it;
                                }
                                ++i;
                            }
                            for_print.push_back(mystr);
                            mystr.clear();
                        }
                        for_print.sort();
                        for_print.unique();
                        for(auto print_it = for_print.begin(); print_it != for_print.end(); ++print_it)
                        {
                            have_printed = true;
                            if(!column_head)
                            {
                                int ii = 1;                        
                                while(ii <= h->camount)
                                {
                                    for(auto position_it = h->position.begin(); position_it != h->position.end(); ++position_it)
                                    {
                                        if(ii == position_it->second)
                                        {
                                            cout << position_it->first << '\t';
                                            ++ii;
                                            break;
                                        }
                                    }
                            
                                }
                                cout << endl;   
                                column_head = true;
                            }
                            cout << *print_it << endl;
                        }
                    }
                    else
                    {
                        for(auto content_it = h->content.begin(); content_it != h->content.end(); ++content_it)
                        {
                            int i = 1;
                            auto con_lst_it = content_it->second.begin();
                           judg =  _ForWhere(content_it, h, stop);
                           if(stop)
                                break;
                           if(judg)
                            {
                                if(!column_head)
                                {
                                    for(auto iter = h->position.begin(); iter != h->position.end(); ++iter)
                                    {
                                        cout << iter->first << "\t" ;
                                    }
                                    cout << endl;
                                    column_head = true;
                                }
                                while(i <= h->camount)
                                {
                                    if(i == h->primary_key)
                                        mystr.append(content_it->first + "\t");
                                    else
                                    {
                                        mystr.append(*con_lst_it + "\t");
                                        ++con_lst_it;
                                    }
                                    ++i;
                                }
                                for_print.push_back(mystr);
                                mystr.clear();
                            }
                        }
                        if(!for_print.empty())
                        {
                            have_printed = true;
                            for_print.sort();
                            for_print.unique();
                            for(auto print_it = for_print.begin(); print_it != for_print.end(); ++print_it)
                                cout << *print_it << endl;
                        }  
                        else if(!stop)
                            cout << "No values that match the condition!" << endl;
                    }
                }
                else
                {
                    bool columns_existed = true, once = false;
                    for(auto lst_it = lst.begin(); lst_it != lst.end(); ++lst_it)
                    {
                        if(!once)
                        {
                            ++lst_it;
                            once = true;
                        }
                        auto it = h->position.find(*lst_it);
                        if(it == h->position.end())
                        {
                            columns_existed = false;
                            cout << "The column " << "\"" << *lst_it << "\"" << "is not existed!" << endl;
                            break;
                        }
                    }
                    if(columns_existed)
                    {
                        if(!h->content.empty())
                        {
                            if(condition.empty())
                            {
                                once = false;
                                for(auto lst_it = lst.begin(); lst_it != lst.end(); ++lst_it)
                                {
                                    if(!once)
                                    {
                                        ++lst_it;
                                        once = true;
                                    }
                                    cout << *lst_it << "\t";
                                }
                                cout << endl;
                                for(auto content_it = h->content.begin(); content_it != h->content.end(); ++content_it)
                                {
                                    for(auto lst_it = lst.begin(); lst_it != lst.end(); ++lst_it)
                                    {
                                        int j = 1;
                                        if(!once)
                                        {
                                            ++lst_it;
                                            once = true;
                                        }
                                        auto it = h->position.find(*lst_it);
                                        if(it->second == h->primary_key)
                                        mystr.append(content_it->first +"\t");
                                        else
                                        {
                                            int k = it->second;                                                    
                                            if(it->second > h->primary_key)
                                                 --k;
                                            for(auto it1 = content_it->second.begin(); it1 != content_it->second.end(); ++it1)
                                            {
                                                if(j == k)
                                                {       
                                                    mystr.append(*it1 +"\t");
                                                    break;
                                                }
                                                ++j;
                                            }
                                        }
                                    }
                                    for_print.push_back(mystr);
                                    mystr.clear();
                                   
                                }
                                for_print.sort();
                                for_print.unique();
                                for(auto print_it = for_print.begin(); print_it != for_print.end(); ++print_it)
                                {
                                    have_printed = true;                                    
                                    cout << *print_it << endl;
                                }
                                cout << endl;
                            }                     
                            else
                            {
                                once = false;
                                for(auto content_it = h->content.begin(); content_it != h->content.end(); ++content_it)
                                {
                                    int i = 1;
                                    auto con_lst_it = content_it->second.begin();
                                    judg = _ForWhere(content_it, h, stop);
                                    if(stop)
                                        break;                                    
                                    if(judg)
                                    {                                        
                                        for(auto lst_it = lst.begin(); lst_it != lst.end(); ++lst_it)
                                        {
                                            int j = 1;
                                            if(!once)
                                            {
                                                ++lst_it;
                                                once = true;
                                            }
                                            auto it = h->position.find(*lst_it);
                                            if(it->second == h->primary_key)
                                                mystr.append(content_it->first +"\t");
                                            else
                                            {
                                                int k = it->second;                                                    
                                                if(it->second > h->primary_key)
                                                    --k;
                                                for(auto it1 = content_it->second.begin(); it1 != content_it->second.end(); ++it1)
                                                {
                                                    if(j == k)
                                                    {       
                                                        mystr.append(*it1 +"\t");
                                                            break;
                                                    }
                                                    ++j;
                                                }
                                            }
                                        }
                                        for_print.push_back(mystr);
                                        mystr.clear();
                                    }                                    
                                }
                                if(!for_print.empty())
                                {
                                    once = false;
                                    if(!column_head)
                                        {
                                            for(auto lst_it = lst.begin(); lst_it != lst.end(); ++lst_it)
                                            {
                                                if(!once)
                                                {
                                                    ++lst_it;
                                                    once = true;
                                                }
                                                cout << *lst_it << "\t";
                                            }
                                            cout << endl;
                                            column_head = true;
                                        }
                                    for_print.sort();
                                    for_print.unique();
                                    for(auto print_it = for_print.begin(); print_it != for_print.end(); ++print_it)
                                        cout << *print_it << endl;
                                }
                                else if(!stop)
                                    cout << "No values that match the condition!" << endl;
                            }

                        }
                        else
                            cout << "The table is empty!" << endl;
                    }
                }
            }
            else
                cout << "The table is empty!" << endl;

        }
        else
        {
            if(!h->content.empty())
            {
                if(strcmp((*it).c_str(), "*") == 0)
                {
                    if(condition.empty())
                    {
                        int ii = 1;                        
                        while(ii <= h->camount)
                        {
                            for(auto position_it = h->position.begin(); position_it != h->position.end(); ++position_it)
                            {
                                if(ii == position_it->second)
                                {
                                    cout << position_it->first << '\t';
                                    ++ii;
                                    break;
                                }
                            }
                            
                        }
                        cout << endl;                
                        for(auto it2 = h->content.begin(); it2 != h->content.end(); ++it2)
                        {
                            int i = 1;
                            auto it3 = it2->second.begin();
                            while(i <= h->camount)
                            {
                                if(i == h->primary_key)
                                    cout << it2->first << '\t';
                                else
                                {   
                                    cout << *it3 << '\t';
                                    ++it3;
                                }
                                ++i;
                            }
                            cout << endl;
                        }
                    }
                    else
                    {
                        for(auto content_it = h->content.begin(); content_it != h->content.end(); ++content_it)
                        {
                            int i = 1;
                            auto con_lst_it = content_it->second.begin();
                            judg = _ForWhere(content_it, h, stop);
                            if(stop)
                                break;
                            if(judg)
                            {
                                have_printed = true;
                                if(!column_head)
                                {
                                    for(auto it1 = h->position.begin(); it1 != h->position.end(); ++it1)
                                    {
                                        cout << it1->first << '\t';
                                    }
                                    cout << endl;
                                    column_head = true;
                                }
                                while(i <= h->camount)
                                {
                                    if(i == h->primary_key)
                                        cout << content_it->first << '\t';
                                    else
                                    {
                                        cout << *con_lst_it << '\t';
                                        ++con_lst_it;
                                    }
                                    ++i;
                                }
                                cout << endl;
                            }                            
                        }
                        if(!stop && !have_printed)
                                cout << "No values that match the condition!" << endl;
                    }
                }
                else
                {
                    bool columns_existed = true;
                    for(auto lst_it = lst.begin(); lst_it != lst.end(); ++lst_it)
                    {
                        auto it = h->position.find(*lst_it);
                        if(it == h->position.end())
                        {
                            columns_existed = false;
                            cout << "The column " << "\"" << *lst_it << "\"" << "is not existed!" << endl;
                            break;
                        }
                    }
                    if(columns_existed)
                    {
                        if(condition.empty())
                        {
                            for(auto lst_it = lst.begin(); lst_it != lst.end(); ++lst_it)
                            {
                                cout << *lst_it << "\t";
                            }
                            cout << endl;
                            for(auto content_it = h->content.begin(); content_it != h->content.end(); ++content_it)
                            {
                                for(auto lst_it = lst.begin(); lst_it != lst.end(); ++lst_it)
                                {
                                    auto it = h->position.find(*lst_it);
                                    if(it->second == h->primary_key)
                                        cout << content_it->first << "\t";
                                    else
                                    {
                                        int k = it->second;
                                        int j = 1;
                                        if(it->second > h->primary_key)
                                            --k;
                                        for(auto it1 = content_it->second.begin(); it1 != content_it->second.end(); ++it1)
                                        {
                                            if(j == k)
                                            {
                                                cout << *it1 << "\t";
                                                break;
                                            }
                                            ++j;
                                        }
                                        
                                    }
                                }
                                cout << endl;
                            }                       
                        }
                        else
                        {
                            for(auto content_it = h->content.begin(); content_it != h->content.end(); ++content_it)
                            {
                                int i = 1;
                                auto con_lst_it = content_it->second.begin();
                                judg = _ForWhere(content_it, h, stop);
                                if(stop)
                                    break;
                                if(judg)
                                {
                                    have_printed = true;
                                    if(!column_head)
                                    {
                                        for(auto lst_it = lst.begin(); lst_it != lst.end(); ++lst_it)
                                        {
                                            cout << *lst_it << "\t";
                                        }
                                        cout << endl;
                                        column_head = true;
                                    }
                                    for(auto lst_it = lst.begin(); lst_it != lst.end(); ++lst_it)
                                    {
                                        auto it = h->position.find(*lst_it);
                                        if(it->second == h->primary_key)
                                            cout << content_it->first << "\t";
                                        else
                                        {
                                            int k = it->second;
                                            int j = 1;
                                            if(it->second > h->primary_key)
                                               --k;
                                                for(auto it1 = content_it->second.begin(); it1 != content_it->second.end(); ++it1)
                                                {
                                                    if(j == k)
                                                    {       
                                                        cout << *it1 << "\t";
                                                        break;
                                                    }
                                                    ++j;
                                                }
                                        
                                        }
                                    }
                                    cout << endl;
                                }
                            }
                            if(!stop && !have_printed)
                                cout << "No values that match the condition!" << endl;
                        }
                    }
                }
            }
            else
                cout << "The table is empty!" << endl;

        }
    }
    else
        cout << "The table is not existed!" << endl;
    lst.clear();
    condition.clear();
}

void _Update(struct Table*&head)
{
    Table* h = head;
    bool found = false, judg = false, stop = false, updated = false;
    map<string, list<string>>::iterator c_it;
    int count = 0;
    while(h)
    {
        if(strcmp((h->table_name).c_str(), tname.c_str()) == 0)
        {
            found = true;
            break;
        }
        h = h->next;
    }
    if(found)
    {
        if(!h->content.empty())
        {
            if(condition.empty())
            {
                auto lst_it = lst.begin();
                char s[100];
                sscanf((*lst_it).c_str(), "%[^=]", s);
                auto it = h->position.find(s);
                if(it != h->position.end())
                {
                    sscanf((*lst_it).c_str(), "%*[^=]%*1s%s", s);
                    for(auto content_it = h->content.begin(); content_it != h->content.end(); ++content_it )
                    {
                        if(it->second == h->primary_key)
                        {
                            auto find_it = h->content.find(s);
                            if(find_it == h->content.end() && h->content.size() == 1)
                            {
                                auto it1 = h->content.begin();
                                h->content[s] = it1->second;
                                h->content.erase(it1);
                                cout << "Update successfully!"<<endl;
                                _IntoFile("contents.txt",head);
                                break;
                            }
                            else
                            {
                                cout << "The value of \" primary_key \" can not be repeated!" << endl;
                                break;
                            }
                        }
                        else
                        {
                            int k = it->second;
                            if(it->second > h->primary_key)
                                --k;
                            int j = 1;
                            for(auto con_lst_it = content_it->second.begin(); con_lst_it != content_it->second.end(); ++con_lst_it)
                            {
                                if(j == k)
                                {
                                    *con_lst_it = s;
                                    _IntoFile("contents.txt", head);
                                    updated = true;
                                    break;
                                }
                                ++j;
                            }
                        }
                    }
                    if(updated)
                        cout << "Update successfully!"<<endl;
                }
                else 
                    cout << "The column " << "\"" << s << "\"" << "is not existed!" << endl;
            }
            else
            {
                char setnew[100];
                auto lst_it = lst.begin();
                sscanf((*lst_it).c_str(), "%[^=]", setnew);
                auto find_it = h->position.find(setnew);
                sscanf((*lst_it).c_str(), "%*[^=]%*1s%s", setnew);
                if(find_it != h->position.end())
                {
                    for(auto content_it = h->content.begin(); content_it != h->content.end(); ++content_it)
                    {
                        judg = _ForWhere(content_it, h, stop);
                        if(stop)
                            break;
                        if(judg)
                        {
                            ++count;
                            if(find_it->second == h->primary_key)
                            {
                                c_it = content_it;
                            }
                            if(find_it->second != h->primary_key)                                       
                            {
                                int k = find_it->second;
                                if(k > h->primary_key)
                                    --k;
                                int j = 1;
                                for(auto iter = content_it->second.begin(); iter != content_it->second.end(); ++iter)
                                {
                                    if(j == k)
                                    {
                                        *iter = setnew;
                                        updated = true;
                                        _IntoFile("contents.txt", head);                                        
                                        break;
                                    }
                                    ++j;
                                }
                            }
                        }
                    }
                    if(updated)
                        cout << "Update successfully!"<<endl;
                    if(!updated && !stop)
                    {
                        if(find_it->second == h->primary_key)
                        {
                            if(h->content.find(setnew) == h->content.end())
                            {
                                if(count == 1)
                                {
                                    h->content[setnew] = c_it->second;
                                    h->content.erase(c_it);
                                    _IntoFile("contents.txt", head);
                                    cout << "Update successfully!" << endl;
                                }
                                else if(count > 1)
                                    cout << "The value of primary key cann't be repeated!" << endl;
                                else if(count == 0)
                                    cout << "No value that matches the condition!" << endl;
                            }
                            else
                                cout << "The value of primary key cann't be repeated!" << endl;
                        }
                        else
                            cout << "No value that matches the condition!" << endl;
                    }
                }
                else
                    cout << "The column " << "\"" << setnew << "\"" << "is not existed!" << endl;          

            }
        }
        else
            cout << "Update failed! The table is empty!" << endl;
    }
    else
        cout << "The table is not existed!" << endl;
    lst.clear();
    condition.clear();

}

void _Delete(struct Table*&head)
{
    struct Table* h = head;
    bool found = false, stop = false, judg = false, match_condition = false, deleted = false;
    while(h)
    {
        if(strcmp((tname).c_str(), (h->table_name).c_str()) == 0)
        {
            found = true;
            break;
        }
        h = h->next;
    }
    if(found)
    {
        if(condition.empty())
        {
           if(!h->content.empty())
           {
                h->content.clear();
                _IntoFile("contents.txt", head);
                cout << "Delete successfully!" << endl;
           }
           else
               cout << "Delete failed! The table is empty!" << endl; 
        }
        else
        {
            if(!h->content.empty())
            {
                for(auto content_it = h->content.begin(); content_it != h->content.end(); )
                {
                    judg = _ForWhere(content_it, h, stop);
                    if(stop)
                        break;
                    if(judg)
                    {
                        match_condition = true;
                        h->content.erase(content_it++);
                        deleted = true;
                    }
                    else
                        ++content_it;
                }
                if(!stop && !match_condition)
                    cout << "Delete failed! No values that match the condition!" << endl;
            }
            else
                cout << "Delete failed! The table is empty!" << endl;
            if(deleted)
                cout << "Delete successfully!" << endl;
        }
    }
    else
        cout << "The table is not existed!" << endl;
    if(deleted)
        _IntoFile("contents.txt", head);
    lst.clear();
    condition.clear();
}

bool _ForWhere(map<string, list<string>>::iterator &content_it, struct Table*&h, bool & stop)
{
    auto condition_it = condition.begin();
    bool judg = false, for_and = false;
    char s[100], ss[100], s1[100], s2[100];
    strcpy(s1, (*condition_it).c_str());
    ++condition_it;
    if(condition_it == condition.end())
    {
        sscanf(s1, "%[^=]", s);
        auto it5 = h->position.find(s);
        if(it5 != h->position.end())
        {
            sscanf(s1, "%*[^=]%*1s%s", s);
            int i = 1;
            auto con_lst_it = content_it->second.begin();
            if(it5->second == h->primary_key)
            {
                if(0 == strcmp(s, (content_it->first).c_str()))
                    judg = true;
            }
            else
            {
                int k = it5->second;
                int j = 1;
                if(it5->second > h->primary_key)
                    --k;
                for(auto it7 = content_it->second.begin(); it7 != content_it->second.end(); ++it7)
                {
                    if(j == k)
                    {
                        if(0 == strcmp((*it7).c_str(), s))
                        {
                            judg = true;
                            break;
                        }
                    }
                    ++j;
                }
            }
        }
        else
        {
            cout << "The column " << "\"" << s << "\"" << "is not existed!" << endl;
            stop = true;
        }
    }
    else
    {
        if(0 ==strcmp((*condition_it).c_str(), "AND"))
        {
            ++condition_it;
            strcpy(s2, (*condition_it).c_str());
            sscanf(s1, "%[^=]", s);
            sscanf(s2, "%[^=]", ss);
            auto it5 = h->position.find(s); 
            auto it55 = h->position.find(ss);
            if(it5 != h->position.end())
                if(it55 != h->position.end())
                {
                    sscanf(s1, "%*[^=]%*1s%s", s);
                    sscanf(s2, "%*[^=]%*1s%s", ss);
                    
                        int i = 1;
                        auto con_lst_it = content_it->second.begin();
                        if(it5->second == h->primary_key)
                        {
                            if(0 == strcmp(s, (content_it->first).c_str()))
                                for_and = true;
                        }
                            else
                            {
                                int k = it5->second;
                                if(it5->second > h->primary_key)
                                    --k;
                                int j = 1;
                                for(auto it7 = content_it->second.begin(); it7 != content_it->second.end(); ++it7)
                                {
                                    if(j == k)
                                    {
                                        if(0 == strcmp(s, (*it7).c_str()))
                                        {
                                            for_and = true;
                                            break;
                                        }                                                        
                                    }
                                    ++j;
                                }
                            }
                            if(for_and)
                            {
                                if(it55->second == h->primary_key)
                                {
                                    if(0 == strcmp(ss, (content_it->first).c_str()))
                                        judg = true;
                                }
                                    else
                                    {
                                        int k = it55->second;
                                        if(it55->second > h->primary_key)
                                            --k;
                                        int j = 1;
                                        for(auto it7 = content_it->second.begin(); it7 != content_it->second.end(); ++it7)
                                        {
                                            if(j == k)
                                            {
                                                if(0 == strcmp(ss, (*it7).c_str()))
                                                {
                                                    judg = true;
                                                    break;
                                                }                                                        
                                            }
                                            ++j;
                                        }
                                    }
                            }
                    
                }
                else
                {
                    cout << "The column " << "\"" << ss << "\"" << "is not existed!" << endl;
                    stop = true;
                }
            else
            {
                cout << "The column " << "\"" << s << "\"" << "is not existed!" << endl;
                stop = true;
            }
        }
        else if(0 == strcmp((*condition_it).c_str(), "OR"))
        {
            ++condition_it;
            strcpy(s2, (*condition_it).c_str());
            sscanf(s1, "%[^=]", s);
            sscanf(s2, "%[^=]", ss);
            auto it5 = h->position.find(s); 
            auto it55 = h->position.find(ss);
            if(it5 != h->position.end())
                if(it55 != h->position.end())
                {
                    sscanf(s1, "%*[^=]%*1s%s", s);
                    sscanf(s2, "%*[^=]%*1s%s", ss);
                    
                        int i = 1;
                        auto con_lst_it = content_it->second.begin();
                        if(it5->second == h->primary_key)
                        { 
                            if(0 == strcmp(s, (content_it->first).c_str()))
                                judg = true;
                            else
                            {
                                if(it55->second == h->primary_key)
                                { 
                                    if(0 == strcmp(ss, (content_it->first).c_str()))
                                        judg = true;
                                }
                                    else
                                    {
                                        int k = it55->second;
                                        if(it55->second > h->primary_key)
                                            --k;
                                        int j = 1;                                                        
                                        for(auto it7 = content_it->second.begin(); it7 != content_it->second.end(); ++it7)
                                        {
                                            if(j == k)
                                            {
                                                if(0 == strcmp(ss, (*it7).c_str()))
                                                {
                                                    judg = true;
                                                    break;
                                                }                                                        
                                            }
                                            ++j;
                                        }
                                    }
                            }
                        }
                        else
                        {
                            int k = it5->second;
                            if(it5->second > h->primary_key)
                                --k;
                            int j = 1;
                            auto it7 = content_it->second.begin();
                            for(; it7 != content_it->second.end(); ++it7)
                            {
                                if(j == k)
                                {
                                    if(0 == strcmp(s, (*it7).c_str()))
                                    {
                                        judg = true;
                                        break;
                                    }                                                        
                                }
                                ++j;
                            }
                            if(it7 == content_it->second.end())
                                            {
                                                if(it55->second == h->primary_key)
                                                {
                                                     if(0 == strcmp(ss, (content_it->first).c_str()))
                                                        judg = true;
                                                }
                                                else
                                                {
                                                    int k = it55->second;
                                                    if(it55->second > h->primary_key)
                                                        --k;
                                                    int j = 1;
                                                    for(auto it7 = content_it->second.begin(); it7 != content_it->second.end(); ++it7)
                                                    {
                                                        if(j == k)
                                                        {
                                                            if(0 == strcmp(ss, (*it7).c_str()))
                                                            {
                                                                judg = true;
                                                                break;
                                                            }   
                                                        } 
                                                        ++j;
                                                    }
                                                }
                                            }
                        }
                    
                }
                else
                {
                    cout << "The column " << "\"" << ss << "\"" << "is not existed!" << endl;
                    stop = true;
                }
            else
            {
                cout << "The column " << "\"" << s << "\"" << "is not existed!" << endl;
                stop = true;
            }
        }
    }
    return judg;
}

void _Alter(struct Table* &head, struct Table* &tail)
{
    Table* h = head;
    bool found = false;
    while(h)
    {
        if(0 == strcmp((h->table_name).c_str(), tname.c_str()))
        {
            found = true;
            break;
        }
        h = h->next;
    }
    if(found)
    {
        auto lst_it = lst.begin();
        if(*lst_it == "ADD")
        {
            if(h->position.find(cname) == h->position.end() )
            {
                ++h->camount;
                for(auto it = h->column_name.begin(); it != h->column_name.end(); )
                {
                    if(*it == ')')
                        h->column_name.erase(it);
                    else
                        ++it;
                }
                h->column_name.append(',' + cname + ')');
                int m = h->position.size();
                ++m;
                h->position[cname] = m;
                for(auto it = h->content.begin(); it != h->content.end(); ++it)
                {
                    it->second.push_back("");
                }
                _IntoFile("tables.txt", head);
                _IntoFile("contents.txt", head);
                cout << "Alter successfully!" << endl;
            }
            else
                cout << "Alter failed! The column " << "\"" << cname << "\"" << "is existed!" << endl;
        }
        else if(*lst_it == "DROP")
        {
            bool deleted = false;
            auto find_it = h->position.find(cname);
            int count = 0, m;
            if(find_it != h->position.end())
            {
                --h->camount;             
                if(find_it->second == 1)                                                                         //**
                {
                    auto it = h->column_name.begin();
                    ++it;
                    while(*it!= ',')
                    {
                        h->column_name.erase(it);
                    }
                    h->column_name.erase(it);
                }
                else
                {
                    for(auto it = h->column_name.begin(); it != h->column_name.end(); ++it)                        //change column_name;
                    {
                        
                        if(*it == ',')
                            ++count;
                        if(count + 1 == find_it->second)
                        {
                            deleted = true;
                            h->column_name.erase(it);
                            while(*it != ',' && *it != ')')
                            {
                                h->column_name.erase(it);
                            }
                            
                        }
                        if(deleted)
                            break;
                    }
                }                                                                                                //**
                if(find_it->second == h->primary_key)
                {
                    h->primary_key = 0;
                    for(auto it = h->content.begin(); it != h->content.end(); )
                    {
                        nopkey.append("0");
                        h->content[nopkey] = it->second;
                        h->content.erase(it++);
                    }
                }
                else
                {                    
                    if(h->primary_key > find_it->second)
                        --h->primary_key;   
                    for(auto it = h->content.begin(); it != h->content.end(); ++it)
                    {
                        int i = 1;                                                          //change content
                        for(auto it1 = it->second.begin(); it1 != it->second.end();)
                        {
                            if(i == find_it->second)
                            {
                                it->second.erase(it1);
                                break;
                            }
                            if(i != h->primary_key)
                                ++it1;
                            ++i;

                        }

                    }
                }                
                m = find_it->second;                                                                                           //**
                h->position.erase(find_it);
                for(auto it = h->position.begin(); it != h->position.end(); ++it)
                {                                                                                                                          //change h->position;
                    if(it->second > m)
                        --it->second;
                }                                                                                                                      //**
                _IntoFile("tables.txt", head);
                _IntoFile("contents.txt", head);
                cout << "Alter successfully!" << endl;
            }
            else
                cout << "Alter failed! The column " << "\"" << cname << "\"" << "is not existed!" << endl; 
        }

    }
    else
        cout << "The table " << "\"" << tname << "\"" << "is not existed!" << endl;
    cname.clear();
    lst.clear();
}

void _Count(struct Table*&head)
{
    Table* h = head;
    bool found = false, judg = false, stop = false, column_head = false, printed = false, need_print = false;
    while(h)
    {
        if(strcmp((h->table_name).c_str(), tname.c_str()) == 0)
        {
            found = true;
            break;
        }
        h = h->next;
    }
    if(found)
    {
        bool equal = false;
        auto column_it = lst.begin();
        char str[100];
        for(auto it = (*column_it).begin(); it != (*column_it).end(); ++it)
        {
            if(*it == '=')
                equal = true;
        }
        if(equal)
        {                  
            int count = 0;                                                                                            //exist "="
            sscanf((*column_it).c_str(), "%[^=]", str);
            auto find_it = h->position.find(str);
            if(find_it != h->position.end())
            {
                sscanf((*column_it).c_str(), "%*[^=]%*1s%s", str);
                if(condition.empty())
                {
                    for(auto it = h->content.begin(); it != h->content.end(); ++it)
                    {
                        int i = 1;
                        auto it1 = it->second.begin();
                        if(find_it->second == h->primary_key)
                        {
                            if(it->first == str)
                            {
                                printed = true;
                                cout << setw(20) << left << find_it->first << setw(20) << left << "COUNT" << endl;  
                                cout << setw(20) << left << str << setw(20) << left << 1 << endl;
                                break;
                            }
                        }
                        else
                        {
                            while( i <= h->camount)
                            {
                                
                                if(i == find_it->second)
                                {
                                    if(*it1 == str)
                                    {
                                        need_print = true;
                                        ++count;
                                        break;
                                    }
                                }                                
                                if(i != h->primary_key)
                                    ++it1;                                
                                ++i;
                            }
                        }                    
                    }
                }
                else
                {
                    for(auto it = h->content.begin(); it != h->content.end(); ++it)
                    {
                        int i = 1;
                        auto it1 = it->second.begin();
                        judg = _ForWhere(it, h, stop);
                        if(stop)
                            break;
                        if(judg)
                        {
                            if(find_it->second == h->primary_key)
                        {
                            if(it->first == str)
                            {
                                printed = true;
                                cout << setw(20) << left << find_it->first << setw(20) << left << "COUNT" << endl;  
                                cout << setw(20) << left << str << setw(20) << left << 1 << endl;
                                break;
                            }
                        }
                        else
                        {
                            while( i <= h->camount)
                            {
                                if(i == find_it->second)
                                {
                                    if(*it1 == str)
                                    {
                                        need_print = true;
                                        ++count;
                                        break;
                                    }
                                }                                
                                if(i != h->primary_key)
                                    ++it1;                                
                                ++i;
                            }
                        }         
                        }
                    }
                }
                if(!printed && !need_print)
                    cout << "No value that satisfies the condition was found!" << endl;
                if(need_print)
                {
                    cout << setw(20) << left << find_it->first << setw(20) << left << "COUNT" << endl;  
                    cout << setw(20) << left << str << setw(20) << left << count << endl;
                }
            }
            else
                cout << "The column " << "\"" << str << "\"" << "is not existed!" << endl;
        }
        else
        {
            auto find_it = h->position.find(*column_it);
            if(find_it != h->position.end())
            {
                if(!h->content.empty())
                {
                    map<string ,int>newmap;
                    if(condition.empty())
                    {
                        cout << setw(20) << left << *column_it << setw(20) << left << "COUNT" << endl;                        
                        for(auto it = h->content.begin(); it != h->content.end(); ++it)
                        {
                            int i = 1;
                            auto it1 = it->second.begin();
                            while( i <= h->camount)
                            {
                                if(find_it->second == h->primary_key)
                                {
                                    auto new_it = newmap.find(it->first);
                                    if(new_it == newmap.end())
                                    {
                                        newmap[it->first] = 1;
                                    }
                                    else
                                        ++(new_it->second);
                                    break;
                                }
                                else
                                {
                                    if(i == find_it->second)
                                    {
                                        auto new_it = newmap.find(*it1);
                                        if(new_it == newmap.end())
                                        {
                                            newmap[*it1] = 1;
                                        }
                                        else
                                            ++(new_it->second);
                                        break;
                                    }
                                    if(i != h->primary_key)
                                        ++it1;                                    
                                    ++i;
                                }                                
                            }
                        }
                    }
                    else
                    {                        
                        for(auto it = h->content.begin(); it != h->content.end(); ++it)
                        {
                            judg = _ForWhere(it, h, stop);
                            if(stop)
                                break;
                            if(judg)
                            {
                                printed = true;
                                if(!column_head)
                                {
                                    cout << setw(20) << left << *column_it << setw(20) << left << "COUNT" << endl;
                                    column_head = true;
                                }
                                int i = 1;
                            auto it1 = it->second.begin();
                            while( i <= h->camount)
                            {
                                if(find_it->second == h->primary_key)
                                {
                                    auto new_it = newmap.find(it->first);
                                    if(new_it == newmap.end())
                                    {
                                        newmap[it->first] = 1;
                                    }
                                    else
                                        ++(new_it->second);
                                    break;
                                }
                                else
                                {
                                    if(i == find_it->second)
                                    {
                                        auto new_it = newmap.find(*it1);
                                        if(new_it == newmap.end())
                                        {
                                            newmap[*it1] = 1;
                                        }
                                        else
                                            ++(new_it->second);
                                        break;
                                    }
                                    if(i != h->primary_key)
                                        ++it1;                                    
                                    ++i;
                                }                                
                            }
                            }
                        }
                        if(!stop && !printed)
                            cout << "No values that match the condition!" << endl;
                    }
                    if(!newmap.empty())
                    {
                        for(auto it = newmap.begin(); it != newmap.end(); ++it)
                        {
                            cout << setw(20) << left << it->first << setw(20) << left << it->second << endl;
                        }
                    }
                }
                else   
                    cout << "The table is empty!" << endl;
            }
            else
                cout << "The column " << "\"" << *column_it << "\"" << "is not existed!" << endl;
        }
    }
    else
        cout << "The table " << "\"" << tname << "\"" << "is not existed!" << endl;
    lst.clear();
    condition.clear();
}

void _MyMax(struct Table*& head)
{
    Table* h = head;
    bool found = false, stop = false, have = false;
    while(h)
    {
        if(h->table_name == tname)
        {
            found = true;
            break;
        }
        h = h->next;
    }
    if(found)
    {
        bool judg = false;
        auto lst_it = lst.begin();
        auto find_it = h->position.find(*lst_it);
        if(find_it != h->position.end())
        {
            if(!h->content.empty())
            {
                string max_string;
                if(condition.empty())
                {
                    have = true;
                    for(auto it = h->content.begin(); it != h->content.end();++it)
                    {
                        if(find_it->second == h->primary_key)
                        {
                            if(max_string.empty())
                                max_string = it->first;
                            else
                            {
                                if(strcmp((it->first).c_str(), (max_string).c_str()) > 0)
                                    max_string = it->first;
                            }
                        }
                        else
                        {
                            int i = 1;
                            auto it1 = it->second.begin();
                            while(i <= h->camount)
                            {
                                if(i == find_it->second)
                                {
                                    if(max_string.empty())
                                        max_string = *it1;
                                    else
                                    {
                                        if(strcmp((*it1).c_str(), (max_string).c_str()) > 0)
                                            max_string = *it1;
                                    }                                    
                                }
                                if(i != h->primary_key)
                                    ++it1;
                                ++i;
                            }
                        }
                        
                    }
                }
                else
                {
                    for(auto it = h->content.begin(); it != h->content.end(); ++it)
                    {
                        int i = 1;
                        auto it1= it->second.begin();
                        judg = _ForWhere(it, h, stop);
                        if(stop)
                            break;                                                                        
                        if(judg)
                        {
                            have = true;
                            if(find_it->second == h->primary_key)
                            {
                                if(max_string.empty())
                                    max_string = it->first;
                                else
                                {
                                    if(strcmp((it->first).c_str(), (max_string).c_str()) > 0)
                                        max_string = it->first;
                                }
                            }
                            else
                            {
                                while(i <= h->camount)
                                {
                                    if(i == find_it->second)
                                    {
                                        if(max_string.empty())
                                            max_string = *it1;
                                        else
                                        {
                                            if(strcmp((*it1).c_str(), (max_string).c_str()) > 0)
                                                max_string = *it1;
                                        }                                    
                                    }
                                    if(i != h->primary_key)
                                        ++it1;
                                    ++i;
                                }
                            }
                        }                        

                    }
                }
                if(have)
                    cout << "max(" << *lst_it << "): " << max_string << endl; 
                else
                    cout << "No value that satisfies the condition was found!" << endl;
            }
            else
                cout << "The table is empty!" << endl;
        }
        else
            cout << "The column " << "\"" << *lst_it << "\"" << "is not existed!" << endl;
    }
    else
        cout << "The table " << "\"" << tname << "\"" << "is not existed!" << endl;
    lst.clear();
    condition.clear();
}

void _MyMin(struct Table*&head)
{
    Table* h = head;
    bool found = false, stop = false, have = false;
    while(h)
    {
        if(h->table_name == tname)
        {
            found = true;
            break;
        }
        h = h->next;
    }
    if(found)
    {
        bool judg = false;
        auto lst_it = lst.begin();
        auto find_it = h->position.find(*lst_it);
        if(find_it != h->position.end())
        {
            if(!h->content.empty())
            {
                string min_string;
                if(condition.empty())
                {
                    have = true;
                    for(auto it = h->content.begin(); it != h->content.end();++it)
                    {
                        if(find_it->second == h->primary_key)
                        {
                            if(min_string.empty())
                                min_string = it->first;
                            else
                            {
                                if(strcmp((it->first).c_str(), (min_string).c_str()) < 0)
                                    min_string = it->first;
                            }
                        }
                        else
                        {
                            int i = 1;
                            auto it1 = it->second.begin();
                            while(i <= h->camount)
                            {
                                if(i == find_it->second)
                                {
                                    if(min_string.empty())
                                        min_string = *it1;
                                    else
                                    {
                                        if(strcmp((*it1).c_str(), (min_string).c_str()) < 0)
                                            min_string = *it1;
                                    }                                    
                                }
                                if(i != h->primary_key)
                                    ++it1;
                                ++i;
                            }
                        }
                        
                    }
                }
                else
                {
                    for(auto it = h->content.begin(); it != h->content.end(); ++it)
                    {
                        int i = 1;
                        auto it1= it->second.begin();
                        judg = _ForWhere(it, h, stop);
                        if(stop)
                            break;                                                                        
                        if(judg)
                        {
                            have = true;
                            if(find_it->second == h->primary_key)
                            {
                                if(min_string.empty())
                                    min_string = it->first;
                                else
                                {
                                    if(strcmp((it->first).c_str(), (min_string).c_str()) < 0)
                                        min_string = it->first;
                                }
                            }
                            else
                            {
                                while(i <= h->camount)
                                {
                                    if(i == find_it->second)
                                    {
                                        if(min_string.empty())
                                            min_string = *it1;
                                        else
                                        {
                                            if(strcmp((*it1).c_str(), (min_string).c_str()) < 0)
                                                min_string = *it1;
                                        }                                    
                                    }
                                    if(i != h->primary_key)
                                        ++it1;
                                    ++i;
                                }
                            }
                        }                        

                    }
                }
                if(have)
                    cout << "min(" << *lst_it << "): " << min_string << endl; 
                else
                    cout << "No value that satisfies the condition was found!" << endl;
            }
            else
                cout << "The table is empty!" << endl;
        }
        else
            cout << "The column " << "\"" << *lst_it << "\"" << "is not existed!" << endl;
    }
    else
        cout << "The table " << "\"" << tname << "\"" << "is not existed!" << endl;
    lst.clear();
    condition.clear();
}