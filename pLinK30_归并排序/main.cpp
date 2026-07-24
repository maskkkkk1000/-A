#include<iostream>
using namespace std;
int num[100010];
int temp[100010];
void mergesort(int num[],int l,int r)
{
    int mid=l+r>>1;
    if(l>=r) return;
    mergesort(num,l,mid);
    mergesort(num,mid+1,r);
    int k=0;
    int p=l,q=mid+1;
    while(p<=mid&&q<=r)
    {
        if(num[p]<=num[q])
            temp[k++]=num[p++];
        else
            temp[k++]=num[q++];
    }
    while(p<=mid)
        temp[k++]=num[p++];
    while(q<=r)
        temp[k++]=num[q++];
    for(int i=0;i<k;i++)
        num[l+i]=temp[i];
}
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++)
        scanf("%d",&num[i]);
    mergesort(num,0,n-1);
    for(int i=0;i<n;i++)
        printf("%d ",num[i]);
    return 0;
}