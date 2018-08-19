#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cassert>
using namespace std;
FILE *f=fopen("admitere.in","r");
FILE *g=fopen("admitere.out","w");
const int LEN=10000;
int ind=LEN-1;
char buff[LEN];
int T;
int N,M;
int rez=0;
int fr[4005];
pair<int,int> V[2][4005];
char C[4005];
int i32()
{
    int rez=0;
    while(buff[ind]<'0'||'9'<buff[ind]){
        if(++ind>=LEN){
            ind=0;
            fread(buff,1,LEN,f);
        }
    }
    while(buff[ind]>='0'&&'9'>=buff[ind]){
        rez=rez*10+buff[ind]-'0';
        if(++ind>=LEN){
            ind=0;
            fread(buff,1,LEN,f);
        }
    }
    return rez;
}
int main()
{
    T=i32();
    N=i32();M=i32();
    for(int j=0;j<2;j++)for(int i=1;i<=M;i++)V[j][i]={i32(),0};
    for(int i=1;i<=N;i++)
    {
        V[0][M+i]={i32(),i};
        V[1][M+i]={i32(),i};
    }
    sort(V[0]+1,V[0]+1+N+M);reverse(V[0]+1,V[0]+1+N+M);
    sort(V[1]+1,V[1]+1+N+M);reverse(V[1]+1,V[1]+1+N+M);
    memset(C,'X',sizeof(C));
    if(T==1)
    {
        int a=0,b=0;
        for(int i=1;i<=M;i++){a+=(V[0][i].second>0);b+=(V[1][i].second>0);}
        if(a>=b)
        {
            fprintf(g,"%d\n",a);
            for(int i=1;i<=M;i++)if(V[0][i].second)C[V[0][i].second]='R';
        }
        else
        {
            fprintf(g,"%d\n",b);
            for(int i=1;i<=M;i++)if(V[1][i].second)C[V[1][i].second]='U';
        }
        C[1+N]='\0';
        fputs(C+1,g);
        return 0;
    }
    for(int i=0;i<=N;i++)
    {
        memset(fr,0,sizeof(fr));
        int both=0;
        for(int j=1;j<=M+i;j++)fr[V[0][j].second]++;
        for(int j=1;j<=M;j++)
        {
            fr[V[1][j].second]++;
            if(V[1][j].second&&fr[V[1][j].second]>1)both++;
        }
        if(both<i)continue;
        int lim=M+1;
        for(lim=M+1;lim<=M+both-i;lim++)
        {
            fr[V[1][lim].second]++;
            if(V[1][lim].second&&fr[V[1][lim].second]>1)both++;
        }
        int tmp=-both;
        for(int j=1;j<=M+i;j++)tmp+=(V[0][j].second>0);
        for(int j=1;j<lim;j++)tmp+=(V[1][j].second>0);
        if(tmp>rez)
        {
            int smth=0;
            rez=tmp;
            memset(C,'X',sizeof(C));
            int ceva=i;
            for(int j=1;j<=M+i;j++)
            {
                if(!V[0][j].second)continue;
                if(fr[V[0][j].second]>1&&ceva)
                {
                    ceva--;continue;
                }
                C[V[0][j].second]='R';
                smth++;
            }
            for(int j=1;j<lim;j++)
            {
                if(!V[1][j].second)continue;
                if(C[V[1][j].second]!='X')
                {
                    continue;
                }
                C[V[1][j].second]='U';
                smth++;
            }
            assert(smth==tmp);
        }
    }
    fprintf(g,"%d\n",rez);
    C[1+N]='\0';
    fputs(C+1,g);
    fclose(f);
    fclose(g);
    return 0;
}
