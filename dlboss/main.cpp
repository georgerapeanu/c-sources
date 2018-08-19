#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
#define c first
#define t second.first
#define ind second.second
#define x first
#define y second
using namespace std;
FILE *f=fopen("dlboss.in","r");
FILE *g=fopen("dlboss.out","w");
typedef pair<int,pair<int,int> > doamna;
typedef pair<int,int> segm;
doamna A[100005];
segm V[100005];
int usegm=0;
int rez[100005];
priority_queue <int> S;
int smax;
int N,T;
int main()
{
    fscanf(f,"%d%d",&N,&T);
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d %d",&A[i].t,&A[i].c);
        A[i].ind=i;
    }
    sort(A+1,A+1+N);
    for(int i=1;i<=N;i++)
    {
        if(A[i-1].c!=A[i].c)
            usegm++,V[usegm].x=V[usegm].y=i;
        else
            V[usegm].y++;
    }
    for(int i=usegm;i;i--)
    {
        ///getting rez for everyone
        for(int j=V[i].x;j<=V[i].y;j++)
        {
            rez[A[j].ind]=S.size();
        }
        ///updateing
        int m=(1<<30);
        for(int j=V[i].x;j<=V[i].y;j++)
            m=min(A[j].t,m);
        if(m+smax<=T)
        {
            S.push(m);
            smax+=m;
        }
        else
        {
            if(smax-S.top()+m<=T&&m<S.top())
            {
                smax=smax-S.top()+m;
                S.pop();
                S.push(m);
            }
        }
    }
    for(int i=1;i<=N;i++)
        fprintf(g,"%d\n",rez[i]);
    fclose(f);
    fclose(g);
    return 0;
}
