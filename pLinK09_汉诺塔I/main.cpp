#include <iostream>
using namespace std;

void hanoi(int n, char from, char via, char to)
{
    if (n == 1)
    {
        cout << from << "->" << to << endl;
    }
    else
    {
        hanoi(n - 1, from, to, via);
        hanoi(1, from, via, to);
        hanoi(n - 1, via, from, to);
    }
}

int main()
{
    int n;
    cin >> n;
    hanoi(n, 'A', 'B', 'C');
    return 0;
}
