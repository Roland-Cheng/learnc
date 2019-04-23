#include<iostream>
using namespace std;
int main()
{
    int a,b,i,w=0;
    for(i=0,cin>>a;i<=4;i++)
    {
        cin>>b;
        a>b? w+=b:w;
    }
    cout<<w<<endl;
    return 0;
}