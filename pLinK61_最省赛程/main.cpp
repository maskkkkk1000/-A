#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

struct State
{
    int city, fuel, cost;
    bool operator>(const State &o) const { return cost > o.cost; }
};

struct Edge
{
    int to, d;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M;
    cin >> N >> M;
    vector<int> price(N);
    for (int i = 0; i < N; i++)
        cin >> price[i];
    vector<vector<Edge>> g(N);
    while (M--)
    {
        int u, v, d;
        cin >> u >> v >> d;
        g[u].push_back({v, d});
        g[v].push_back({u, d});
    }
    int q;
    cin >> q;
    while (q--)
    {
        int C, S, E;
        cin >> C >> S >> E;
        // Dijkstra on (city, fuel) state
        vector<vector<int>> dist(N, vector<int>(C + 1, 1e9));
        priority_queue<State, vector<State>, greater<State>> pq;
        dist[S][0] = 0;
        pq.push({S, 0, 0});
        int ans = -1;
        while (!pq.empty())
        {
            auto [u, f, c] = pq.top();
            pq.pop();
            if (c != dist[u][f])
                continue;
            if (u == E)
            {
                ans = c;
                break;
            }
            // Option 1: refuel 1 unit
            if (f < C && c + price[u] < dist[u][f + 1])
            {
                dist[u][f + 1] = c + price[u];
                pq.push({u, f + 1, c + price[u]});
            }
            // Option 2: go along edges
            for (auto &e : g[u])
            {
                if (f >= e.d && c < dist[e.to][f - e.d])
                {
                    dist[e.to][f - e.d] = c;
                    pq.push({e.to, f - e.d, c});
                }
            }
        }
        if (ans == -1)
            cout << "impossible" << endl;
        else
            cout << ans << endl;
    }
    return 0;
}
