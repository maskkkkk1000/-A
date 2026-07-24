#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
#include<utility>
using namespace std;
#define N 1007
typedef pair<int,int> PII;
char area[N][N];
int dist[N][N],n,m;
int dx[]={-1,0,1,0},dy[]={0,1,0,-1};
void printDistMap(int n,int m)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
            cout <<dist[i][j]<<" ";
        cout<<endl;
    }
}
void bfs()
{
    queue<PII> q;
    memset(dist,-1,sizeof(dist));
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            if(area[i][j]=='1')
            {
                dist[i][j]=0;
                q.push(make_pair(i,j));
            }
        }
    }
    while(q.size())
    {
        auto t=q.front();
        q.pop();
        for(int i=0;i<4;i++)
        {
            int x=t.first+dx[i],y=t.second+dy[i];
            if(x<0||x>=n||y<0||y>=m||dist[x][y]!=-1) continue;
            dist[x][y]=dist[t.first][t.second]+1;
            q.push({x,y});
        }
    }
}
int main()
{
    cin>>n>>m;
    for(int i=0;i<n;i++)
        cin>>area[i];
    bfs();
    printDistMap(n,m);
    return 0;
}