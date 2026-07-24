#include<iostream>
#include<vector>
using namespace std;
int main()
{
    int sum;
    cin>>sum;
    int n;
    cin>>n;
    vector<int> num(n);
    for(int i=0;i<n;i++)
    {
        cin>>num[i];
    }
    int temp;
    for(int i=0;i<n;i++)
        for(int j=i+1;j<n;j++)
        {
            temp=num[i]+num[j];
            if(temp==sum)
                cout<<i<<' '<<j;
        }
    return 0;
}