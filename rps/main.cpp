#include <cstdio>
#include <cstring>
#define LEN 1000005
using namespace std;
FILE *f=fopen("rps.in","r");
FILE *g=fopen("rps.out","w");
int CH[256];
char RH[256];
int N,K,W,D;
char c[LEN];
struct Trie
{
    int cnt;
    int dp;
    Trie *fiu[3];
    int c;
    Trie()
    {
        cnt=dp=c=0;
        memset(fiu,0,sizeof(fiu));
    }
};
Trie *T;
void ins(Trie *nod,char *s)
{
    nod->cnt++;
    if(*s=='\n') {nod->dp=D*nod->cnt;nod->c=-1;return;}
    if(nod->fiu[CH[*s]]==NULL)
        nod->fiu[CH[*s]]=new Trie;
    ins(nod->fiu[CH[*s]],s+1);
    int a;
    nod->dp=-(1<<30);
    for(int i=0;i<3;i++)
    {
        a=0;
        if(nod->fiu[i]!=NULL)
            a+=nod->fiu[i]->dp;
        if(nod->fiu[(i+1)%3]!=NULL)
            a+=nod->fiu[(i+1)%3]->cnt*W;
        if(nod->dp<a)
        {
            nod->dp=a;
            nod->c=i;
        }
    }
}
void q(Trie *nod,int pas)
{
    if(nod->c==-1) return;
    fputc(RH[nod->c],g);
    if(nod->fiu[nod->c]==NULL)
    {
        while(pas<K)
        {
            pas++;
            fputc('P',g);
        }
    }
    else
        q(nod->fiu[nod->c],pas+1);
}
char C[20];
void dfs(Trie *nod,int pas)
{
    bool ok=0;
    for(int i=0;i<3;i++)
    {
        if(nod->fiu[i]!=NULL)
            {C[pas]=RH[i];dfs(nod->fiu[i],pas+1);ok=1;}
    }
    if(!ok)
    {fputs(C+1,g);fputc('\n',g);}
}
int main()
{
    CH['P']=0;
    CH['R']=1;
    CH['S']=2;
    RH[0]='P';
    RH[1]='R';
    RH[2]='S';
    T=new Trie;
    fscanf(f,"%d %d %d %d\n",&N,&K,&W,&D);
    for(int i=1;i<=N;i++)
    {
        fgets(c+1,LEN,f);
        ins(T,c+1);
        q(T,1);
        fputc('\n',g);
    }
    ///dfs(T,1);
    fclose(f);
    fclose(g);
    return 0;
}
