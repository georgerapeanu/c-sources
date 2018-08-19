#include <cstdio>
#include <vector>
#include <bitset>
#define LEN 10000
using namespace std;
FILE *f=fopen("nogame.in","r");
FILE *g=fopen("nogame.out","w");
vector<int> G[16];
bitset<16> U;
int op[16][4];
int L[16];
int R[16];
int tmp[4];
int nr,N,T;
int V[1005];
int rez[1005];
int B[16][1005];
char buff[LEN];
int ind=LEN-1;
void getEdges()
{
    for(int i=0;i<16;i++)
    {
        G[i].clear();
        if(V[0]!=B[i][0])
            continue;
        for(int j=0;j<16;j++)
        {
            bool ok=1;
            for(int k=1;k<N;k++)
            {
                int rez=0;
                for(int l=0;(1<<l)<=V[k]||(1<<l)<=B[i][k-1];l++)
                {
                    rez|=(op[j][2*((B[i][k-1]>>l)&1)+((V[k]>>l)&1)]<<l);
                }
                if(rez!=B[i][k])
                    {ok=0;break;}
            }
            if(ok)G[i].push_back(j);
        }
    }
}
bool pairup(int nod)
{
    if(!U[nod]) U[nod]=1;
    else return 0;
    for(auto it:G[nod])
    {
        if(L[it]==-1){L[it]=nod;R[nod]=it;return 1;}
    }
    for(auto it:G[nod])
    {
        if(pairup(L[it])){L[it]=nod;R[nod]=it;return 1;}
    }
    return 0;
}
bool cuplaj()
{
    for(int i=0;i<16;i++) L[i]=R[i]=-1;
    getEdges();
    int nr=0;
    bool ok=0;
    do
    {
        ok=0;
        U.reset();
        for(int i=0;i<16;i++)
        {
            if(R[i]!=-1) continue;
            if(pairup(i))
            {
                ok=1;nr++;
            }
        }
    }
    while(ok);
    return (nr==16);
}
void genop(int pas)
{
    if(pas>=4)
    {
        for(int i=0;i<4;i++) op[nr][i]=tmp[i];
        nr++;
        return ;
    }
    tmp[pas]=0;
    genop(pas+1);
    tmp[pas]=1;
    genop(pas+1);
}
bool mmic()
{
    int i=0;
    while(i<15&&V[i]==rez[i]) i++;
    return (V[i]<rez[i]);
}
int i32()
{
    int nr=0;
    while(buff[ind]<'0'||buff[ind]>'9')
        if(++ind>=LEN){
            fread(buff,1,LEN,f);
            ind=0;
    }
    while(buff[ind]>='0'&&buff[ind]<='9'){
        nr=nr*10+buff[ind]-'0';
        if(++ind>=LEN){
            fread(buff,1,LEN,f);
            ind=0;
        }
    }
    return nr;
}
int main()
{
    genop(0);
    T=i32();
    while(T--)
    {
        bool ok=0;
        N=i32();
        for(int i=0;i<16;i++)
            for(int j=0;j<N;j++)
                B[i][j]=i32();
        for(int i=0;i<16;i++)
        {
            V[0]=B[i][0];
            for(int j=1;j<N;j++)
                V[j]=(B[i][j-1]^B[i][j]);
            if(cuplaj())
            {
                if(ok==0||mmic()) for(int i=0;i<N;i++) rez[i]=V[i];
                ok=1;
                break;
            }
        }
        if(!ok) fputs("-1\n",g);
        else {for(int i=0;i<N;i++) fprintf(g,"%d ",rez[i]);fputc('\n',g);}
    }
    fclose(f);
    fclose(g);
    return 0;
}
