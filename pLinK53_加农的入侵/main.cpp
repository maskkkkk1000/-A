#include<algorithm>
#include<queue>
#include<iostream>
#include<cstring>
using namespace std;
typedef pair<int ,int> PII;
const int N=110;
int n,m;
PII start;
char g[N][N];
int dist[N][N];
const int dx[8]={1,-1,0,0,1,-1,1,-1};
const int dy[8]={0,0,1,-1,1,-1,-1,1};
int bfs()
{
    memset(dist,-1,sizeof dist);
    queue<PII> q;
    q.push(start);
    dist[start.first][start.second]=0;
    int res=0;
    while(q.size())
    {
        auto t=q.front();
        q.pop();
        for (int i = 0; i < 8; i++)
        {
            int x=t.first+dx[i];
            int y=t.second+dy[i];
            if(x<1||x>n||y<1||y>m) continue;
            if(g[x][y]=='*'||dist[x][y]!=-1) continue;
            dist[x][y]=dist[t.first][t.second]+1;
            res=max(res,dist[x][y]);
            q.push(make_pair(x,y));
        }
        
    }
    return res;
}
int main()
{
    cin>>m>>n>>start.second>>start.first;
    start.first=n+1-start.first;
    for (int i = 1; i <= n; i++)
    {
        cin >> g[i]+1;
    }
    cout<<bfs()<<endl;
    return 0;
    
}