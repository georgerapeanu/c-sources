#include <cstdio>
#include <deque>
#include <algorithm>
#define st first
#define dr second
using namespace std;
FILE *f;
int ind;
char buffer[4096];
FILE *g=fopen("saracsaurege.out","w");
int RMQ[50005];///RMQ[i]-elementul maxim din intervalul i-dist+1,i
int M,V[50005];
int dist=(1<<16),N,a,b;
int dq[50005];
void read_init(char* nume)
{
    f=fopen(nume,"r");
    ind=4095;
}
char get_ch()
{
    ind++;
    if(ind==4096)
    {
        ind=0;
        fread(buffer,1,4096,f);
    }
    return buffer[ind];
}
int get_i32()
{
    int nr=0,sgn=1;
    char c=get_ch();
    while(c!='-'&&!isdigit(c))
        c=get_ch();
    if(c=='-')
    {
        sgn=-1;
    }
    else
    {
        nr=c-'0';
    }
   while(isdigit(c=get_ch()))
    {
        nr=nr*10+c-'0';
    }
    return nr*sgn;
}
void get_max(int dist)
{
    int st=0,dr=-1;
    for(int i=1;i<=N;i++)
    {
        while((st<=dr)&&dq[st]==i-dist) st++;
        while((st<=dr)&&V[dq[dr]]<=V[i]) dr--;
        dq[++dr]=i;
        RMQ[i]=V[dq[st]];
    }
}
int main()
{
    read_init("saracsaurege.in");
    N=get_i32();
    M=get_i32();
    for(int i=1;i<=N;i++)
    {
       V[i]=get_i32();
    }
    for(int i=1;i<=M;i++)
    {
        a=get_i32();
        b=get_i32();
        if(dist>b-a+1)
        {
            while(dist>b-a+1)
            {
                dist/=2;
            }
            get_max(dist);
        }
        fprintf(g,"%d\n",max(RMQ[b],RMQ[a+dist-1]));
    }
    fclose(g);
    return 0;
}
