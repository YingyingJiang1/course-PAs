#include <iostream>
#include <string.h>
#include <sstream>
#include <map>
#include <list>
using namespace std;
#include "extern.h"
int _Parse(char command[])
{
    pkey = 0;               //value of pkey may have changed,so every turn should set it to 0
    char str[100], key[20];
    int m = 1, n;
    bool end = false;
    sscanf(command, "%s", str);
    if(0 == strcmp(str, "CREATE"))
    {
        sscanf(command, "%*s%s", str);
        if(0 == strcmp(str, "TABLE"))
        {
            n = sscanf(command, "%*s%*s%s", str);
            if(n != -1)
                tname = str;
            else
                return 0;
            char s[100] = "%*[^,]%*1s", t[100];
            n = sscanf(command, "%*s%*s%*s%[^,]", str);
            if(str[1] == '(')
            {
                if(str[0] == ' ')
                {
                    for(int i = 0; str[i] != '\0'; ++i)
                    {
                        if(str[i] == ')')
                        {
                            ++i;
                            if(str[i] == ';')
                            {
                                str[i] = '\0';
                                cname.append(str);
                                auto it = cname.begin();
                                cname.erase(it);
                                sscanf(str, "%*s%[^)]", key);
                                if(0 == strcmp(key, " PRIMARY_KEY")) //pay attention to the blank before "PRIMARY_KEY"
                                {
                                    pkey = m;
                                    sscanf(str,"%*1s%s", key);
                                }
                                else
                                    sscanf(str, "%*1s%[^)]s",key);
                                pos[key] = m;   
                                columns = m;                             
                                return 1;
                            }
                            cname.clear();
                            return 0;
                        }
                        
                    }
                    string str1 = str;
                    str1.append(",");
                    cname.append(str1);
                    auto it = cname.begin();
                    cname.erase(it);
                }
                else
                {
                    cname.clear();
                    pos.clear();
                    return 0;
                }
                sscanf(str, "%*s%s", key);
                if(0 == strcmp(key, "PRIMARY_KEY"))
                    pkey = m;
                sscanf(str, "%*1s%s",key);
                pos[key] = m;
                strcpy(t, s);
                strcat(t, "%[^,]");
                n = sscanf(command, t, str);
                while(n != -1)
                {
                    int i = 0;
                    for(; str[i] != '\0'; ++i)
                    {
                        if(str[i] == ')')
                        {
                            ++i;
                            if(str[i] == ';')
                            {
                                end = true;
                                break;
                            }
                            else
                            cname.clear();
                            return 0;
                        }
                    }
                    if(end)
                    {
                        for(int i = 0; str[i] != '\0'; ++i)
                        {
                            if(str[i] == ';')
                            {
                                str[i] = '\0';
                                break;
                            }
                        }
                        cname.append(str);
                        sscanf(str, "%*s%[^)]", key);
                        if(0 == strcmp(key, " PRIMARY_KEY"))
                        {
                            ++m;
                            pkey = m;
                            sscanf(str, "%s",key);
                            pos[key] = m;
                            columns = m;
                        }
                        else
                        {
                            ++m;
                            sscanf(str, "%[^)]",key);
                            pos[key] = m;
                            columns = m;
                        }
                        return 1;
                    }
                    else
                    {
                        ++m;
                        cname.append(str);
                        cname.append(",");
                        sscanf(str, "%*s%s", key);
                        if(0 == strcmp(key, "PRIMARY_KEY"))
                            pkey = m;
                        sscanf(str, "%s",key);
                        pos[key] = m;                        
                        strcat(s, "%*[^,]%*1s");
                        strcpy(t, s);
                        strcat(t, "%[^,]");
                        n = sscanf(command, t, str);
                    }
                    
                }
                cname.clear();
                pos.clear();
                return 0;
                
            }
            else
                return 0;

        }
        else
        return 0;
    }
    else 
    {
        sscanf(command, "%[^;]", str);
        if(0 == strcmp(str, "SHOW TABLES"))
        {
            int i = 0;
            sscanf(command, "%*s%s", str);
            for(; str[i] != '\0'; ++i)
            {
                if(str[i] == ';')
                return 2;
            }
            if(str[i] == '\0')
            return 0;
        }
        else
        {
            sscanf(command, "%s", str);
            if(0 == strcmp(str, "DROP"))
            {
                
                sscanf(command, "%*s%s", str);
                if(0 == strcmp(str, "TABLE"))
                {
                    n = sscanf(command, "%*s%*s%s", str);
                    if(n == -1)
                        return 0;
                    else
                    {
                        tname = str;
                        int i = 0;
                        for(; tname[i] != '\0'; ++i)
                        {
                            if(tname[0] == ';')
                                return 0;
                            if(tname[i] == ';')
                            {
                                for(auto it = tname.begin(); it != tname.end(); ++it)
                                {
                                    if(*it == ';')
                                    {   
                                        tname.erase(it);
                                        break;
                                    }
                                }
                                return 3;
                            }
                            if(tname[i] != '_')
                                if(tname[i] < 'A' || tname[i] > 'Z')
                                    if(tname[i] < 'a' || tname[i] > 'z')
                                        return 0;
                        }
                        if(str[i] == '\0')
                            return 0;
                    }

                }
                else
                return 0;

            }
            else
            {
                if(0 == strcmp(str, "INSERT"))
                {
                    sscanf(command, "%*s%s", str);
                    if(0 == strcmp(str, "INTO"))
                    {
                        n = sscanf(command, "%*s%*s%s", str);
                        if(n == -1)
                            return 0;
                        else
                        {
                            tname = str;
                            
                            for(int i = 0; tname[i] != '\0'; ++i)
                            {
                                if(tname[i] != '_')
                                    if(tname[i] < 'A' || tname[i] > 'Z')
                                        if(tname[i] < 'a' || tname[i] > 'z')
                                            return 0;
                                
                            }    
                            n = sscanf(command, "%*s%*s%*s%s", str);
                            if(0 == strcmp(str, "VALUES"))
                            {
                                n = sscanf(command, "%*s%*s%*s%*s%1s", str);
                                if(0 == strcmp(str, "("))
                                {
                                    n = sscanf(command, "%*s%*s%*s%*s%*1s%[^,]", str);
                                    if(n != -1)
                                    {
                                        lst.push_back(str);
                                        char s[100] = "%*[^,]%*1s", t[100] = "%*[^,]%*1s";
                                        strcat(t, "%[^,]");
                                        n = sscanf(command, t, str);                                        
                                        while(n != -1)
                                        {
                                            for(int i = 0; str[i] != '\0'; ++i)
                                            {
                                                if(str[i] == ')')
                                                {
                                                    ++i;
                                                    if(str[i] == ';')
                                                    {
                                                        end = true;
                                                        break;
                                                    }
                                                    else
                                                    {
                                                        lst.clear();
                                                        return 0;
                                                    }
                                                }
                                            }
                                            if(end)
                                            {
                                                string str1 = str;
                                                for(auto it = str1.begin(); it != str1.end();)
                                                {
                                                    if(*it == ')')
                                                        str1.erase(it);
                                                    if(*it == ';')
                                                        str1.erase(it);
                                                    else
                                                        ++it;
                                                }                                                                                               
                                                lst.push_back(str1);
                                                return 4;
                                            }
                                            else
                                            {
                                                lst.push_back(str);
                                                strcat(s, "%*[^,]%*1s");
                                                strcpy(t, s);
                                                strcat(t, "%[^,]");
                                                n = sscanf(command, t, str);
                                            }
                                        }
                                        lst.clear();
                                        return 0;
                                    }
                                    else
                                        return 0;
                                }
                                else
                                    return 0;

                            }
                            else
                                return 0;
                        }
                    }
                    else
                        return 0;
                }
                else
                {
                    if(0 == strcmp(str, "SELECT"))
                    {
                        sscanf(command, "%*s%s", str);
                        if(0 == strcmp(str, "DISTINCT"))
                        {
                            lst.push_back(str);
                            n = sscanf(command, "%*s%*s%s", str);
                            char str1[100], s[100] = "%*[^,]%*1s", t[100] = "%*[^,]%*1s";
                            n = sscanf(str, "%[^,]", str1);
                            if(n != -1)
                                lst.push_back(str1);
                            strcat(t, "%[^,]");
                            n = sscanf(str, t, str1);
                            while(n != -1)
                            {
                                lst.push_back(str1);
                                strcat(s, "%*[^,]%*1s");
                                strcpy(t, s);
                                strcat(t, "%[^,]");
                                n = sscanf(str, t, str1);

                            }
                            sscanf(command, "%*s%*s%*s%s", str);
                            if(0 == strcmp(str, "FROM"))
                            {
                                n = sscanf(command, "%*s%*s%*s%*s%s", str);
                                if(n != -1)
                                {
                                    int i = 0;
                                    for(; str[i] != '\0'; ++i)
                                    {
                                        if(str[i] == ';')
                                        {
                                            str[i] = '\0';
                                            tname = str;
                                            return 5;
                                        }
                                    }
                                    tname = str;
                                    sscanf(command, "%*s%*s%*s%*s%*s%s", str);
                                    if(0 == strcmp(str, "WHERE"))
                                    {
                                        n = sscanf(command, "%*s%*s%*s%*s%*s%*s%s", str);
                                        if(n != -1)
                                        {
                                            int i = 0;
                                            for(; str[i] != '\0'; ++i)
                                            {
                                                if(str[i] == ';')
                                                {
                                                    string str1 = str;
                                                    for(auto it = str1.begin(); it != str1.end(); )
                                                    {
                                                        if(*it == ';')
                                                            str1.erase(it);
                                                        else
                                                        ++it;
                                                    }
                                                    condition.push_back(str1);
                                                    return 5;
                                                }
                                            }
                                            condition.push_back(str);
                                            sscanf(command, "%*s%*s%*s%*s%*s%*s%*s%s", str);
                                            if(0 == strcmp(str, "AND")|| 0 == strcmp(str, "OR"))
                                            {
                                                condition.push_back(str);
                                                n = sscanf(command, "%*s%*s%*s%*s%*s%*s%*s%*s%s", str);
                                                if(n != -1)
                                                {
                                                    int i = 0;
                                                    for(; str[i] != '\0'; ++i)
                                                    {
                                                        if(str[i] == ';')
                                                        {
                                                            string str1 = str;
                                                            for(auto it = str1.begin(); it != str1.end(); )
                                                            {
                                                                if(*it == ';')
                                                                    str1.erase(it);
                                                                else
                                                                    ++it;
                                                            }
                                                            condition.push_back(str1);
                                                            return 5;
                                                        }
                                                    }
                                                    lst.clear();
                                                    condition.clear();
                                                    return 0;
                                                }
                                                else
                                                {
                                                    lst.clear();
                                                    condition.clear();
                                                    return 0;
                                                }
                                            }
                                            else
                                            {
                                                lst.clear();
                                                condition.clear();
                                                return 0;
                                            }
                                        }

                                    }
                                    else
                                    {
                                        lst.clear();
                                        condition.clear();
                                        return 0;
                                    }
                                }
                                else
                                {
                                    lst.clear();
                                    condition.clear();
                                    return 0;
                                }
                            }
                            else
                            {
                                lst.clear();
                                return 0;
                            }
                        }
                        else if(0 == strcmp(str, "*"))
                        {
                            lst.push_back("*");
                            sscanf(command, "%*s%*s%s", str);
                            if(0 == strcmp(str, "FROM"))
                            {
                                n = sscanf(command, "%*s%*s%*s%s", str);
                                 if(n != -1)
                                {
                                    int i = 0;
                                    for(; str[i] != '\0'; ++i)
                                    {
                                        if(str[i] == ';')
                                        {
                                            str[i] = '\0';
                                            tname = str;
                                            return 5;
                                        }
                                    }
                                    tname= str;
                                    sscanf(command, "%*s%*s%*s%*s%s", str);
                                    if(0 == strcmp(str, "WHERE"))
                                    {
                                        n = sscanf(command, "%*s%*s%*s%*s%*s%s", str);
                                        if(n != -1)
                                        {
                                            int i = 0;
                                            for(; str[i] != '\0'; ++i)
                                            {
                                                if(str[i] == ';')
                                                {
                                                    str[i] = '\0';
                                                    condition.push_back(str);
                                                    return 5;
                                                }
                                            }
                                            condition.push_back(str);
                                            sscanf(command, "%*s%*s%*s%*s%*s%*s%s", str);
                                            if(0 == strcmp(str, "AND")|| 0 == strcmp(str, "OR"))
                                            {
                                                condition.push_back(str);
                                                n = sscanf(command, "%*s%*s%*s%*s%*s%*s%*s%s", str);
                                                if(n != -1)
                                                {
                                                    int i = 0;
                                                    for(; str[i] != '\0'; ++i)
                                                    {
                                                        if(str[i] == ';')
                                                        {
                                                            str[i] = '\0';
                                                            condition.push_back(str);
                                                            return 5;
                                                        }
                                                    }
                                                    lst.clear();
                                                    condition.clear();
                                                    return 0;
                                                }
                                                else
                                                {
                                                    lst.clear();
                                                    condition.clear();
                                                    return 0;
                                                }
                                            }
                                            else
                                            {
                                                lst.clear();
                                                condition.clear();
                                                return 0;
                                            }
                                        }
                                        else
                                        {
                                            lst.clear();
                                            condition.clear();
                                            return 0;
                                        }
                                    }
                                    else
                                    {
                                        lst.clear();
                                        condition.clear();
                                        return 0;
                                    }
                                }
                                else
                                {
                                    lst.clear();
                                    condition.clear();
                                    return 0;
                                }
                            }
                            else
                            {
                                lst.clear();
                                condition.clear();
                                return 0;
                            }
                        }
                        else
                        {
                            char str1[100], s[100] = "%*[^,]%*1s", t[100] = "%*[^,]%*1s";
                            n = sscanf(str, "%[^,]", str1);
                            if(n != -1)
                                lst.push_back(str1);
                            strcat(t, "%[^,]");
                            n = sscanf(str, t, str1);
                            while(n != -1)
                            {
                                lst.push_back(str1);
                                strcat(s, "%*[^,]%*1s");
                                strcpy(t, s);
                                strcat(t, "%[^,]");
                                n = sscanf(str, t, str1);

                            }
                            sscanf(command, "%*s%*s%s", str);
                            if(0 == strcmp(str, "FROM"))
                            {
                                n = sscanf(command, "%*s%*s%*s%s", str);
                                 if(n != -1)
                                {
                                    int i = 0;
                                    for(; str[i] != '\0'; ++i)
                                    {
                                        if(str[i] == ';')
                                        {
                                            str[i] = '\0';
                                            tname = str;
                                            return 5;
                                        }
                                    }
                                    tname = str;
                                    sscanf(command, "%*s%*s%*s%*s%s", str);
                                    if(0 == strcmp(str, "WHERE"))
                                    {
                                        n = sscanf(command, "%*s%*s%*s%*s%*s%s", str);
                                        if(n != -1)
                                        {
                                            int i = 0;
                                            for(; str[i] != '\0'; ++i)
                                            {
                                                if(str[i] == ';')
                                                {
                                                    str[i] = '\0';
                                                    condition.push_back(str);
                                                    return 5;
                                                }
                                            }
                                            condition.push_back(str);
                                            sscanf(command, "%*s%*s%*s%*s%*s%*s%s", str);
                                            if(0 == strcmp(str, "AND")|| 0 == strcmp(str, "OR"))
                                            {
                                                condition.push_back(str);
                                                n = sscanf(command, "%*s%*s%*s%*s%*s%*s%*s%s", str);
                                                if(n != -1)
                                                {
                                                    int i = 0;
                                                    for(; str[i] != '\0'; ++i)
                                                    {
                                                        if(str[i] == ';')
                                                        {
                                                            str[i] = '\0';
                                                            condition.push_back(str);
                                                            return 5;
                                                        }
                                                    }
                                                    lst.clear();
                                                    condition.clear();
                                                    return 0;
                                                }
                                                else
                                                {
                                                    lst.clear();
                                                    condition.clear();
                                                    return 0;
                                                }
                                            }
                                            else
                                            {
                                                lst.clear();
                                                condition.clear();
                                                return 0;
                                            }
                                        }
                                        else
                                        {
                                            lst.clear();
                                            condition.clear();
                                            return 0;
                                        }
                                    }
                                    else
                                    {
                                        lst.clear();
                                        condition.clear();
                                        return 0;
                                    }
                                }
                                else
                                    {
                                        lst.clear();
                                        condition.clear();
                                        return 0;
                                    }
                            }
                            else
                                    {
                                        lst.clear();
                                        condition.clear();
                                        return 0;
                                    };
                        }
                    }
                    else
                    {
                        if(0 == strcmp(str, "UPDATE"))
                        {
                            n = sscanf(command, "%*s%s", str);
                            if(n != -1)
                                tname = str;
                            else
                                return 0;
                            sscanf(command, "%*s%*s%s", str);
                            if(0 == strcmp(str, "SET"))
                            {
                                n = sscanf(command, "%*s%*s%*s%s", str);
                                if(n != -1)
                                {
                                    int i = 0;
                                    for(; str[i] != '\0'; ++i)
                                    {
                                        if(str[i] == ';')
                                        {
                                            str[i] = '\0';
                                            lst.push_back(str);
                                            return 6;
                                        }
                                    }
                                    lst.push_back(str);
                                    sscanf(command, "%*s%*s%*s%*s%s", str);
                                    if(0 == strcmp(str, "WHERE"))
                                    {
                                        n = sscanf(command,"%*s%*s%*s%*s%*s%s" , str);
                                        if(n != -1)
                                        {
                                            int i = 0;
                                            for(; str[i] != '\0'; ++i)
                                            {
                                                if(str[i] == ';')
                                                {
                                                    str[i] = '\0';
                                                    condition.push_back(str);
                                                    return 6;
                                                }
                                            }
                                            condition.push_back(str);
                                            sscanf(command, "%*s%*s%*s%*s%*s%*s%s", str);
                                            if(0 == strcmp(str, "AND") ||0 == strcmp(str, "OR"))
                                            {
                                                condition.push_back(str);
                                                n = sscanf(command,"%*s%*s%*s%*s%*s%*s%*s%s", str);
                                                if(n != -1)
                                                {
                                                    int i = 0;
                                                    for(; str[i] != '\0'; ++i)
                                                    {
                                                        if(str[i] == ';')
                                                        {
                                                            str[i] = '\0';
                                                            condition.push_back(str);
                                                            return 6;
                                                        }
                                                    }
                                                    lst.clear();
                                                    condition.clear();
                                                    return 0;
                                                }
                                                else
                                                    lst.clear();
                                                    condition.clear();
                                                    return 0;
                                            }
                                            else
                                                lst.clear();
                                                condition.clear();
                                                return 0;
                                        }
                                        lst.clear();
                                        condition.clear();
                                        return 0;
                                    }
                                    lst.clear();
                                    condition.clear();
                                    return 0;
                                }
                            }
                            lst.clear();
                            condition.clear();
                            return 0;
                        }
                        else
                        {
                            if(0 == strcmp(str, "DELETE"))
                            {

                                sscanf(command, "%*s%s", str);
                                if(0 == strcmp(str, "FROM"))
                                {
                                    n = sscanf(command, "%*s%*s%s", str);
                                    if(n != -1)
                                    {
                                        tname = str;
                                        int i = 0;
                                        if(tname == ";")
                                            return 0;
                                        for(; tname[i] != '\0'; ++i)
                                        {
                                            if(tname[i] == ';')
                                            {
                                                tname[i] = '\0';
                                                return 7;
                                            }
                                        }
                                        sscanf(command, "%*s%*s%*s%s",str);
                                        if(0 == strcmp(str,"WHERE"))
                                        {
                                            n = sscanf(command, "%*s%*s%*s%*s%s",str);
                                            if(n != -1)
                                            {
                                                int i = 0;
                                                for(; str[i] != '\0'; ++i)
                                                {
                                                    if(str[i] == ';')
                                                    {
                                                        str[i] = '\0';
                                                        condition.push_back(str);
                                                        return 7;
                                                    }
                                                }
                                                condition.push_back(str);
                                                sscanf(command, "%*s%*s%*s%*s%*s%s",str);
                                                if(0 == strcmp(str, "AND") || 0 == strcmp(str, "OR"))
                                                {
                                                    condition.push_back(str);
                                                    n = sscanf(command, "%*s%*s%*s%*s%*s%*s%s", str);
                                                    if(n != -1)
                                                    {
                                                        int i = 0;
                                                        for(; str[i] != '\0'; ++i)
                                                        {
                                                            if(str[i] == ';')
                                                            {
                                                                str[i] = '\0';
                                                                condition.push_back(str);
                                                                return 7;
                                                            }
                                                        }
                                                        condition.clear();
                                                        return 0;

                                                    }
                                                    condition.clear();
                                                    return 0;
                                                }
                                                condition.clear();
                                                return 0;
                                            }
                                            condition.clear();
                                            return 0;
                                        }
                                        else
                                            return 0;
                                    }
                                    else
                                        return 0;
                                }
                                else
                                    return 0;
                            }
                            else
                            {
                                if(0 == strcmp(str,"ALTER"))
                                {
                                    sscanf(command, "%*s%s", str);
                                    if(0 == strcmp(str, "TABLE"))
                                    {
                                        n = sscanf(command, "%*s%*s%s", str);
                                        if(n != -1)
                                        {
                                            if(str == ";")
                                                return 0;
                                            else
                                                tname = str;
                                            n = sscanf(command, "%*s%*s%*s%s", str);
                                            if(n != -1)
                                            {
                                                if(strcmp(str, "ADD") == 0 || strcmp(str, "DROP") == 0)
                                                {
                                                    lst.push_back(str);
                                                    n = sscanf(command, "%*s%*s%*s%*s%s", str);
                                                    if(n != -1)
                                                    {
                                                        if(str == ";")
                                                            return 0;
                                                        else
                                                        {                                                           
                                                            for(int i = 0; str[i] != '\0'; ++i)
                                                            {
                                                                if(str[i] == ';')
                                                                {
                                                                    str[i] = '\0';
                                                                    break;
                                                                }
                                                                if(str[i] != '_')
                                                                    if(str[i] < 'A' || str[i] > 'Z')
                                                                        if(str[i] < 'a' || str[i] > 'z')
                                                                        {
                                                                            lst.clear();
                                                                            return 0;
                                                                        }
                                
                                                            }    
                                                            cname = str;
                                                            for(auto it = cname.begin(); it != cname.end(); ++it)
                                                            {
                                                                if(*it == ';')
                                                                    cname.erase(it);
                                                            }
                                                            return 8;
                                                        }
                                                    }
                                                    else
                                                    cname.clear();
                                                    lst.clear();
                                                        return 0;
                                                }
                                                else
                                                    return 0;
                                            }
                                            else
                                                return 0;
                                        }
                                        else
                                            return 0;
                                    }
                                }
                                else
                                {
                                    bool par = false;         //to verify whether parentheses are a pari
                                    sscanf(command,"%6s", str);
                                    if(0 == strcmp(str, "COUNT("))
                                    {
                                        n = sscanf(command, "%*6s%s", str);
                                        if(n != -1)
                                        {
                                            for(int i = 0; str[i] != '\0'; ++i)
                                            {
                                                if(str[i] == ')')
                                                {
                                                    par = true;
                                                    str[i] = '\0';
                                                }
                                            }
                                            if(par)
                                            {
                                                bool equal = false;
                                                lst.push_back(str);
                                                sscanf(command, "%*s%s", str);
                                                if(0 == strcmp(str,"IN"))
                                                {
                                                    n = sscanf(command, "%*s%*s%s", str);
                                                    if(n != -1)
                                                    {
                                                        tname = str;
                                                        for(int i = 0; tname[i] != '\0'; ++i)
                                                        {
                                                            if(tname[i] == ';')
                                                            {
                                                                tname[i] = '\0';
                                                                return 9;
                                                            }
                                                        }
                                                        sscanf(command, "%*s%*s%*s%s", str);
                                                        if(0 == strcmp(str, "WHERE"))
                                                        {
                                                            n = sscanf(command, "%*s%*s%*s%*s%s", str);
                                                            if(n != -1)
                                                            {
                                                                for(int i = 0; str[i] != '\0'; ++i)
                                                                {
                                                                    if(str[i] == '=')
                                                                    {
                                                                        equal = true;
                                                                    } 
                                                                    if(str[i] == ';')
                                                                    {
                                                                        if(equal)
                                                                        {
                                                                            str[i] = '\0';
                                                                            condition.push_back(str);
                                                                            return 9;
                                                                        }
                                                                        lst.clear();
                                                                        return 0;
                                                                    }                                                                                                           
                                                                }
                                                                if(equal)
                                                                {
                                                                    equal = false;
                                                                    condition.push_back(str);
                                                                    sscanf(command, "%*s%*s%*s%*s%*s%s", str);
                                                                    if(0 == strcmp(str, "AND") || 0 == strcmp(str, "OR"))
                                                                    {
                                                                        condition.push_back(str);
                                                                        n = sscanf(command, "%*s%*s%*s%*s%*s%*s%s", str);
                                                                        if(n != -1)
                                                                        {
                                                                            for(int i = 0; str[i] != '\0'; ++i)
                                                                            {
                                                                                if(str[i] == '=')
                                                                                {
                                                                                    equal = true;
                                                                                }
                                                                                if(str[i] == ';')
                                                                                {
                                                                                    if(equal)
                                                                                    {
                                                                                        str[i] = '\0';
                                                                                        condition.push_back(str);
                                                                                        return 9;
                                                                                    }
                                                                                    lst.clear();
                                                                                    condition.clear();
                                                                                    return 0;
                                                                                }
                                                                            }
                                                                            lst.clear();
                                                                            condition.clear();
                                                                            return 0;
                                                                        }
                                                                        lst.clear();
                                                                        condition.clear();
                                                                        return 0;
                                                                    }
                                                                    lst.clear();
                                                                    condition.clear();
                                                                    return 0;
                                                                }
                                                                lst.clear();
                                                                return 0;
                                                            }
                                                            lst.clear();
                                                            return 0;
                                                        }
                                                        lst.clear();
                                                        return 0;
                                                    }
                                                    lst.clear();
                                                    return 0;

                                                }
                                                lst.clear();
                                                return 0;
                                            }
                                            return 0;
                                        }
                                        return 0;
                                    }
                                    else
                                    {
                                        if(0 == strcmp(str ,"MAX"))
                                        {
                                            n = sscanf(command, "%*s%s", str);
                                            if(n != -1)
                                            {
                                                lst.push_back(str);
                                                sscanf(command, "%*s%*s%s", str);
                                                if(0 == strcmp(str,"IN"))
                                                {
                                                    n = sscanf(command, "%*s%*s%*s%s", str);
                                                    if(n != -1)
                                                    {
                                                        for(int i = 0; str[i] != '\0'; ++i)
                                                        {
                                                            if(str[i] == ';')
                                                            {
                                                                str[i] = '\0';
                                                                tname = str;
                                                                return 10;
                                                            }
                                                        }
                                                        tname = str;
                                                        sscanf(command, "%*s%*s%*s%*s%s", str);
                                                        if(0 == strcmp(str, "WHERE"))
                                                        {
                                                            bool equal = false;
                                                            n = sscanf(command, "%*s%*s%*s%*s%*s%s", str);
                                                            if(n != -1)
                                                            {
                                                                for(int i = 0; str[i] != '\0'; ++i)
                                                                {
                                                                    if(str[i] == '=')
                                                                    {
                                                                        equal = true;
                                                                    } 
                                                                    if(str[i] == ';')
                                                                    {
                                                                        if(equal)
                                                                        {
                                                                            str[i] = '\0';
                                                                            condition.push_back(str);
                                                                            return 10;
                                                                        }
                                                                        lst.clear();
                                                                        return 0;
                                                                    }                                                                                                           
                                                                }
                                                                if(equal)
                                                                {
                                                                    equal = false;
                                                                    condition.push_back(str);
                                                                    sscanf(command, "%*s%*s%*s%*s%*s%*s%s", str);
                                                                    if(0 == strcmp(str, "AND") || 0 == strcmp(str, "OR"))
                                                                    {
                                                                        condition.push_back(str);
                                                                        n = sscanf(command, "%*s%*s%*s%*s%*s%*s%*s%s", str);
                                                                        if(n != -1)
                                                                        {
                                                                            for(int i = 0; str[i] != '\0'; ++i)
                                                                            {
                                                                                if(str[i] == '=')
                                                                                {
                                                                                    equal = true;
                                                                                }
                                                                                if(str[i] == ';')
                                                                                {
                                                                                    if(equal)
                                                                                    {
                                                                                        str[i] = '\0';
                                                                                        condition.push_back(str);
                                                                                        return 10;
                                                                                    }
                                                                                    lst.clear();
                                                                                    condition.clear();
                                                                                    return 0;
                                                                                }
                                                                            }
                                                                            lst.clear();
                                                                            condition.clear();
                                                                            return 0;
                                                                        }
                                                                        lst.clear();
                                                                        condition.clear();
                                                                        return 0;
                                                                    }
                                                                    lst.clear();
                                                                    condition.clear();
                                                                    return 0;
                                                                }
                                                                lst.clear();
                                                                return 0;
                                                            }
                                                            lst.clear();
                                                            return 0;
                                                        }
                                                    }                                                    
                                                    cname.clear();
                                                    return 0;
                                                }
                                                cname.clear();
                                                return 0;
                                            }
                                            return 0;
                                        }
                                        else
                                        {
                                            if(0 == strcmp(str ,"MIN"))
                                            {
                                                n = sscanf(command, "%*s%s", str);
                                                if(n != -1)
                                                {
                                                    lst.push_back(str);
                                                    sscanf(command, "%*s%*s%s", str);
                                                    if(0 == strcmp(str,"IN"))
                                                    {
                                                        n = sscanf(command, "%*s%*s%*s%s", str);
                                                        if(n != -1)
                                                        {
                                                            for(int i = 0; str[i] != '\0'; ++i)
                                                            {
                                                                if(str[i] == ';')
                                                                {
                                                                    str[i] = '\0';
                                                                    tname = str;
                                                                    return 11;
                                                                }
                                                            }
                                                            tname = str;
                                                            sscanf(command, "%*s%*s%*s%*s%s", str);
                                                            if(0 == strcmp(str, "WHERE"))
                                                            {
                                                                bool equal = false;
                                                                n = sscanf(command, "%*s%*s%*s%*s%*s%s", str);
                                                                if(n != -1)
                                                                {
                                                                    for(int i = 0; str[i] != '\0'; ++i)
                                                                    {
                                                                        if(str[i] == '=')
                                                                        {
                                                                            equal = true;
                                                                        } 
                                                                        if(str[i] == ';')
                                                                        {
                                                                            if(equal)
                                                                            {
                                                                                str[i] = '\0';
                                                                                condition.push_back(str);
                                                                                return 11;
                                                                            }
                                                                            lst.clear();
                                                                            return 0;
                                                                        }                                                                                                           
                                                                    }
                                                                    if(equal)
                                                                    {
                                                                        equal = false;
                                                                        condition.push_back(str);
                                                                        sscanf(command, "%*s%*s%*s%*s%*s%*s%s", str);
                                                                        if(0 == strcmp(str, "AND") || 0 == strcmp(str, "OR"))
                                                                        {
                                                                            condition.push_back(str);
                                                                            n = sscanf(command, "%*s%*s%*s%*s%*s%*s%*s%s", str);
                                                                            if(n != -1)
                                                                            {
                                                                                for(int i = 0; str[i] != '\0'; ++i)
                                                                                {
                                                                                    if(str[i] == '=')
                                                                                    {
                                                                                        equal = true;
                                                                                    }
                                                                                    if(str[i] == ';')
                                                                                    {
                                                                                        if(equal)
                                                                                        {
                                                                                            str[i] = '\0';
                                                                                            condition.push_back(str);
                                                                                            return 11;
                                                                                        }
                                                                                        lst.clear();
                                                                                        condition.clear();
                                                                                        return 0;
                                                                                    }
                                                                                }
                                                                                lst.clear();
                                                                                condition.clear();
                                                                                return 0;
                                                                            }
                                                                            lst.clear();
                                                                            condition.clear();
                                                                            return 0;
                                                                        }
                                                                        lst.clear();
                                                                        condition.clear();
                                                                        return 0;
                                                                    }
                                                                    lst.clear();
                                                                    return 0;
                                                                }
                                                                lst.clear();
                                                                return 0;
                                                            }
                                                        }                                                    
                                                        cname.clear();
                                                        return 0;
                                                    }
                                                    cname.clear();
                                                    return 0;
                                                }
                                                return 0;
                                            }
                                            else
                                                return 0;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

    }
}
