#include <iostream>
#include <cstring>
using namespace std;

const int N = 15;
int n;
char g[N][N];
bool col[N], diag1[N * 2], diag2[N * 2];

void dfs(int r)
{
    if (r == n)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                cout << g[i][j];
            cout << endl;
        }
        cout << endl;
        return;
    }
    for (int c = 0; c < n; c++)
    {
        if (col[c] || diag1[r + c] || diag2[r - c + n])
            continue;
        g[r][c] = 'Q';
        col[c] = diag1[r + c] = diag2[r - c + n] = true;
        dfs(r + 1);
        col[c] = diag1[r + c] = diag2[r - c + n] = false;
        g[r][c] = '.';
    }
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            g[i][j] = '.';
    dfs(0);
    return 0;
}
