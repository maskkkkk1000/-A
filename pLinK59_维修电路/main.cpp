#include <iostream>
#include <deque>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

struct Node
{
    int x, y;
};

const int dx[4] = {-1, -1, 1, 1};
const int dy[4] = {-1, 1, -1, 1};
const int ix[4] = {-1, -1, 0, 0};
const int iy[4] = {-1, 0, -1, 0};
// actual wire directions for '/' and '\'
// '/' connects (0,1) and (1,0), i.e., top-right and bottom-left
// '\' connects (0,0) and (1,1), i.e., top-left and bottom-right
const char wire[4] = {'\\', '/', '/', '\\'};

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        int R, C;
        cin >> R >> C;
        vector<string> g(R);
        for (int i = 0; i < R; i++)
            cin >> g[i];

        // 0-1 BFS: distance to each node (R+1)x(C+1)
        vector<vector<int>> dist(R + 1, vector<int>(C + 1, 1e9));
        deque<Node> dq;
        dq.push_back({0, 0});
        dist[0][0] = 0;

        while (!dq.empty())
        {
            auto cur = dq.front();
            dq.pop_front();
            int x = cur.x, y = cur.y;

            for (int d = 0; d < 4; d++)
            {
                int nx = x + dx[d], ny = y + dy[d];
                if (nx < 0 || nx > R || ny < 0 || ny > C)
                    continue;
                int gx = x + ix[d], gy = y + iy[d];
                // If current wire matches this diagonal, cost 0, else 1
                int cost = (g[gx][gy] == wire[d]) ? 0 : 1;
                if (dist[x][y] + cost < dist[nx][ny])
                {
                    dist[nx][ny] = dist[x][y] + cost;
                    if (cost == 0)
                        dq.push_front({nx, ny});
                    else
                        dq.push_back({nx, ny});
                }
            }
        }
        if (dist[R][C] == 1e9)
            cout << "NO SOLUTION" << endl;
        else
            cout << dist[R][C] << endl;
    }
    return 0;
}
