#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
const int INF = 1e9;

int V, N, ans = INF;

// min volume for remaining layers
int minV[25], minS[25];

void dfs(int layer, int sumV, int sumS, int r, int h)
{
    if (layer == 0)
    {
        if (sumV == V)
            ans = min(ans, sumS);
        return;
    }
    // Pruning
    if (sumV + minV[layer] > V)
        return;
    if (sumS + minS[layer] >= ans)
        return;
    // The max volume achievable from here
    int maxV = 0;
    for (int i = layer, rr = r - 1, hh = h - 1; i >= 1; i--, rr--, hh--)
        maxV += rr * rr * hh;
    if (sumV + maxV < V)
        return;

    // Try next radius and height
    for (int i = r - 1; i >= layer; i--)
    {
        for (int j = h - 1; j >= layer; j--)
        {
            int v = i * i * j;
            if (sumV + v > V)
                continue;
            int extraS = 2 * i * j;
            if (layer == N)
                extraS += i * i; // top surface of bottom layer
            dfs(layer - 1, sumV + v, sumS + extraS, i, j);
        }
    }
}

int main()
{
    cin >> V >> N;
    // Precompute min volume & surface for remaining k layers
    for (int i = 1; i <= N; i++)
    {
        minV[i] = minV[i - 1] + i * i * i;
        minS[i] = minS[i - 1] + 2 * i * i;
    }
    // The bottom layer cannot be too large
    int maxR = sqrt(V) + 1;
    int maxH = V + 1;
    dfs(N, 0, 0, maxR, maxH);
    cout << (ans == INF ? 0 : ans) << endl;
    return 0;
}
