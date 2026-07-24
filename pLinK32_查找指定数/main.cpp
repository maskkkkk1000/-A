#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int main()
{
    int n;
    cin>>n;
    vector<int> num(n);
    for(int i=0;i<n;i++)
    {
        cin>>num[i];
    }
    int nu;
    cin>>nu;
    int target;
    while(cin>>target)
    {
        auto it =find(num.begin(), num.end(), target);
        if (it != num.end()) {
            int index = distance(num.begin(), it); 
            cout << index << "\n";
        } 
        else {
            cout << -1  << "\n";
        }
    }
    return 0;
}