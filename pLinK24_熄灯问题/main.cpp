#include <iostream>
#include <cstring>
using namespace std;

int light[7][8], press[7][8];

int solve()
{
    // Try all 2^6 = 64 possibilities for first row
    for (int s = 0; s < (1 << 6); s++)
    {
        memset(press, 0, sizeof(press));
        for (int j = 0; j < 6; j++)
            if (s >> j & 1)
                press[1][j + 1] = 1;

        for (int i = 1; i <= 5; i++)
        {
            for (int j = 1; j <= 6; j++)
            {
                int cur = light[i][j] ^ press[i][j] ^ press[i][j - 1] ^ press[i][j + 1] ^ press[i - 1][j];
                press[i + 1][j] = cur;
            }
        }

        bool ok = true;
        for (int j = 1; j <= 6; j++)
            if (light[5][j] ^ press[5][j] ^ press[5][j - 1] ^ press[5][j + 1] ^ press[4][j])
            {
                ok = false;
                break;
            }
        if (ok)
            return s;
    }
    return -1;
}

int main()
{
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++)
    {
        memset(light, 0, sizeof(light));
        for (int i = 1; i <= 5; i++)
            for (int j = 1; j <= 6; j++)
                cin >> light[i][j];

        int s = solve();
        cout << "PUZZLE #" << t << endl;
        for (int i = 1; i <= 5; i++)
        {
            for (int j = 1; j <= 6; j++)
            {
                if (s >= 0)
                    cout << press[i][j];
                else
                    cout << 0;
                if (j < 6)
                    cout << " ";
            }
            cout << " " << endl;
        }
    }
    return 0;
}
