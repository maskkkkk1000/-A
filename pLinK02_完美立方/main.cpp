#include<iostream>
using namespace std;
int main()
{
	int ori;
	cin >> ori;
	int i, j, k;
	int sum;
	for (sum = 1; sum <= ori; sum++)
		for(i=2;i<=sum;i++)
		 for(j=i;j<=sum;j++)
			  for(k=j;k<=sum;k++)
				{
					if (i*i*i + j*j*j + k*k*k == sum*sum*sum)
						cout << "Cube = " << sum << ", Triple = (" << i << "," << j << "," << k << ")" << endl;
				}
	return 0;
}