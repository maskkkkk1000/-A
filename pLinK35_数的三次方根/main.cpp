#include<iostream>
#include<cmath>
using namespace std;
double tar;
bool f(double x)
{
    double res=x*x*x;
    if(res<tar) return true;
    else return false;
}
inline double fn(double x)
{
    return x*x*x;
}
double deep(double m,double n)
{
    double mid=(m+n)/2;
    if(abs(fn(mid)-tar)<1e-10)
    return mid;
    if(f(m)!=f(mid))
    return deep(m,mid);
    else
    return deep(mid,n);
}
int main()
{
    cin>>tar;
    printf("%.6f",deep(-100,100));
    return 0;
}