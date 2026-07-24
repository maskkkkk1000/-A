#include<iostream>
using namespace std;
const int N=15;
int u;
int n;
int Path[N]={0};
bool FT[N]={false};
void dfs(int u)
{
    if(u>n)
    {
        for(int i=1;i<=n;i++)
        {
            cout <<Path[i]<<" ";
        }
        cout <<endl;
    }
    else
    {
        for(int i=1;i<=n;i++)
        {
            if(FT[i]==false)
            {
                Path[u]=i;
                FT[i]=true;
                dfs(u+1);
                Path[u]=0;
                FT[i]=false;
            }
        }
    }
    return;
}
int main()
{
    cin>>n;
    dfs(1);
    return 0;
} 