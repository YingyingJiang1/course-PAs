#include <iostream>
#include <vector>
#include <string.h>
#include <cmath>
#include <sstream>
#include <stack>
#include <map>
#include <queue>
#include <list>
using namespace std;
#include "def.h"
#include "parse.h"
#include "calcuExpr.h"
void HandleUnary(vector<pair<string, string>>& toks)
{
    int countMinus = 0, count = 0;
    //表达式开头的++expr形式和中间的x ++ expr形式需要分开处理
    auto it = toks.begin();
    while ((*it).second == "(" || (*it).second == "#" || (*it).second == "$")
        ++it;
    if ((*it).second == "+") {
        it = toks.erase(it);
        while ((*it).second == "(" || (*it).second == "#" || (*it).second == "$")
            ++it;
        while ((*it).second == "+" || (*it).second == "-")
        {

            if ((*it).second == "-")
                ++countMinus;
            it = toks.erase(it);
            while ((*it).second == "(")
                ++it;
            if ((*it).second == "#" || (*it).second == "$") {
                if (countMinus % 2 == 1) {
                    it = toks.insert(it, make_pair("op", "-"));
                    it = toks.insert(it, make_pair("const", "0"));
                    it = toks.insert(it, make_pair("bracket", "("));
                    countMinus = 0;
                    ++count;
                    it += 3;
                }
                ++it;
                while ((*it).second == "#" || (*it).second == "$")
                    ++it;
            }

        }
    }
    else if ((*it).second == "-") {
        ++countMinus;
        it = toks.erase(it);
        while ((*it).second == "(" || (*it).second == "#" || (*it).second == "$")
            ++it;
        while ((*it).second == "+" || (*it).second == "-")
        {

            if ((*it).second == "-")
                ++countMinus;
            it = toks.erase(it);
            while ((*it).second == "(")
                ++it;
            if ((*it).second == "#" || (*it).second == "$") {
                if (countMinus % 2 == 1) {
                    it = toks.insert(it, make_pair("op", "-"));
                    it = toks.insert(it, make_pair("const", "0"));
                    it = toks.insert(it, make_pair("bracket", "("));
                    countMinus = 0;
                    ++count;
                    it += 3;
                }
                ++it;
                while ((*it).second == "#" || (*it).second == "$")
                    ++it;
            }

        }
    }
    if (countMinus % 2 == 1) {
        it = toks.insert(it, make_pair("op", "-"));
        it = toks.insert(it, make_pair("const", "0"));
        it = toks.insert(it, make_pair("bracket", "("));
        it += 4;
        for (int i = 0; i <= count; ++i) {
            it = toks.insert(it, make_pair("bracket", ")"));
        }
        countMinus = 0;
        count = 0;
    }
    else if (count > 0) {
        ++it;
        for (int i = 0; i < count; ++i) {
            it = toks.insert(it, make_pair("bracket", ")"));
        }
        countMinus = 0;
        count = 0;
    }
    ++it;
    for (; it != toks.end(); ++it)
    {
        if ((*it).first == "op")
        {
            ++it;
            //9+(+++--+7)
            while ((*it).second == "(" || (*it).second == "#" || (*it).second == "$") {
                ++it;

            }
            while ((*it).second == "+" || (*it).second == "-")
            {

                if ((*it).second == "-")
                    ++countMinus;
                it = toks.erase(it);

                while ((*it).second == "(") {
                    ++it;

                }
                if ((*it).second == "#" || (*it).second == "$") {
                    if (countMinus % 2 == 1) {
                        it = toks.insert(it, make_pair("op", "-"));
                        it = toks.insert(it, make_pair("const", "0"));
                        it = toks.insert(it, make_pair("bracket", "("));
                        countMinus = 0;
                        ++count;
                        it += 3;
                    }
                    ++it;
                    while ((*it).second == "#" || (*it).second == "$")
                        ++it;
                }
            }
            if (countMinus % 2 == 1) {
                it = toks.insert(it, make_pair("op", "-"));
                it = toks.insert(it, make_pair("const", "0"));
                it = toks.insert(it, make_pair("bracket", "("));
                it += 4;
                for (int i = 0; i <= count; ++i) {
                    it = toks.insert(it, make_pair("bracket", ")"));
                }
                countMinus = 0;
                count = 0;
            }
            else if (count > 0) {
                ++it;
                for (int i = 0; i < count; ++i) {
                    it = toks.insert(it, make_pair("bracket", ")"));
                }
                countMinus = 0;
                count = 0;
            }
        }
    }
}
void ConverFormat(vector<pair<string, string>>& toks)//将所有的带单目运算符的结构转化为0+的形式，例如##$$8转化为（0 + ##$$8）
{
    auto it = toks.begin();
    if ((*it).second == "#" || (*it).second == "$")
    {
        toks.insert(toks.begin(), make_pair("bracket", "("));
        toks.insert(toks.begin() + 1, make_pair("const", "0"));
        toks.insert(toks.begin() + 2, make_pair("op", "+"));
        it = toks.begin() + 4;
        while ((*it).second == "#" || (*it).second == "$")
            ++it;
        it = toks.insert(it + 1, make_pair("bracket", ")"));
        ++it;
    }
    for (; it != toks.end(); ++it)
    {
        if ((*it).second == "#" || (*it).second == "$")
        {
            it = toks.insert(it, make_pair("op", "+"));
            it = toks.insert(it, make_pair("const", "0"));
            it = toks.insert(it, make_pair("bracket", "("));
            it += 4;
            while ((*it).second == "#" || (*it).second == "$")
                ++it;

            it = toks.insert(it + 1, make_pair("bracket", ")"));

        }
    }
}
string Eval(vector<pair<string, string>>toks, struct GLOBAL* varHead, struct GLOBAL* funcHead, string env, bool& error) //eval legal expr
{
    HandleUnary(toks);
    ConverFormat(toks);
    string result;
    struct GLOBAL* head1 = varHead, * head2 = funcHead;
    bool find = false;
    if (error)
        return "0";
    for (auto it = toks.begin(); it != toks.end(); ++it)
    {
        find = false;
        head1 = varHead;
        head2 = funcHead;
        if (error)
            return "0";
        if ((*it).first == "var")        //eval var
        {

            if (env != "")
            {
                auto it1 = head2->args.begin();
                while (head2)
                {
                    if (head2->name == env)
                    {
                        it1 = head2->args.begin();
                        for (; it1 != head2->args.end(); ++it1)
                        {
                            if ((*it1).first == (*it).second)
                                break;
                        }
                        if (it1 != head2->args.end())
                        {
                            find = true;
                            break;
                        }
                    }
                    head2 = head2->next;
                }
                if (find)
                {
                    (*it).second = (*it1).second;
                    (*it).first = "const";
                }
            }
            if (!find) {
                while (head1)
                {
                    if (head1->name == (*it).second)
                    {
                        find = true;
                        break;
                    }
                    head1 = head1->next;
                }
                if (find)
                {
                    find = false;   //记得还原find的值，否则若出现类似x + y的情况，计算完x后find为true,会影响后续计算y
                    result = Eval(head1->toks, varHead, funcHead, "", error);
                    if (result[0] == '-')
                        result = "(0" + result + ")";
                    (*it).second = result;
                    (*it).first = "const";
                }
                else
                {
                    error = true;
                    cout << "NameError" << endl;
                    return "0";
                }
            }
        }
        else if ((*it).first == "func")      //eval func
        {
            string str;
            int n;
            char chs[50];
            char funcName[13];
            n = sscanf((*it).second.c_str(), "%s", funcName);    //待计算的函数的名字            
            while (head2)
            {
                if (strcmp(head2->name, funcName) == 0)
                {
                    find = true;
                    break;
                }
                head2 = head2->next;
            }
            if (find)
            {
                find = false;   //记得还原find的值，否则若出现类似x + y的情况，计算完x后find为true,会影响后续计算y
                vector<pair<string, string>>argsToks;
                char format[30], s[30] = "%*s";
                string expr;
                unsigned int count = 0;
                auto argsIt = head2->args.begin();
                while (n != 0)       //eval args;
                {
                    strcpy(format, s);
                    strcat(format, "%s");
                    strcat(s, "%*s");
                    n = sscanf((*it).second.c_str(), format, chs);
                    if (n <= 0)
                        break;
                    ++count;
                    if (count > head2->args.size())
                    {
                        error = true;
                        cout << "Parameters mismatch!" << endl;
                        return "0";
                        break;
                    }
                    expr = chs;
                    memset(format, '\0', sizeof(format));
                    TakeApart(expr, argsToks);
                    result = Eval(argsToks, varHead, funcHead, env, error);
                    if (result[0] == '-')
                        result = "(0" + result + ")";
                    (*argsIt).second = result;
                    ++argsIt;
                    argsToks.clear();
                }
                if (count < head2->args.size())
                {
                    error = true;
                    cout << "Parameters mismatch!" << endl;
                    return "0";
                    break;
                }
                result = Eval(head2->toks, varHead, funcHead, head2->name, error);                
                if (result[0] == '-')
                    result = "(0" + result + ")";
                (*it).second = result;
            }
            else
            {
                error = true;
                cout << "NameError!" << endl;
                return "0";
            }
        }
    }
    if (toks.size() == 1) {
        if (toks[0].second.npos == toks[0].second.find('('))
            return toks[0].second;
    }
    change(GetStr(toks));
    result = Calculate(error);
    Init();
    return result;
}

