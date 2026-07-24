#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 16;
int ones[1 << N], cnt[1 << N];
int row[N], col[N], cell[4][4];
char board[N][N];

// Precompute count of 1-bits and lowest set bit index
void init()
{
    for (int i = 0; i < (1 << N); i++)
    {
        int s = 0;
        for (int j = 0; j < N; j++)
            if (i >> j & 1)
                s++;
        ones[i] = s;
    }
    for (int i = 0; i < N; i++)
        cnt[1 << i] = i;
}

int get(int x, int y)
{
    return row[x] & col[y] & cell[x / 4][y / 4];
}

int lowbit(int x)
{
    return x & -x;
}

bool dfs(int left)
{
    if (!left)
        return true;

    // Find the cell with fewest candidates
    int minc = 20, mx = -1, my = -1;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (board[i][j] == '-')
            {
                int cand = get(i, j);
                int c = ones[cand];
                if (c < minc)
                {
                    minc = c;
                    mx = i;
                    my = j;
                }
            }

    if (mx == -1)
        return false;

    int cand = get(mx, my);
    for (int k = cand; k; k -= lowbit(k))
    {
        int v = cnt[lowbit(k)];
        board[mx][my] = 'A' + v;
        row[mx] ^= (1 << v);
        col[my] ^= (1 << v);
        cell[mx / 4][my / 4] ^= (1 << v);
        if (dfs(left - 1))
            return true;
        // backtrack
        board[mx][my] = '-';
        row[mx] ^= (1 << v);
        col[my] ^= (1 << v);
        cell[mx / 4][my / 4] ^= (1 << v);
    }
    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();

    string line;
    while (getline(cin, line))
    {
        // Reset
        for (int i = 0; i < N; i++)
        {
            row[i] = (1 << N) - 1;
            col[i] = (1 << N) - 1;
        }
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                cell[i][j] = (1 << N) - 1;

        // Read first line if not empty
        if (line.empty())
            continue;
        int empty_cnt = 0;
        for (int j = 0; j < N; j++)
        {
            board[0][j] = line[j];
            if (line[j] != '-')
            {
                int v = line[j] - 'A';
                row[0] ^= (1 << v);
                col[j] ^= (1 << v);
                cell[0 / 4][j / 4] ^= (1 << v);
            }
            else
                empty_cnt++;
        }
        for (int i = 1; i < N; i++)
        {
            getline(cin, line);
            for (int j = 0; j < N; j++)
            {
                board[i][j] = line[j];
                if (line[j] != '-')
                {
                    int v = line[j] - 'A';
                    row[i] ^= (1 << v);
                    col[j] ^= (1 << v);
                    cell[i / 4][j / 4] ^= (1 << v);
                }
                else
                    empty_cnt++;
            }
        }

        dfs(empty_cnt);

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
                cout << board[i][j];
            cout << endl;
        }
        cout << endl;
    }
    return 0;
}
