#include <iostream>
#include <string.h>
#include <vector>
using namespace std;
#include "def.h"
#define SIZE 100
extern void TakeApart(string expr, vector<pair<string, string>>& toks);
string DeleChar(string str, char ch)    //删除等号前的字符包括等号
{
    auto it = str.begin();
    while (*it != ch)
        it = str.erase(it);
    str.erase(it);
    return str;

}
string DeleBlanks(string expr)
{
    for (auto it = expr.begin(); it != expr.end();)
    {
        if (*it == ' ')
            it = expr.erase(it);
        else
            ++it;
    }
    return expr;
}
bool IsExisted(char name[], struct GLOBAL* head)
{
    while (head)
    {
        if (strcmp(head->name, name) == 0)
            return true;
        head = head->next;
    }
    return false;

}
bool IsExprValid(string expr)
{
    int count = 0;
    if(expr[0] == '*' || expr[0] == '/' || expr[0] == '%')
        return false;
    int i = 0;
    for (; expr[i] != '\0'; ++i) //check the expression
    {
        if (count < 0)
            return false;
        //error:end with '(' or nothing in brackets
        if (expr[i] == '(')
        {
            ++count; 
            ++i;
            if(expr[i] == '\0' || expr[i] == ')')
                return false;
            --i;
        }   
        //behind of ')' is not operator                                                         //出现类似 x（y+2)的情况当作函数调用来处理
        else if (expr[i] == ')')
        {   
            --count;
            ++i;
            if(expr[i] == '(' || expr[i] >= 'a' && expr[i] <= 'z' || expr[i] >= 'A' && expr[i] <= 'Z')
                return false;
            --i;
        }
        //error:2 */3 or end with operator or 8+++-+*+9
        else if (expr[i] == '*' || expr[i] == '/' || expr[i] == '%' || expr[i] == '#' || expr[i] == '$')
        {
            ++i;
            if ( expr[i] == '*' || expr[i] == '/' ||  expr[i] == '%' || expr[i] == ')' || expr[i] == '\0')    
                return false;           
            --i;
        }
        else if(expr[i] == '+' || expr[i] == '-'){
            ++i;
            while(expr[i] == '+' || expr[i] == '-' || expr[i] == '#' || expr[i] == '$'){
                if(expr[i] == '*' || expr[i] == '/' ||  expr[i] == '%'  || expr[i] == '\0')
                    return false;
                ++i;
            }
            --i;
        }
        else if(expr[i] >= '0' && expr[i] <= '9'){
            ++i;
            while(expr[i] >= '0' && expr[i] <= '9')
                ++i;
            if(expr[i] == '\0')
                break;
            else{
                if(expr[i] == '#' || expr[i] == '$' || expr[i] == '(')
                    return false;                
                else if(expr[i] >= 'a' && expr[i] <= 'z' || expr[i] >= 'A' && expr[i] <= 'Z')
                    return false;
            --i;
                
            }
        }
        else if(expr[i] >= 'a' && expr[i] <= 'z' || expr[i] >= 'A' && expr[i] <= 'Z'){
            ++i;
            while(expr[i] >= 'a' && expr[i] <= 'z' || expr[i] >= 'A' && expr[i] <= 'Z')
                ++i;
            if(expr[i] == '\0')
                break;
            else{
                if(expr[i] == '#' || expr[i] == '$')
                    return false;                
                else if(expr[i] >= '0' && expr[i] <= '9')
                    return false;
            --i;
            }
        }
    }
    if (count != 0)
        return false;
    return true;
}
int Parse(string input, struct GLOBAL& temp, struct GLOBAL* varHead, struct GLOBAL* funcHead)
{
    char chs[50];
    int n;
    string expr;
    n = sscanf(input.c_str(), "%s", chs);
    if (input == "SHOW VAR")
        return 6;
    if (input == "SHOW FUNC")
        return 7;
    if(input == "Taylor formula")
        return 11;
    if (strcmp(chs, "Var") == 0)
    {
        temp.type = "var";
        int j = 0;
        expr = input.substr(4);
        expr = DeleBlanks(expr);
        sscanf(expr.c_str(), "%[^=]", temp.name);
        if (IsExisted(temp.name, varHead))
            return 8;
        expr = DeleChar(expr, '=');
        if (!IsExprValid(expr))
            return 4;
        TakeApart(expr, temp.toks);
        return 1;
    }
    else if (strcmp(chs, "Func") == 0)
    {        
        temp.type = "func";
        int j = 0;
        expr = input.substr(5);
        expr = DeleBlanks(expr);
        if (!IsExprValid(expr))
            return 4;
        sscanf(expr.c_str(), "%[^(]", temp.name);
        if (IsExisted(temp.name, funcHead))
            return 8;
        for (auto it = expr.begin(); it != expr.end(); ++it)
        {
            if ('(' == *it)
            {
                int count = 0;
                string str = "";
                ++count;
                ++it;
                int count1 = 0;
                while (count != 0)
                {
                    if (*it == ')')
                    {
                        --count;
                        --count1;
                    }
                    else if (*it == '(')
                    {
                        ++count;
                        ++count1;
                    }
                    if (0 == count)
                        break;
                    else
                    {
                        if (count1 == 0 && *it == ',')
                        {
                            temp.args.push_back(make_pair(str, "#"));
                            str.clear();
                        }
                        else
                            str += *it;
                    }
                    ++it;
                }
                temp.args.push_back(make_pair(str, "#"));
                str.clear();
                if (count == 0 && *it == ')')
                    break;
            }
        }
        expr = DeleChar(expr, '=');        
        TakeApart(expr, temp.toks);
        return 2;
    }
    else if (input == "exit")
        return 5;
    else {       //eval
        auto findit = input.begin();
        for (; findit != input.end(); ++findit)
            if (*findit == '=')
                break;
        if (findit != input.end())       //modefy the expr of var which has been defined
        {
            for (int i = 0; input[i] != '='; ++i)
            {
                if (input[i] == '(' || input[i] == ')')
                    return 9;
            }
            string expr;
            expr = DeleBlanks(input);
            if (!IsExprValid(expr))
                return 4;
            n = sscanf(expr.c_str(), "%[^=]", temp.name);
            expr = DeleChar(expr, '=');
            TakeApart(expr, temp.toks);
            return 10;

        }
        else
        {        
            int count = 0;
            expr = DeleBlanks(input);
            if(expr.empty())
                return 12;  //input valid
            if(!IsExprValid(expr))
                return 4;            
            TakeApart(input, temp.toks);
            return 3;
        }
    }
}

