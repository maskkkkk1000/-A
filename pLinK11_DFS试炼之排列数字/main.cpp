#include<iostream>
#include<algorithm>
using namespace std;
int fin[10];
bool used[10]={false};
int n;
void dfs(int i)
{
    if(i==n)
    {
        for(int m=0;m<n;m++)
        {
            cout<<fin[m]<<' ';
        }
        cout<<endl;
        return;
    }
    else
    {
        for(int m=1;m<=n;m++)
        {
            if(used[m]==true)
                continue;
            fin[i]=m;
            used[m]=true;
            dfs(i+1);
            used[m]=false;
        }
        return;
    }
}
int main()
{
    cin>>n;
    dfs(0);
    return 0;
}