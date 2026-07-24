#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
string allchar;
char fin[10];
bool used[10];
int n;
void dfs(int i)
{
     if(i==n)
    {
        for(int m=0;m<n;m++)
        {
            cout<<fin[m];
        }
        cout<<endl;
        return;
    }
    else
    {
        for(int m=0;m<n;m++)
        {
            if(used[m]==true)
                continue;
            fin[i]=allchar[m];
            used[m]=true;
            dfs(i+1);
            used[m]=false;
        }
        return;
    }
}
int main()
{
    cin>>allchar;
    n=allchar.size();
    sort(allchar.begin(),allchar.end());
    dfs(0);
    return 0;
}