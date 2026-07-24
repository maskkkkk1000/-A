#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

vector<string> ans;
int col[10], diag1[20], diag2[20];
int path[10];

void dfs(int r)
{
    if (r == 9)
    {
        string s;
        for (int i = 1; i <= 8; i++)
            s += char('0' + path[i]);
        ans.push_back(s);
        return;
    }
    for (int c = 1; c <= 8; c++)
    {
        if (col[c] || diag1[r + c] || diag2[r - c + 8])
            continue;
        col[c] = diag1[r + c] = diag2[r - c + 8] = 1;
        path[r] = c;
        dfs(r + 1);
        col[c] = diag1[r + c] = diag2[r - c + 8] = 0;
    }
}

int main()
{
    dfs(1);
    sort(ans.begin(), ans.end());
    int T;
    cin >> T;
    while (T--)
    {
        int n;
        cin >> n;
        cout << ans[n - 1] << endl;
    }
    return 0;
}
