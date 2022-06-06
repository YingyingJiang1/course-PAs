#include <iostream>
#include <string.h>
#include <list>
#include <limits>
using namespace std;
#include "parse.h"
#include "eval.h"
#include "def.h"
#include "calcuExpr.h"
extern void Print(struct GLOBAL* head, string str);
extern void ModiVar(char name[], vector<pair<string, string>>toks, struct GLOBAL* head);
extern int InputPrompts(int& expanPoint, int& power, char& ch);
extern map<char, int>p;
int main()
{
    string input, expr;
    int n;
    string result;
    struct GLOBAL* varHead = NULL, * varTail = NULL;
    struct GLOBAL* funcHead = NULL, * funcTail = NULL;
    struct GLOBAL temp;
    string env;
    string funcName, varName;
    int expanPoint, power, sequence;
    char ch;
    p['+'] = p['-'] = 1;//通过hashmap赋值
    p['*'] = p['/'] = p['%'] = 2;
    p['!'] = 3;
    p['#'] = p['$'] = 3;    //# means '+' , '$' means '-'
    while (true)
    {
        bool error = false;
        cout << ">>";
        getline(cin, input);
        n = Parse(input, temp, varHead, funcHead);
        switch (n)
        {
        case 1:
            Def(varHead, varTail, temp);
            break;
        case 2:
            Def(funcHead, funcTail, temp);
            break;
        case 3:
            result = Eval(temp.toks, varHead, funcHead, env, error); //"input" has been modefied(there's no blank)
            if (!error)
                cout << result << endl;
            temp.toks.clear();
            break;
        case 4:
            cout << "Expression Error!" << endl;
            break;
        case 5:
            return 0;
        case 6:
            Print(varHead, "var");
            break;
        case 7:
            Print(funcHead, "func");
            break;
        case 8:
            cout << "The var or func is existed!" << endl;
            break;
        case 9:
            cout << "Function definition can't be changed!" << endl;
            break;
        case 10:
            ModiVar(temp.name, temp.toks, varHead);
            temp.toks.clear();
            memset(temp.name, '\0', sizeof(temp.name));
            break;
        case 11:
            sequence = InputPrompts(expanPoint, power, ch);
            result = EvalTaylorFormula(sequence, expanPoint, power, error, ch);
            if (!error)
                cout << result << endl;
            break;
        default:
            cout << "Input invalid!" << endl;

        }
    }
}

void Print(struct GLOBAL* head, string str)
{
    if (head == NULL)
        cout << "No var or func!" << endl;
    else
    {
        if (str == "var")
        {
            while (head)
            {
                cout << head->name << " = ";
                for (auto it = head->toks.begin(); it != head->toks.end(); ++it)
                {
                    if ((*it).first == "func")
                    {
                        int i = 0;
                        for (; (*it).second[i] != ' '; ++i)
                        {
                            cout << (*it).second[i];
                        }
                        cout << '(';
                        for (int j = i + 1; (*it).second[j] != '\0'; ++j)
                        {
                            if ((*it).second[j] == ' ')
                                cout << ',';
                            else
                                cout << (*it).second[j];
                        }
                        cout << ')';
                    }
                    else
                        cout << (*it).second;
                }
                head = head->next;
                cout << endl;

            }
        }
        else
        {
            while (head)
            {
                cout << head->name << '(';
                auto it = head->args.begin();
                for (; it != head->args.end(); ++it)
                {
                    if (++it == head->args.end())
                        break;
                    --it;
                    cout << (*it).first << ',';
                }
                --it;
                cout << (*it).first << ')' << '=';
                for (auto it = head->toks.begin(); it != head->toks.end(); ++it)
                {
                    if ((*it).first == "func")
                    {
                        int i = 0;
                        for (; (*it).second[i] != ' '; ++i)
                        {
                            cout << (*it).second[i];
                        }
                        cout << '(';
                        for (int j = i + 1; (*it).second[j] != '\0'; ++j)
                        {
                            if ((*it).second[j] == ' ')
                                cout << ',';
                            else
                                cout << (*it).second[j];
                        }
                        cout << ')';
                    }
                    else
                        cout << (*it).second;
                }
                head = head->next;
                cout << endl;
            }

        }
    }

}

void ModiVar(char name[], vector<pair<string, string>>toks, struct GLOBAL* head)
{
    bool find = false;
    while (head)
    {
        if (strcmp(head->name, name) == 0)
        {
            find = true;
            head->toks.clear();
            head->toks = toks;
            cout << "Modify successfully!" << endl;
            break;
        }
        head = head->next;
    }
    if (!find)
        cout << "NameError!" << endl;
}
int InputPrompts(int& expanPoint, int& power, char& ch)
{
    int sequence;
    cout << "*******************************************************************************************************************************" << endl;
    cout << "This calculator only supports expansion of the following functions: " << endl;
    cout << "1:sinx, 2:cosx, 3:e^x,  4:ln(1 + x), 5:1/ (1 +x), 7:1/(1-x)" << endl;
    cout << "*******************************************************************************************************************************" << endl;
    cout << "please Enter the ordinal number of the function you want to expand:";
    cin >> sequence;
    while (cin.fail())
    {
        cout << "Invalid input!" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "please Enter the ordinal number of the function you want to expand: ";
        cin >> sequence;
    }
    cout << "please enter the expansion point:";
    cin >> expanPoint;
    while (cin.fail())
    {
        cout << "Invalid input!" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "please enter the expansion point ";
        cin >> expanPoint;
    }
    cout << "Please enter the power:";
    cin >> power;
    while (cin.fail())
    {
        cout << "Invalid input!" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Please enter the power: ";
        cin >> power;
    }
    cout << "please enter \'y\' or \'n'\'(\'y\' means calculating factorial while \'n\' not):";
    cin >> ch;
    while (ch != 'y' && ch != 'n') {
        cout << "Invalid input!" << endl;
        cin >> ch;
    }
    getchar();  //use to capture \r,or the \r will be caputured by getline as the next input!
    return sequence;
}