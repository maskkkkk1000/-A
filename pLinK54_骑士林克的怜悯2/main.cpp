#include <iostream>
#include <queue>
#include <cstring>
#include <vector>
#include <string>
using namespace std;

struct State
{
    int x, y, step;
};

const int dx[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
const int dy[8] = {-1, 1, -2, 2, -2, 2, -1, 1};

int main()
{
    int C, R;
    while (cin >> C >> R)
    {
        vector<string> g(R);
        int sx = -1, sy = -1, tx = -1, ty = -1;
        for (int i = 0; i < R; i++)
        {
            cin >> g[i];
            for (int j = 0; j < C; j++)
            {
                if (g[i][j] == 'K')
                {
                    sx = i;
                    sy = j;
                }
                if (g[i][j] == 'H')
                {
                    tx = i;
                    ty = j;
                }
            }
        }
        vector<vector<int>> dist(R, vector<int>(C, -1));
        queue<State> q;
        q.push({sx, sy, 0});
        dist[sx][sy] = 0;
        int ans = -1;
        while (!q.empty())
        {
            auto cur = q.front();
            q.pop();
            if (cur.x == tx && cur.y == ty)
            {
                ans = cur.step;
                break;
            }
            for (int d = 0; d < 8; d++)
            {
                int nx = cur.x + dx[d];
                int ny = cur.y + dy[d];
                if (nx >= 0 && nx < R && ny >= 0 && ny < C && g[nx][ny] != '*' && dist[nx][ny] == -1)
                {
                    dist[nx][ny] = cur.step + 1;
                    q.push({nx, ny, cur.step + 1});
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}
