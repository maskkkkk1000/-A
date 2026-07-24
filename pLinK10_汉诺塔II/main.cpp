#include<iostream>
using namespace std;
void hanoi(int n,int id,char start,char process,char target)
{
    if(n==1)
    {
        cout<<id<<":"<<start<<"->"<<target<<endl;
    }
    else
    {
        hanoi(n-1,1,start,target,process);
        hanoi(1,n,start,process,target);
        hanoi(n-1,1,process,start,target);
    }
    return;
}
int main()
{
    int n;
    char a,b,c;
    cin>>n;
    cin>>a>>b>>c;
    hanoi(n,n,a,b,c);
    return 0;
}