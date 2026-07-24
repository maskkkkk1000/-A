#include<iostream>
#include<vector>
#include<algorithm>
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
    sort(num.begin(),num.end());
    int temp;
    for(int i=0;i<n;i++)
    for(int i2=i+1;i2<n;i2++)
    {
        int j = i2 + 1;
        int k = n - 1;
        while (j < k) 
        {
            temp = num[i] + num[i2] + num[j] + num[k];
            
            if (temp == sum) 
            {
                cout << num[i] << ' ' << num[i2] << ' ' << num[j] << ' ' << num[k] << endl;
                j++;
                k--;
            } 
            else if (temp < sum) 
            {
                j++;
            } 
            else 
            {
                k--;
            }
        }
    }
    return 0;
}