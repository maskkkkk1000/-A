#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

ll merge(vector<int> &a, int l, int mid, int r)
{
    vector<int> tmp(r - l + 1);
    int i = l, j = mid + 1, k = 0;
    ll cnt = 0;
    while (i <= mid && j <= r)
    {
        if (a[i] <= a[j])
            tmp[k++] = a[i++];
        else
        {
            tmp[k++] = a[j++];
            cnt += mid - i + 1;
        }
    }
    while (i <= mid)
        tmp[k++] = a[i++];
    while (j <= r)
        tmp[k++] = a[j++];
    for (i = l; i <= r; i++)
        a[i] = tmp[i - l];
    return cnt;
}

ll mergeSort(vector<int> &a, int l, int r)
{
    if (l >= r)
        return 0;
    int mid = (l + r) / 2;
    ll cnt = mergeSort(a, l, mid);
    cnt += mergeSort(a, mid + 1, r);
    cnt += merge(a, l, mid, r);
    return cnt;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    cout << mergeSort(a, 0, n - 1) << endl;
    return 0;
}
