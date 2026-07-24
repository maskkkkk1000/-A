#include<iostream>
#include<algorithm>
using namespace std;
const int N=110;
int n,m;
int w[N][N];
int f[N][N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                scanf("%d",&w[i][j]);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                f[i][j]=max(f[i-1][j],f[i][j-1])+w[i][j];
        printf("%d\n",f[n][m]);

    }
    return 0;
}