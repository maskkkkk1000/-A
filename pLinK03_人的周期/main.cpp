#include<iostream>
using namespace std;
int main()
{
    int a,b,c,d;
    int i,k=0;
	while(cin>>a>>b>>c>>d&&a!=-1)
    {
        for(i=0;(i-d)<=21252;i++)
        {
            if(((i-a)%23==0)&&((i-b)%28==0)&&((i-c)%33==0)&&(i>d))
            {
                cout<<"Case "<<++k<<": the next triple peak occurs in "<<i-d<<" days."<<endl;
                break;
            }
        }
    } 
	return 0;
}