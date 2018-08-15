#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
FILE *f=fopen("subgeom.in","r");
FILE *g=fopen("subgeom.out","w");
int rez=1;
int N,T;
int V[5005];
int fr[100005];
bool ok[100005];
const int LEN=10000;
char buff[LEN];
int ind=LEN-1;
int i32()
{
    int rez=0;
    while(buff[ind]<'0'||buff[ind]>'9')
    {
        if(++ind>=LEN)
        {
            ind=0;
            fread(buff,1,LEN,f);
        }
    }
    while(buff[ind]>='0'&&buff[ind]<='9')
    {
        rez=rez*10+buff[ind]-'0';
        if(++ind>=LEN)
        {
            ind=0;
            fread(buff,1,LEN,f);
        }
    }
    return rez;
}
int main()
{
    T=i32();
    while(T--)
    {
        rez=1;
        memset(ok,0,sizeof(ok));
        N=i32();
        for(int i=1;i<=N;i++)
        {
            V[i]=i32();
            if(ok[V[i]])rez=2;
            else for(int j=V[i]<<1;j<=100000;j+=V[i])ok[j]=1;
        }
        int k;
        for(k=2;k*k<=100000;k++)
        {
            memset(fr,0,sizeof(fr));
            for(int i=1;i<=N;i++)
            {
                int tmp=1;
                if(V[i]%k==0)
                {
                    tmp=max(tmp,1+fr[V[i]/k]);
                }
                fr[V[i]]=max(fr[V[i]],tmp);
                rez=max(rez,tmp);
            }
            if(rez>=3&&k>=47)break;
            if(rez>=4&&k>= 18)break;
        }
        memset(fr,0,sizeof(fr));
        fprintf(g,"%d\n",rez);
    }
    fclose(f);
    fclose(g);
    return 0;
}
