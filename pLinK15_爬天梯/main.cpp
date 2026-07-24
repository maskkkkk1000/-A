#include<iostream>
using namespace std;
int climb(int n)
{
    if(n<=0)
    return 1;
    else if(n==1)
    return 1;
    else if(n==2)
    return 2;
    else
    return climb(n-1)+climb(n-2); 
}
int main()
{
    int n;
    cin>>n;
    cout<<climb(n)<<endl;
}