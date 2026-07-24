#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int dp[25][25][25]; // dp[w][h][m] = min max area

int solve(int w, int h, int m)
{
    if (dp[w][h][m] != -1)
        return dp[w][h][m];
    if (m == 1)
        return dp[w][h][m] = w * h;
    if (w * h == m)
        return dp[w][h][m] = 1;

    int ans = 1e9;
    // Cut horizontally
    for (int i = 1; i < w; i++)
        for (int k = 1; k < m; k++)
        {
            if (k <= i * h && m - k <= (w - i) * h)
                ans = min(ans, max(solve(i, h, k), solve(w - i, h, m - k)));
        }
    // Cut vertically
    for (int i = 1; i < h; i++)
        for (int k = 1; k < m; k++)
        {
            if (k <= w * i && m - k <= w * (h - i))
                ans = min(ans, max(solve(w, i, k), solve(w, h - i, m - k)));
        }
    return dp[w][h][m] = ans;
}

int main()
{
    int w, h, m;
    memset(dp, -1, sizeof(dp));
    while (cin >> w >> h >> m)
    {
        if (w == 0 && h == 0 && m == 0)
            break;
        cout << solve(w, h, m) << endl;
    }
    return 0;
}
