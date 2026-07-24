#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
const double PI = 3.141592653589793;

int n, f;
vector<int> r;

bool check(double vol)
{
    int cnt = 0;
    for (int i = 0; i < n; i++)
    {
        double cake = PI * r[i] * r[i];
        cnt += (int)(cake / vol);
    }
    return cnt >= f + 1;
}

int main()
{
    cin >> n >> f;
    r.resize(n);
    double lo = 0, hi = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> r[i];
        hi = max(hi, PI * r[i] * r[i]);
    }
    for (int i = 0; i < 100; i++)
    {
        double mid = (lo + hi) / 2;
        if (check(mid))
            lo = mid;
        else
            hi = mid;
    }
    printf("%.3f\n", lo);
    return 0;
}
