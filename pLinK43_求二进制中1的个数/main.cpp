#include <iostream>
using namespace std;

int main()
{
    int x;
    while (cin >> x)
    {
        int cnt = 0;
        while (x)
        {
            x &= x - 1; // lowbit: remove the lowest 1-bit
            cnt++;
        }
        cout << cnt << endl;
    }
    return 0;
}
