#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

// moves[i] which clocks are affected (0-indexed)
const int moves[9][9] = {
    {0, 1, 3, 4, -1},
    {0, 1, 2, -1},
    {1, 2, 4, 5, -1},
    {0, 3, 6, -1},
    {1, 3, 4, 5, 7, -1},
    {2, 5, 8, -1},
    {3, 4, 6, 7, -1},
    {6, 7, 8, -1},
    {4, 5, 7, 8, -1}};

int main()
{
    int clock[9];
    for (int i = 0; i < 9; i++)
        cin >> clock[i];

    vector<int> best;
    // Each move can be applied 0-3 times (4 times = 0)
    for (int a0 = 0; a0 < 4; a0++)
        for (int a1 = 0; a1 < 4; a1++)
            for (int a2 = 0; a2 < 4; a2++)
                for (int a3 = 0; a3 < 4; a3++)
                    for (int a4 = 0; a4 < 4; a4++)
                        for (int a5 = 0; a5 < 4; a5++)
                            for (int a6 = 0; a6 < 4; a6++)
                                for (int a7 = 0; a7 < 4; a7++)
                                    for (int a8 = 0; a8 < 4; a8++)
                                    {
                                        int tmp[9];
                                        for (int i = 0; i < 9; i++)
                                            tmp[i] = clock[i];
                                        int cnt[9] = {a0, a1, a2, a3, a4, a5, a6, a7, a8};
                                        for (int m = 0; m < 9; m++)
                                            for (int k = 0; moves[m][k] != -1; k++)
                                                tmp[moves[m][k]] = (tmp[moves[m][k]] + cnt[m]) % 4;
                                        bool ok = true;
                                        for (int i = 0; i < 9; i++)
                                            if (tmp[i] != 0)
                                                ok = false;
                                        if (!ok)
                                            continue;
                                        vector<int> cur;
                                        for (int m = 0; m < 9; m++)
                                            for (int c = 0; c < cnt[m]; c++)
                                                cur.push_back(m + 1);
                                        if (best.empty() || cur.size() < best.size() ||
                                            (cur.size() == best.size() && cur < best))
                                            best = cur;
                                    }

    for (size_t i = 0; i < best.size(); i++)
    {
        if (i)
            cout << " ";
        cout << best[i];
    }
    cout << endl;
    return 0;
}
