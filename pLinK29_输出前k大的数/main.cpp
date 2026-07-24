#include<iostream>
#include<utility>
using namespace std;
const int N=100010;
int q[N];
 void qs(int q[],int l,int r)
{
    if(l>=r) return;
    int i=l-1,j=r+1,x=q[(l+r)>>1];
    while(i<j)
    {
        do i++;while(q[i]<x);
        do j--;while(q[j]>x);
        if(i<j) swap(q[i],q[j]);
    }
    qs(q,l,j);
    qs(q,j+1,r);

}
int main()
{
    int n,k;
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        scanf("%d",&q[i]);
    }
    scanf("%d",&k);
    qs(q,0,n-1);
    for(int i=0;i<k;i++)
        printf("%d\n",q[n-i-1]);
    return 0;
}