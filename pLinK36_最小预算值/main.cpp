#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

int n, m;
vector<int> a;

bool check(ll budget)
{
    ll sum = 0;
    int cnt = 1;
    for (int i = 0; i < n; i++)
    {
        if (a[i] > budget)
            return false;
        if (sum + a[i] > budget)
        {
            cnt++;
            sum = a[i];
        }
        else
            sum += a[i];
    }
    return cnt <= m;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    a.resize(n);
    ll lo = 0, hi = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        hi += a[i];
    }
    while (lo < hi)
    {
        ll mid = (lo + hi) / 2;
        if (check(mid))
            hi = mid;
        else
            lo = mid + 1;
    }
    cout << lo << endl;
    return 0;
}
