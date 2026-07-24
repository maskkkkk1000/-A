#include <iostream>
#include <string>
#include <climits>
using namespace std;

int main()
{
    string src, dst;
    cin >> src >> dst;
    int n = src.size();
    int ans = INT_MAX;

    auto flip = [&](string &s, int i)
    {
        s[i] = (s[i] == '0') ? '1' : '0';
        if (i > 0)
            s[i - 1] = (s[i - 1] == '0') ? '1' : '0';
        if (i < n - 1)
            s[i + 1] = (s[i + 1] == '0') ? '1' : '0';
    };

    // Try the two possibilities for the first button
    for (int first = 0; first <= 1; first++)
    {
        string cur = src;
        int cnt = 0;
        if (first)
        {
            flip(cur, 0);
            cnt++;
        }
        for (int i = 1; i < n; i++)
        {
            if (cur[i - 1] != dst[i - 1])
            {
                flip(cur, i);
                cnt++;
            }
        }
        if (cur == dst)
            ans = min(ans, cnt);
    }
    if (ans == INT_MAX)
        cout << "impossible" << endl;
    else
        cout << ans << endl;
    return 0;
}
