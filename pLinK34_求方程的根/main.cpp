#include<iostream>
#include<cmath>
using namespace std;
bool f(double x)
{
    double res=x*x*x-5*x*x+10*x-80;
    if(res<0) return true;
    else return false;
}
inline double fn(double x)
{
    return x*x*x-5*x*x+10*x-80;
}
double deep(double m,double n)
{
    double mid=(m+n)/2;
    if(abs(fn(mid))<1e-10)
    return mid;
    if(f(m)!=f(mid))
    return deep(m,mid);
    else
    return deep(mid,n);
}
int main()
{
    printf("%.9f",deep(5,6));
    return 0;
}