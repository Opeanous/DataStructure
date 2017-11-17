#include <iostream>
#include <stack>
#include <vector>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 1000
using namespace std;
//????????????????????
int is_op(char op) {
    if(op == '+' || op == '-' || op == '*' || op == '/' || op == '%')
        return 1;
    else return 0;
}
//??????????????????????????????
int priority(char op) {
    if(op == '(')
        return 0;
    else if(op == '+' || op == '-')
        return 1;
    else if(op == '*' || op == '/')
        return 2;
    else return -1;
}
//???????????
void print_stack(stack<char>s, int m) {
    stack<char>n;
    int i;
    printf("?????????\n");
    for(i = m - 1; i >= 0; i--)
    {
        printf("%c\n", s.top());
        n.push(s.top());
        s.pop();
    }
    printf("---bottom---\n");
    for(i = 0; i <= m - 1; i++)
    {
        s.push(n.top());
        n.pop();
    }
}
//???????????
void print_stack_float(stack<float>s, int m) {
    stack<float>n;
    int i;
    printf("?????????\n");
    for(i = m - 1; i >= 0; i--)
    {
        printf("%f\n", s.top());
        n.push(s.top());
        s.pop();
    }
    printf("---bottom---\n");
    for(i = 0; i <= m - 1; i++)
    {
        s.push(n.top());
        n.pop();
    }
}
//????????????????????
void in2su(string s, vector<char> &v) {
    int i = 1, len = s.length();
    stack<char>stk;
    v.push_back(s[1]);
    for(i = 2; i < len - 1; i++)
    {
        if((s[i] >= '0' && s[i] <= '9') || s[i] == '.' ||(s[i] >= 'a' && s[i] <= 'z'))//???????????????
        {
            v.push_back(s[i]);
        }

        else if(s[i] == '(')//?????????????????????????????????????????
            stk.push(s[i]);

        else if(s[i] == ')')
        {
            while(stk.top() != '(')
        {
            v.push_back(' ');
            v.push_back(stk.top());

            stk.pop();
        }
        stk.pop();

        }
        else if(is_op(s[i]))
        {
          if(!stk.empty())
          {

              while(!stk.empty() && priority(s[i]) <= priority(stk.top()))
              {
                  v.push_back(' ');
                  v.push_back(stk.top());
                  stk.pop();
              }

        }

        stk.push(s[i]);
        v.push_back(' ');
        }

    print_stack(stk,stk.size());
    }
    while(!stk.empty())//?????????????????????????????
    {
        v.push_back(' ');
        v.push_back(stk.top());
        v.push_back(' ');
        stk.pop();
        print_stack(stk,stk.size());
    }
}
//??????????
float cal_suffix(vector<char>&v) {
    int i = 0, j = 0;
    float sum_float = 0, sum_int = 0, a, b, x;
    int flag = 0;
    int sat = 0;
    stack<float>result;
     //printf("????????????,???????????0\n");
         //scanf("%f", &x);



    for(i; i < v.size(); i++)   //???????????
    {
        if(v[i] == '-' && v[i + 1] != ' ')
            sat = 1;

        if(v[i] >= '0' && v[i] <= '9' && flag == 0)
        {
            sum_int *= 10;
            sum_int += (v[i] - '0');
        }
        else if(v[i] == '.')
        {
            flag = 1;
        }
        else if(v[i] >= '0' && v[i] <= '9' && flag == 1)
        {
          sum_float *= 10;
          sum_float += (v[i] - '0');
          ++j;
        }
        else if(v[i] == ' ' && (v[i - 1] >= '0' && v[i - 1] <= '9') && sat == 1)
        {
             result.push(-(float)(sum_int + (float)sum_float / pow(10, j)));
             sum_int = 0;
             sum_float = 0;
             flag = 0;
             j = 0;
             print_stack_float(result, result.size());
             sat = 0;
        }
        else if(v[i] == ' ' && (v[i - 1] >= '0' && v[i - 1] <= '9') && sat == 0)
        {
             result.push((float)(sum_int + (float)sum_float / pow(10, j)));
             sum_int = 0;
             sum_float = 0;
             flag = 0;
             j = 0;
             print_stack_float(result, result.size());

        }
        else if(v[i] >= 'a' && v[i] <= 'z')
        {
            result.push(x);
        }
        else if(v[i] == '+')
        {
            a = result.top();
            result.pop();
            b= result.top();
            result.pop();
            result.push(b + a);
            print_stack_float(result, result.size());
        }
        else if(v[i] == '-' && v[i + 1] == ' ')
        {
           a = result.top();
            result.pop();
            b= result.top();
            result.pop();
            result.push(b - a);
            print_stack_float(result, result.size());
        }
        else if(v[i] == '*')
        {
            a = result.top();
            result.pop();
            b= result.top();
            result.pop();
            result.push(b * a);
            print_stack_float(result, result.size());
        }
        else if(v[i] == '/')
        {
            a = result.top();
            result.pop();
            b= result.top();
             result.pop();
            result.push(b / a);
            print_stack_float(result, result.size());
        }
        else if(v[i] == '%')
        {
          a = result.top();
            result.pop();
            b= result.top();
             result.pop();
            result.push((int)b % (int)a);
            print_stack_float(result, result.size());
        }
        else
        {

            continue;

        }
    }
    return result.top();
}

int main()
{

    int i;
    char ar[1000];
    vector<char>vec;
    FILE *fp = fopen("test.txt", "r");
    fgets(ar, 1000, fp);
    string infix_expression(ar);
    fclose(fp);
    printf("??????????\n");
    for(i = 1; i < infix_expression.length() - 1; i++)
        printf("%c", infix_expression[i]);
    printf("\n");
    in2su(infix_expression, vec);
    printf("suffix expression:");
    for(i = 0; i < vec.size(); i++)
        printf("%c",vec[i]);
    printf("\n????????????\n");

    cout << "?????????" << cal_suffix(vec) << endl;
    return 0;
}
