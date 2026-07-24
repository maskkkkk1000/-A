#include<iostream>
#include<cmath>
using namespace std;
int set[100];
int n;
void dfs(int k)
{
    if(k==n)
    {
        for(int i=0;i<n;i++)
            cout<<set[i]+1;
        cout<<endl;
        return;
    }
    for(int i=0;i<n;i++)
    {
        int cou;
        for(cou=0;cou<k;cou++)
        {
            if(set[cou]==i||abs(set[cou]-i)==abs(k-cou)) break;
        }
        if(cou==k)
        {
            set[k]=i;
            dfs(k+1);
        }
    }
}
int main()
{
    cin>>n;
    dfs(0);
    return 0;
}