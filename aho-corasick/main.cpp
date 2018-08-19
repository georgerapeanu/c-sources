#include <cstdio>
#include <vector>
#include <cstring>
#define SIGMA 26
#define CH (*c-'a')
using namespace std;
FILE *f=fopen("ahocorasick.in","r");
FILE *g=fopen("ahocorasick.out","w");
char A[1000005];
char B[10005];
struct tn
{
    int n0;
    vector<int> cuv;
    tn *fiu[SIGMA],*fail;
    tn()
    {
        memset(fiu,0,sizeof(fiu));
        fail=0;
        n0=0;
    }
};
void ins(tn *t,char *c,int nr)
{
    if(*c=='\n')
    {
        t->cuv.push_back(nr);
        return ;
    }
    if(!t->fiu[CH]) t->fiu[CH]=new tn;
    ins(t->fiu[CH],c+1,nr);
}
tn *q[1000005];
int st=0,dr=0;
int rez[105];
int N;
tn *T;
void bfs()
{
    T->fail=T;
    q[st]=T;
    tn *a,*fr;
    while(st<=dr)
    {
        fr=q[st++];
        for(int i=0;i<SIGMA;i++)
        {
            if(fr->fiu[i]==0) continue;
            a=fr->fail;
            while(a!=T&&a->fiu[i]==0)
                a=a->fail;
            if(a->fiu[i]!=0&&a->fiu[i]!=fr->fiu[i]) a=a->fiu[i];
            fr->fiu[i]->fail=a;
            q[++dr]=fr->fiu[i];
        }
    }
    T->fail=0;
}
void antibfs()
{
    for(int i=dr;i>0;i--)
    {
        if(q[i]->fail!=0) q[i]->fail->n0+=q[i]->n0;
        for(auto it:q[i]->cuv)
            rez[it]=q[i]->n0;
    }
}
int main()
{
    T=new tn;
    fgets(A,1000005,f);
    fscanf(f,"%d\n",&N);
    for(int i=1;i<=N;i++)
    {
        fgets(B,10005,f);
        ins(T,B,i);
    }
    bfs();
    tn *tmp=T;
    for(int i=0;;i++)
    {
        if(A[i]=='\n') break;
        while(tmp!=T&&tmp->fiu[A[i]-'a']==0)
            tmp=tmp->fail;
        if(tmp->fiu[A[i]-'a']!=0)tmp=tmp->fiu[A[i]-'a'];
        tmp->n0++;
    }
    antibfs();
    for(int i=1;i<=N;i++)
        fprintf(g,"%d\n",rez[i]);
    fclose(f);
    fclose(g);
    return 0;
}
