#include<iostream>
#include<cstring>
using namespace std;
string leftl[3];
string rightr[3];
string result[3];
bool findcoin(char coin,string height)
{
    string c;
    c.push_back(coin);
    for(int i=0;i<3;i++)
    switch(result[i][0])
    {
        case'e':
        if(leftl[i].find(c)!=string::npos||rightr[i].find(c)!=string::npos)
        return false;break;
        case'u':
        if((height=="heavy"&&rightr[i].find(c)!=string::npos)||(height=="light"&&leftl[i].find(c)!=string::npos)||(leftl[i].find(c)==string::npos&&rightr[i].find(c)==string::npos))
        return false;break;
        case'd':
        if((height=="light"&&rightr[i].find(c)!=string::npos)||(height=="heavy"&&leftl[i].find(c)!=string::npos)||(leftl[i].find(c)==string::npos&&rightr[i].find(c)==string::npos))
        return false;break;
    }
    return true;
}
int main()
{
    int n;
    cin>>n;
    while(n--)
    {
    for(int i=0;i<3;i++)
    {
        cin>>leftl[i];
        cin>>rightr[i];
        cin>>result[i];
    }
    for(char coin='A';coin<='L';coin++)
      {
        if(findcoin(coin,"heavy"))
        {
            cout<<coin<<" is the counterfeit coin and it is heavy."<<endl;
            break;
        }
        else if(findcoin(coin,"light"))
        {
            cout<<coin<<" is the counterfeit coin and it is light."<<endl;
            break;
        }
      }
    }
    return 0;
}