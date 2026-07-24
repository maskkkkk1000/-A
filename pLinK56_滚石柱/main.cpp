#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

// 定义地图的最大长宽
const int N = 510;

// 存储石柱的状态结构体
struct State {
    int x, y, lie; // x, y 代表左上角位置；lie 代表状态 (0:立, 1:横躺, 2:竖躺)
};

int n, m; // 地图的行数和列数
char g[N][N]; // 存储地图字符
int dist[N][N][3]; // 存储从起点到当前状态的最少步数，同时充当“判重”数组

// 状态转移向量表：4个方向（上、下、左、右）在3种不同状态(lie=0, 1, 2)下的坐标和状态变化
// next_state[lie][dir] = {dx, dy, next_lie}
// 注意：这里的dx, dy是目标状态的“左上角”相对于当前状态“左上角”的相对偏移量
int next_state[3][4][3] = {
    // lie = 0 (立着)
    {
        {-2, 0, 2}, // 上：向上翻转，左上角往上移动2格，变为竖躺
        {1, 0, 2},  // 下：向下翻转，左上角往下移动1格，变为竖躺
        {0, -2, 1}, // 左：向左翻转，左上角往左移动2格，变为横躺
        {0, 1, 1}   // 右：向右翻转，左上角往右移动1格，变为横躺
    },
    // lie = 1 (横躺着，占据 (x, y) 和 (x, y+1))
    {
        {-1, 0, 1}, // 上：整体向上滚一格，左上角往上移动1格，仍是横躺
        {1, 0, 1},  // 下：整体向下滚一格，左上角往下移动1格，仍是横躺
        {0, -1, 0}, // 左：向左立起来，左上角往左移动1格，变为立着
        {0, 2, 0}   // 右：向右立起来，左上角往右移动2格，变为立着
    },
    // lie = 2 (竖躺着，占据 (x, y) 和 (x+1, y))
    {
        {-1, 0, 0}, // 上：向上立起来，左上角往上移动1格，变为立着
        {2, 0, 0},  // 下：向下立起来，左上角往下移动2格，变为立着
        {0, -1, 2}, // 左：整体向左滚一格，左上角往左移动1格，仍是竖躺
        {0, 1, 2}   // 右：整体向右滚一格，左上角往右移动1格，仍是竖躺
    }
};

// 检查坐标 (x, y) 是否在地图合法边界内
bool check_bound(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

// 检查当前状态是否合法（不越界、不踩悬崖、立着时不踩易碎地面）
bool is_valid(State s) {
    // 首先检查左上角坐标是否越界，或者是否踩到悬崖 '#'
    if (!check_bound(s.x, s.y) || g[s.x][s.y] == '#') return false;

    // 分情况检查石柱占据的其余部分
    if (s.lie == 0) {
        // 立着的时候，不能踩在易碎地面 'E' 上
        if (g[s.x][s.y] == 'E') return false;
    }
    else if (s.lie == 1) {
        // 横躺时，检查右侧相邻格子 (x, y+1) 是否越界或踩到悬崖
        if (!check_bound(s.x, s.y + 1) || g[s.x][s.y + 1] == '#') return false;
    }
    else if (s.lie == 2) {
        // 竖躺时，检查下方相邻格子 (x+1, y) 是否越界或踩到悬崖
        if (!check_bound(s.x + 1, s.y) || g[s.x + 1][s.y] == '#') return false;
    }
    
    // 所有检查都通过，状态合法
    return true;
}

// 广度优先搜索求最短步数
int bfs(State start, State end) {
    // 初始化步数数组为 -1，代表该状态尚未到达
    memset(dist, -1, sizeof dist);
    
    queue<State> q; // 定义 BFS 队列
    dist[start.x][start.y][start.lie] = 0; // 起点步数初始化为 0
    // 注意：由于上面多打了一个start，修正为：
    dist[start.x][start.y][start.lie] = 0; 
    q.push(start); // 将起点状态入队

    while (!q.empty()) {
        auto t = q.front(); // 取出队头状态
        q.pop(); // 弹出队头

        // 如果当前状态就是终点（立在终点 'O' 上），直接返回步数
        if (t.x == end.x && t.y == end.y && t.lie == end.lie) return dist[t.x][t.y][t.lie];

        // 尝试向 4 个方向滚动
        for (int i = 0; i < 4; i++) {
            // 根据当前状态的 lie 和滚动方向 i，计算下一步的状态
            int next_x = t.x + next_state[t.lie][i][0];
            int next_y = t.y + next_state[t.lie][i][1];
            int next_lie = next_state[t.lie][i][2];

            State next_s = {next_x, next_y, next_lie}; // 封装成新状态

            // 1. 检查新状态是否合法；2. 检查新状态是否之前已经访问过 (dist == -1 代表未访问)
            if (is_valid(next_s) && dist[next_x][next_y][next_lie] == -1) {
                dist[next_x][next_y][next_lie] = dist[t.x][t.y][t.lie] + 1; // 步数 + 1
                q.push(next_s); // 新状态入队
            }
        }
    }

    // 若队列为空仍未找到终点，说明无法到达，返回 -1
    return -1;
}

int main() {
    // 循环读入地图的长宽，当 n 和 m 均为 0 时结束输入
    while (cin >> n >> m, n || m) {
        // 读入整张地图
        for (int i = 0; i < n; i++) cin >> g[i];

        State start, end; // 定义起点和终点状态

        // 扫描地图，寻找起点 'X' 和终点 'O'
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (g[i][j] == 'X') { // 找到了石柱的一部分
                    // 如果它右边也是 'X'，说明初始状态是横躺 (lie=1)
                    if (i + 1 < n && g[i + 1][j] == 'X') {
                        start = {i, j, 2}; // 此时 (i,j) 是左上角，状态为竖躺
                        g[i][j] = g[i + 1][j] = '.'; // 将其还原为普通地面，避免干扰后续判断
                    }
                    // 如果它下方也是 'X'，说明初始状态是竖躺 (lie=2)
                    else if (j + 1 < m && g[i][j + 1] == 'X') {
                        start = {i, j, 1}; // 此时 (i,j) 是左上角，状态为横躺
                        g[i][j] = g[i][j + 1] = '.'; // 还原为普通地面
                    }
                    // 如果孤立一个 'X'，说明初始状态是立着的 (lie=0)
                    else {
                        start = {i, j, 0};
                        g[i][j] = '.'; // 还原为普通地面
                    }
                }
                else if (g[i][j] == 'O') { // 找到了目标终点
                    end = {i, j, 0}; // 题目要求石柱最终要“立”在终点上
                }
            }
        }

        // 运行 BFS 并输出结果
        int res = bfs(start, end);
        if (res == -1) cout << "Impossible" << endl; // 无法到达
        else cout << res << endl; // 输出最少步数
    }

    return 0;
}