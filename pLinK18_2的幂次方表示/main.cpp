#include <iostream>
#include <string>
using namespace std;

string f(int n)
{
    if (n == 0)
        return "0";
    string res;
    for (int i = 14; i >= 0; i--)
    {
        if (n >> i & 1)
        {
            if (!res.empty())
                res += "+";
            if (i == 1)
                res += "2";
            else
                res += "2(" + f(i) + ")";
        }
    }
    return res;
}

int main()
{
    int n;
    cin >> n;
    cout << f(n) << endl;
    return 0;
}
