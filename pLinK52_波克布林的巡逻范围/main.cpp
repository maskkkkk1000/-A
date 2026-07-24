#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
char che[55][55];
typedef pair <int ,int> PII;
int k,m,n;
int posum(int i,int j)
{
    int temp=0;
    while(i!=0)
    {
        temp=temp+i%10;
        i=i/10;
    }
    while(j!=0)
    {
        temp=temp+j%10;
        j=j/10;
    }
    return temp;
}
int bfs(int ox,int oy)
{
    int res=0;
    queue <PII> q;
    q.push({ox,oy});
    che[ox][oy]='#';
    int dx[]={-1,0,1,0},dy[]={0,-1,0,1};
    while(q.size()!=0)
    {
        auto t=q.front();
        q.pop();
        res++;
        for (int i = 0; i < 4; i++)
        {
            int x=t.first+dx[i];
            int y=t.second+dy[i];
            if(x<0||y<0||posum(x,y)>k||x>=m||y>=n||che[x][y]=='#') continue;
            che[x][y]='#';
            q.push({x,y});
        }
        
    }
    return  res;
}
int main()
{
    cin>>k>>m>>n;
    if(m==0||n==0)
    {
        cout<<0<<endl;
        return 0;
    } 
    cout<<bfs(0,0)<<endl;
    return 0;
}