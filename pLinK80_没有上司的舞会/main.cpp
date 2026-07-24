#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 6010;
int n, happy[N];
vector<int> g[N];
int f[N][2]; // f[u][0] = not choose u, f[u][1] = choose u
bool has_father[N];

void dfs(int u)
{
    f[u][1] = happy[u];
    for (int v : g[u])
    {
        dfs(v);
        f[u][0] += max(f[v][0], f[v][1]);
        f[u][1] += f[v][0];
    }
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> happy[i];
    for (int i = 0; i < n - 1; i++)
    {
        int l, k;
        cin >> l >> k;
        g[k].push_back(l);
        has_father[l] = true;
    }
    int root = 1;
    while (has_father[root])
        root++;
    dfs(root);
    cout << max(f[root][0], f[root][1]) << endl;
    return 0;
}
