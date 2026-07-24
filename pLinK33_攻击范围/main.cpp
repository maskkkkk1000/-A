#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    while (q--)
    {
        int x;
        cin >> x;
        auto l = lower_bound(a.begin(), a.end(), x);
        auto r = upper_bound(a.begin(), a.end(), x);
        if (l == a.end() || *l != x)
            cout << "-1 -1\n";
        else
            cout << (l - a.begin()) << " " << (r - a.begin() - 1) << "\n";
    }
    return 0;
}