void Def(struct GLOBAL*& head, struct GLOBAL*& tail, struct GLOBAL& temp)
{
    struct GLOBAL* p = new GLOBAL;
    *p = temp;
    p->next = NULL;
    if (head == NULL)
        head = p;
    else
        tail->next = p;
    tail = p;
    temp.args.clear();
    temp.toks.clear();
    memset(&temp.name, '\0', sizeof(temp.name));
    memset(&temp.type, '\0', sizeof(temp.type));


}

void TakeApart(string expr, vector<pair<string, string>>& toks)
{
    int n;
    int count = 0;
    string str = "";
    for (auto it = expr.begin(); it != expr.end(); ++it)
    {
        str.clear();
        if ((*it) == '(')
            toks.push_back(make_pair("bracket", "("));
        else if ((*it) == ')')
            toks.push_back(make_pair("bracket", ")"));
        else if ('+' == *it || '-' == *it || '*' == *it || '/' == *it || '%' ==  *it || '!' == *it || '#' == *it || *it == '$')
        {
            str += *it;
            toks.push_back(make_pair("op", str));
        }
        else if ((*it >= 'a' && *it <= 'z') || (*it >= 'A' && *it <= 'Z'))
        {
            while ((*it >= 'a' && *it <= 'z') || (*it >= 'A' && *it <= 'Z'))
            {                
                str += *it;
                ++it;
                if (it == expr.end())
                    break;
            }
            if (it == expr.end())
            {
                toks.push_back(make_pair("var", str));
                break;
            }                
            if ('(' == *it)
            {
                str.append(" ");
                ++count;
                ++it;
                int count1 = 0;
                while (count != 0 && it != expr.end())
                {
                    if (*it == ')')
                    {
                        --count;
                        --count1;
                    }
                    else if (*it == '(')
                    {
                        ++count;
                        ++count1;
                    }
                    if (0 == count)
                        break;
                    else
                    {
                        if (*it == ',' && count1 == 0)
                            str.append(" ");
                        else
                            str += *it;
                    }
                    ++it;
                }
                toks.push_back(make_pair("func", str)); //format: {"func", name arg1 arg2...} use blanks to seperate func name and args;
            }
            else if (*it == ')')
            {
                toks.push_back(make_pair("var", str));
                str.clear();
                str += *it;
                toks.push_back(make_pair("bracket", str));

            }
            else if ('+' == *it || '-' == *it || '*' == *it || '/' == *it || '%' == *it || '!' == *it || '#' == *it || '$' == *it)
            {
                toks.push_back(make_pair("var", str));
                str.clear();
                str += *it;
                toks.push_back(make_pair("op", str));
                str.clear();
            }
            else if (it == expr.end())
            {
                toks.push_back(make_pair("var", str));
                break;
            }
        }
        else if (*it >= '0' && *it <= '9')
        {
            str += *it;
            ++it;
            if (it == expr.end())
            {
                toks.push_back(make_pair("const", str));
                break;
            }
            while ((*it >= '0' && *it <= '9')|| *it == '.')
            {                
                str += *it;
                ++it;
                if (it == expr.end())
                    break;
            }
            toks.push_back(make_pair("const", str));
            str.clear();
            if (it == expr.end())
                break;
            if (*it == ')')
                toks.push_back(make_pair("bracket", ")"));
            else
            {
                str += *it;
                if ('+' == *it || '-' == *it || '*' == *it || '/' == *it || '%' == *it || '!' == *it || '#' == *it || '$' == *it)
                {
                    toks.push_back(make_pair("op", str));
                    str.clear();
                }
            }
        }
    }
}