#include <iostream>
#include <cstring>
using namespace std;
char P[1000];
int n,k,l,r,p1,p2,lung,kp,beta,i;
int Z[1000];
int main()
{
    P[0]='.';
    cin>>P+1;
    n=strlen(P+1);
    Z[1]=0;
    l=r=0;
    for(k=2;k<=n;k++)
    {
        if(r<k)
        {
            p1=1;p2=k;
            lung=0;
            while(P[p1]==P[p2])
            {
                p1++;
                p2++;
                lung++;
            }
            if(lung==0)
            {
                Z[k]=0;
            }
            else
            {
                Z[k]=lung;
                l=k;
                r=p2-1;
            }
        }
        else
        {
            kp=k-l+1;
            beta=r-k+1;
            if(Z[kp]<beta)
            {
                Z[k]=Z[kp];
            }
            else
            {
                p1=beta+1;
                p2=r+1;
                lung=0;
                while(P[p1]==P[p2])
                {
                    p1++;
                    p2++;
                    lung++;
                }
                l=k;
                r=p2-1;
                Z[k]=beta+lung;

            }
        }
    }
    for(i=1;i<=n;i++)
    {
        cout<< Z[i]<<" ";
    }
    return 0;
}
