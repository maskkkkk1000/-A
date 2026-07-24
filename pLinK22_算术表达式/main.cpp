#include <iostream>
#include <string>
using namespace std;
using ll = long long;
const ll MOD = 1000000007;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    string expr;
    cin >> N >> expr;
    // First pass: handle all * (higher precedence)
    // Stack-based: numbers with + between them
    ll ans = 0;
    ll cur = 0;
    char prev_op = '+';
    for (int i = 0; i < N; i++)
    {
        int num = expr[i * 2] - '0';
        if (prev_op == '+')
        {
            ans = (ans + cur) % MOD;
            cur = num;
        }
        else // '*'
        {
            cur = (cur * num) % MOD;
        }
        if (i < N - 1)
            prev_op = expr[i * 2 + 1];
    }
    ans = (ans + cur) % MOD;
    cout << ans << endl;
    return 0;
}
