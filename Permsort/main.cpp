#include <cstdio>
#include <algorithm>
#define val first
#define p second
#define LEN 100000
using namespace std;
FILE *f=fopen("permsort.in","r");
FILE *g=fopen("permsort.out","w");
int st=1;
int l[1000001];
int r[1000001];
int N;
pair<int,int> V[1000001];
int AIB[1000001];
long long S;
char buff[LEN];
int ind=LEN-1;
int i32()
{
    int rez=0;
    int sgn=1;
    while((buff[ind]<'0'||buff[ind]>'9')&&buff[ind]!='-')
        if(++ind>=LEN){
            fread(buff,1,LEN,f);
            ind=0;
        }
    if(buff[ind]=='-')
    {
        sgn=-1;
        if(++ind>=LEN){
            fread(buff,1,LEN,f);
            ind=0;
        }
    }
    while(buff[ind]>='0'&&buff[ind]<='9'){
        rez=rez*10+buff[ind]-'0';
        if(++ind>=LEN){
            fread(buff,1,LEN,f);
            ind=0;
        }
    }
    return rez*sgn;
}
void u(int pos,int val)
{
    for(int i=pos;i<=N;i+=(i&(-i))) AIB[i]+=val;
}
int q(int pos)
{
    int rez=0;
    for(int i=pos;i;i-=(i&(-i)))rez+=AIB[i];
    return rez;
}
int main()
{
    N=i32();
    for(int i=1;i<=N;i++)
    {
        l[i]=(N-1+i-1)%N+1;
        r[i]=(i%N+1);
        V[i].val=i32();
        V[i].p=i;
    }
    sort(V+1,V+1+N);
    for(int i=1;i<=N;i++)
    {
        int nl,nr;
        nl=l[V[i].p];
        nr=r[V[i].p];
        l[nr]=nl;
        r[nl]=nr;
        if(st<=V[i].p)
        {
            S+=V[i].p-st+1-(q(V[i].p)-q(st-1));
        }
        else
        {
            S+=(N-st+1+V[i].p)-(i-1-(q(st-1)-q(V[i].p)));
        }
        u(V[i].p,1);
        st=r[V[i].p];
    }
    fprintf(g,"%lld",S);
    fclose(f);
    fclose(g);
    return 0;
}
