#include <cstdio>
#include <algorithm>
#define x first
#define y second
using namespace std;
FILE *f=fopen("startreck.in","r");
FILE *g=fopen("startreck.out","w");
pair<int,int> AIB[100005];
pair<int,int> V[100005];
int R[100005];
bool r[100005];
int N,M,P,Q;
int poz,val;
void u(int poz,int st,int dr)
{
    bool a=(R[poz]!=0);
    for(;poz<=N;poz+=(poz&(-poz)))
    {
        r[poz]|=a;
        AIB[poz].x=min(AIB[poz].x,st);
        AIB[poz].y=max(AIB[poz].y,dr);
    }
}
pair<int,int> q(int st,int dr)
{
    pair<int,int> rez;rez.x=9999999;rez.y=0;
    if(st==0){rez.x=0;st++;}
    while(st<=dr)
    {
        if(R[dr])
        {
            rez.x=min(R[dr],rez.x);
            rez.y=max(R[dr],rez.y);
            break;
        }
        else if(r[dr]||dr-(st&(-st))+1<st)
        {
            rez.x=min(R[dr],rez.x);
            rez.y=max(R[dr],rez.y);
            dr--;
        }
        else
        {
            rez.x=min(AIB[dr].y,rez.x);
            rez.y=max(AIB[dr].x,rez.y);
            dr-=(st&(-st));
        }
    }
    return rez;
}
int main()
{
    for(int i=0;i<100005;i++)AIB[i].x=9999999;
    fscanf(f,"%d%d%d%d",&N,&P,&Q,&M);
    for(int i=1;i<=M;i++)
    {
        fscanf(f,"%d%d",&poz,&val);
        R[poz]=val;
    }
    V[0]={0,0};
    for(int i=1;i<=N;i++)
    {
        V[i]=q(max(0,i-Q),max(0,i-P));
        V[i].x++;
        V[i].y++;
        u(i,V[i].x,V[i].y);
    }
    fprintf(g,"%d",V[N].y);
    fclose(f);
    fclose(g);
    return 0;
}
