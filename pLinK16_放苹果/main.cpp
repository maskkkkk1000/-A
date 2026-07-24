#include<iostream>
using namespace std;
int put(int apple,int plate)
{
    if(apple==0) return 1;
    else if(plate==0) return 0;
    else if(apple<plate) return put(apple,apple);
    else
    {
        return put(apple - plate, plate) + put(apple, plate - 1);
    }
}
int main()
{
    int t;
    int m,n;
    cin>>t;
    while(t--)
    {
        cin>>m>>n;
        cout<<put(m,n)<<endl;
    }
    return 0;
}