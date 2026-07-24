#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n=0;
        cin>>n;
        vector<int> num;
        for(int i=0;i<n;i++)
        {
            int temp;
            cin>>temp;
            num.push_back(temp);
        }
        sort(num.begin(),num.end());
        int j;
        for(j=0;j<n-1;j++)
        {
            cout<<num[j]<<" ";
        }
        cout<<num[j]<<endl;
    }
	return 0;
}