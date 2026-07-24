#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
using namespace std;

double eval()
{
    char s[20];
    if (!(cin >> s))
        return 0;
    if (strlen(s) == 1 && (s[0] == '+' || s[0] == '-' || s[0] == '*' || s[0] == '/'))
    {
        double a = eval();
        double b = eval();
        switch (s[0])
        {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
        }
    }
    return atof(s);
}

int main()
{
    double res = eval();
    printf("%f\n", res);
    return 0;
}