//1:sinx, 2:cosx, 3:e^x,  4:ln(1 + x), 5:1/ (1 +x), 7:1/(1-x),
string GetResult(string result, int expanPoint, int n, int i, char ch)
{
    bool error = false;
    if (i % 2 == 0)
        result.append("+");
    else
        result.append("-");
    if (expanPoint == 0)
        result.append("x^");
    else if (expanPoint > 0)
        result.append("(x-" + to_string(expanPoint) + ")^");
    else
        result.append("(x+" + to_string(expanPoint) + ")^");
    if (ch == 'n')
        result.append(to_string(n) + "/" + to_string(n) + "!");
    else
    {
        change(to_string(n) + "!");
        result.append(to_string(n) + "/" + Calculate(error));

    }
    return result;
}
string EvalTaylorFormula(int sequence, int  expanPoint, int power, bool& error, char ch)
{
    int i = 0;
    int n;//power of var
    string result = "";
    if (power < 0)
    {
        error = true;
        cout << "power should be greater than 0" << endl;
        return "0";
    }
    switch (sequence)
    {
    case 1: //sinx;
        n = 2 * i + 1;
        cout << "The " << expanPoint << "th order expansion of sinx at x equals " << power << " is: ";
        if (power == 0)
            return "0";
        while (n <= power)
        {
            result = GetResult(result, expanPoint, n, i, ch);
            ++i;
            n = 2 * i + 1;
        }
        return result;
    case 2: //cosx
        cout << "The " << expanPoint << "th order expansion of cosx at x equals " << power << " is: ";
        result = "1";
        if (power == 0)
            return result;
        ++i;
        n = 2 * i;
        while (n <= power)
        {
            result = GetResult(result, expanPoint, n, i, ch);
            ++i;
            n = 2 * i;
        }
        return result;
    case 3://e^x
        cout << "The " << expanPoint << "th order expansion of e^x at x equals " << power << " is: ";
        result = "1";
        if (power == 0)
            return result;
        ++i;
        n = i;
        while (n <= power)
        {
            result.append("+");
            if (expanPoint == 0)
                result.append("x^");
            else if (expanPoint > 0)
                result.append("(x-" + to_string(expanPoint) + ")^");
            else
                result.append("(x+" + to_string(expanPoint) + ")^");
            result.append(to_string(n) + "/" + to_string(n) + "!");
            ++i;
            n = i;
        }
        return result;
    case 4:     //ln(1+x)
        n = i + 1;
        cout << "The " << expanPoint << "th order expansion of ln(1+x) at x equals " << power << " is: ";
        if (power == 0)
            return "0";
        while (n <= power)
        {
            result = GetResult(result, expanPoint, n, i, ch);
            ++i;
            n = i + 1;
        }
        return result;
    case 5: //1/(1+x)
        cout << "The " << expanPoint << "th order expansion of 1/(1+x) at x equals " << power << " is: ";
        result = "1";
        if (power == 0)
            return result;
        ++i;
        n = i;
        while (n <= power)
        {
            if (i % 2 == 0)
                result.append("+");
            else
                result.append("-");
            if (expanPoint == 0)
                result.append("x^");
            else if (expanPoint > 0)
                result.append("(x-" + to_string(expanPoint) + ")^");
            else
                result.append("(x+" + to_string(expanPoint) + ")^");
            result.append(to_string(n));
            ++i;
            n = i;
        }
        return result;
    case 6:     //1/(1-x)
        cout << "The " << expanPoint << "th order expansion of 1/(1-x) at x equals " << power << " is: ";
        result = "1";
        if (power == 0)
            return result;
        ++i;
        n = i;
        while (n <= power)
        {
            result.append("+");
            if (expanPoint == 0)
                result.append("x^");
            else if (expanPoint > 0)
                result.append("(x-" + to_string(expanPoint) + ")^");
            else
                result.append("(x+" + to_string(expanPoint) + ")^");
            result.append(to_string(n));
            ++i;
            n = i;
        }
        return result;

    }
}
