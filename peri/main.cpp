#include <cstdio>
#include <cassert>
#include <algorithm>
using namespace std;
FILE *f=fopen("peri.in","r");
FILE *g=fopen("peri.out","w");
int N,M;
int S[251][251];
int maxim=-(1<<30);
long long nrmax=1;
int main()
{
    fscanf(f,"%d%d",&N,&M);
    assert(N>1&&M>1);
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=M;j++)
        {
            fscanf(f,"%d",&S[i][j]);
            if(S[i][j]==0)S[i][j]=-1;
            S[i][j]+=S[i-1][j];
        }
    }
    for(int i=1;i<=N;i++)
    {
        for(int j=i+1;j<=N;j++)
        {
            int difmax=-(1<<30),nr=1;
            for(int k=1;k<=M;k++)
            {
                if(k!=1)
                {
                    if(maxim<difmax+S[j][k]-S[i-1][k])
                    {
                        maxim=difmax+S[j][k]-S[i-1][k];
                        nrmax=nr;
                    }
                    else if(maxim==difmax+S[j][k]-S[i-1][k])
                    {
                        nrmax+=nr;
                    }
                }
                if(difmax+S[i][k]-S[i-1][k]+S[j][k]-S[j-1][k]==S[j][k]-S[i-1][k])
                {
                    difmax=difmax+S[i][k]-S[i-1][k]+S[j][k]-S[j-1][k];
                    nr++;
                }
                else if(difmax+S[i][k]-S[i-1][k]+S[j][k]-S[j-1][k]<S[j][k]-S[i-1][k])
                {
                    difmax=S[j][k]-S[i-1][k];
                    nr=1;
                }
                else
                {
                    difmax=difmax+S[i][k]-S[i-1][k]+S[j][k]-S[j-1][k];
                }
            }
        }
    }
    fprintf(g,"%d %lld",maxim,nrmax);
    fclose(f);
    fclose(g);
    return 0;
}
