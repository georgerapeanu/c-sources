#include <iostream>
using namespace std;
int linie[3000],N,M,X,i,j,a,ctr=1,k;
int main()
{
    cin>>N>>M>>X;
    for(i=1;i<=N;i++)
    {
        ctr=1;
        for(j=1;j<=M;j++)
        {
            cin>>a;
            for(k=ctr;k<ctr+X;k++)
                linie[k]=a;
            ctr+=X;
        }
        for(j=1;j<=X;j++)
        {
            for(k=1;k<ctr;k++)
                cout<<linie[k]<<" ";
            cout<<"\n";
        }
    }
    return 0;
}
