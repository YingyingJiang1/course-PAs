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
struct Node {
    double num;//操作数
    char op;//操作符
    bool flag;//true表示操作数，false表示操作符
};
typedef struct Node node;
stack<node> s;//操作符栈
stack<node> s1;//存放操作数的，为了计算后缀表达式的值
queue<node> q;//后缀表达式队列
map<char, int> p;
void Init()
{
    while (!q.empty())
        q.pop();
    while (!s.empty())
        s.pop();
    while (!s1.empty())
        s1.pop();

}
string GetStr(vector<pair<string, string>>toks)
{
    string str = "";
    for (auto it = toks.begin(); it != toks.end(); ++it)
        str.append((*it).second);
    return str;
}
string convertToString(double d) {
    ostringstream os;
    if (os << d)
        return os.str();
}
//中缀转后缀函数
void change(string str) {
    node temp;
    for (unsigned int i = 0; i < str.length();) {
        if (str[i] == '(') {//3.遇到左括号：将其入栈
            temp.flag = false;
            temp.op = str[i];
            s.push(temp);
            i++;
        }
        else if (str[i] == ')') {//4.遇到右括号：执行出栈操作，输出到后缀表达式，直到弹出的是左括号
            while (!s.empty() && s.top().op != '(') {
                q.push(s.top());
                s.pop();
            }
            s.pop();//弹出左括号
            i++;
        }
        else if (str[i] >= '0' && str[i] <= '9') {
            //如果是数字
            temp.flag = true;
            temp.num = str[i] - '0';
            i++;//后移一位,因为数字不一定是个位数
            while (i < str.length() && str[i] >= '0' && str[i] <= '9') {
                temp.num = temp.num * 10 + (str[i] - '0');
                i++;
            }
            if (str[i] == '.')
            {
                ++i;
                int count = 1;
                while (i < str.length() && str[i] >= '0' && str[i] <= '9') {
                    temp.num = temp.num + (str[i] - '0') * pow(0.1, count);
                    i++;
                    ++count;
                }
            }                    
            q.push(temp);//操作数进入后缀表达式
        }
        else {
            //如果是操作符
            //5.遇到其他运算符：弹出所有优先加大于或等于该运算符的栈顶元素，然后将该运算符入栈
            temp.flag = false;
            while (!s.empty() && p[s.top().op] >= p[str[i]]) {
                q.push(s.top());
                s.pop();
            }
            temp.op = str[i];
            s.push(temp);
            i++;
        }
    }
    //6.将栈中剩余内容依次弹出后缀表达式
    while (!s.empty()) {
        q.push(s.top());
        s.pop();
    }
}


string  Calculate(bool &error) {
    if(!q.front().flag && q.front().op == '#' || q.front().op == '$'){

    }
    double num_a, num_b;//操作数a,b
    node cur, temp;
    while (!q.empty()) {//后缀队列非空
        cur = q.front();//记录队首元素
        q.pop();
        if (cur.flag == true) {//是操作数进入栈
            s1.push(cur);
            
        }
        else {//是操作符就运算
            
            temp.flag = true;            
            num_b = s1.top().num;//双目运算的右操作数
            s1.pop();                           
            if(cur.op == '!')
            {
                double result = 1;
                while(num_b > 0)
                {
                    result *= num_b;
                    --num_b;
                }
                temp.num = result;
            }
            else if(cur.op == '#'){
                
                temp.num = num_b + 1;
                
            }
            else if(cur.op == '$'){
                temp.num = num_b - 1;
                
            }
            else{
                    num_a = s1.top().num;//双目运算的左操作数
                    s1.pop();
                    if (cur.op == '+') {
                        temp.num = num_a + num_b;
                    }
                    else if (cur.op == '-') {
                        temp.num = num_a - num_b;

                    }
                    else if (cur.op == '*') {
                        temp.num = num_a * num_b;
                    }
                    else if(cur.op == '/'){
                        if (num_b == 0)
                        {
                            error = true;
                            cout << "divide by zero!" << endl;
                            return "0";
                        }
                        else
                            temp.num = num_a / num_b;
                    }
                    else if(cur.op == '%'){
                        if (num_b == 0)
                        {
                            error = true;
                            cout << "divide by zero!" << endl;
                            return "0";
                        }
                        else
                            temp.num = fmod(num_a, num_b);
                    } 
                }            
            s1.push(temp);//把计算后的结果再次压栈
            
        }
    }
    return convertToString(s1.top().num);

}

