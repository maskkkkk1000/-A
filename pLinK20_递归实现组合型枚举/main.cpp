#include<iostream>
using namespace std;
int n,m;
int u;
const int N=30;
int Path[N]={0};
void co(int u,int start)
{
    if(u>m)
    {
        for(int i=1;i<=m;i++)
        {
            cout<<Path[i]<<" ";
        }
        cout<<endl;
    }
    else
    {
        for(int i=start;i<=n;i++)
        {
            Path[u]=i;
            co(u+1,i+1);
            Path[u]=0;
        }
    }
    return ;
}

int main()
{
    cin>>n>>m;
    co(1,1);
    return 0;
}