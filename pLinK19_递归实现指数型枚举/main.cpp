#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=153;
bool s[N];
int n;
void d(int u)
{
    if(u>n)
    {
        for(int i=1;i<=n;i++)
        {
            if(s[i])
            cout <<i<<" ";
        }
        cout<<endl;
        return;
    }
    s[u]=true;
    d(u+1);
    s[u]=false;
    d(u+1);
}
int main()
{
    cin>>n;
    d(1);
    return 0;
}