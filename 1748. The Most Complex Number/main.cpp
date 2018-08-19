#include <iostream>
#define inf (1LL<<62)
#define MAXCOM 105000
using namespace std;
int P[]={0,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53};
long long F[MAXCOM+5],T,N;
int nr[MAXCOM+5][17];
///f(x)-cel mai mic numar care are complexitatea x.nu,nu merge cautare binara la final
int main()
{
    F[1]=1;
    for(int i=2;i<=MAXCOM;i++)
        F[i]=inf;
    for(int i=1;i<=MAXCOM;i++)
    {
        if(F[i]==inf&&i<=63)
        {F[i]=(1LL<<(i-1));nr[i][1]=i-1;}
        for(int j=1;F[i]!=inf&&j<=16;j++)
        {
            long long tmp=F[i]*P[j];
            if(tmp%F[i]==0&&tmp>0&&tmp<=(long long)1e18)
            {
                int aux=1,ind=1;
                for(ind=1;ind<=16&&nr[i][ind];ind++)
                    aux*=(nr[i][ind]+1+(j==ind));
                if(ind<=j)
                    aux*=2;
                if(tmp<F[aux])
                {
                    F[aux]=tmp;
                    for(ind=1;ind<=16;ind++)
                        nr[aux][ind]=nr[i][ind];
                    nr[aux][j]++;
                }
            }
        }
    }
    cin>>T;
    for(int i=1;i<=T;i++)
    {
        cin>>N;
        /*int st=1,dr=MAXCOM,mid,last=-1;
        while(st<=dr)
        {
            mid=(st+dr)/2;
            if(F[mid]>N)
            {
                dr=mid-1;
            }
            else
            {
                st=mid+1;
                last=mid;
            }
        }*/
        int last=1;
        for(int i=1;i<=MAXCOM;i++)
        {
            if(F[i]<=N)
                last=i;
        }
        cout<<F[last]<<" "<<last<<"\n";
    }
    return 0;
}
