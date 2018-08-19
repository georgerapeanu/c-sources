#include<iostream>
using namespace std;
int main()
{
    long l=0,s,i,j,s2=0,k=0,gasit=0;
    cout<<"s=";
    cin>>s;
    for(j=1;j<s;j++)
    {
        i=j;
        s2=0;
        k=0;
        while(s2<s)
        {
           s2+=i;
           i++;
           k++;
        }
        if(s2==s)
        {
            cout<<k<<" "<<j<<"\n";
            gasit++;
        }
    }
    cout<<"numar de solutii "<<gasit;
    return 0;
}
