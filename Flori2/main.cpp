#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int T,N,a,b;
typedef struct{double x,y;} point;
point P[1005];
double M[1005];
int maxim,nr;
int main()
{
    freopen("flori2.in","r",stdin);
    freopen("flori2.out","w",stdout);
    cin>>T;
    while(T)
    {
        cin>>N;
        for(int i=1;i<=N;i++)
            cin>>P[i].x>>P[i].y;
        maxim=0;
        for(int i=1;i<=N;i++)
        {
            for(int j=1;j<=N;j++)
            {
                if(j!=i)
                {
                    if(P[i].x!=P[j].x)
                    {
                        M[j]=double(P[i].y-P[j].y)/(P[i].x-P[j].x);
                    }
                    else
                        M[j]=-10000002;
                }
                M[i]=-10000004;
            }
            sort(M+1,M+1+N);
            nr=1;
            for(int i=1;i<N;i++)
            {
                if(abs(M[i+1]-M[i])<=0.0000000001)
                    nr++;
                else
                {
                    maxim=max(maxim,nr);
                    nr=1;
                }
            }
            maxim=max(maxim,nr);
            ///cout<<maxim<<"\n";;
        }
        if(N!=1)
            cout<<maxim+1<<"\n";
        else
            cout<<1<<"\n";
        T--;
    }
    return 0;
}
