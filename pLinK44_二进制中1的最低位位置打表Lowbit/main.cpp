#include<iostream>
using namespace std;
#define N 16
int log[1<<N];
void BuildlogTable(int n)
{
    for(int i=0;i<=n;i++)
        log[1<<i]=i;
}
inline int lowbit(int n)
{
    return n&-n;
}
int query(int n)
{
    return log[lowbit(n)];
}
int main()
{
    BuildlogTable(N);
    int n;
    cin>>n;
    cout<<query(n);
    return 0;
}