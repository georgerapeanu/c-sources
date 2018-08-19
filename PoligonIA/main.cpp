#include <cstdio>
#include <algorithm>
#include <vector>
#define x first
#define y second
using namespace std;
FILE *f=fopen("poligon.in","r");
FILE *g=fopen("poligon.out","w");
pair<int,int> P[2005];
vector<int> V[2005];
vector<int> ceva[100005];
int t[2005];
int N,M,col,R;
double mij;
long long det(pair<int,int> a,pair<int,int> b,pair<int,int> c)
{
    return 1LL*a.x*b.y+1LL*b.x*c.y+1LL*c.x*a.y-1LL*a.x*c.y-1LL*b.x*a.y-1LL*c.x*b.y;
}
double eval(pair<int,int> a,pair<int,int> b,double x)
{
    return a.y+(b.y-a.y)*(mij-a.x)/((double)b.x-a.x);
}
bool cmp(int a,int b)
{
    return eval(P[a],P[a+1],mij)<eval(P[b],P[b+1],mij);
}
bool ok(int i,pair<int,int> a)
{
    long long tmp=det(min(P[i],P[i+1]),max(P[i],P[i+1]),a);
    if(tmp==0){col=1;return 1;}
    return tmp>0;
}
int main()
{
    fscanf(f,"%d%d",&N,&M);
    for(int i=1;i<=N;i++)
    {
       fscanf(f,"%d %d",&P[i].x,&P[i].y);
       t[i]=P[i].x;
    }
    P[N+1]=P[1];
    for(int i=1;i<=N;i++)if(P[i].x==P[i+1].x){ceva[P[i].x].push_back(P[i].y);ceva[P[i].x].push_back(P[i+1].y);}
    for(int i=1;i<=N;i++)sort(ceva[P[i].x].begin(),ceva[P[i].x].end());
    t[0]=-1;
    sort(t+1,t+1+N);
    int k=0;
    for(int i=1;i<=N;i++)
        if(t[k]!=t[i])
            t[++k]=t[i];
    t[k+1]=t[k]+100;
    for(int i=1;i<=k;i++)
    {
        for(int j=1;j<=N;j++)
        {
            if((P[j].x<=t[i]&&t[i+1]<=P[j+1].x)||(P[j+1].x<=t[i]&&t[i+1]<=P[j].x))
                V[i].push_back(j);
        }
        mij=0.5*(t[i]+t[i+1]);
        sort(V[i].begin(),V[i].end(),cmp);
    }
    for(int i=1;i<=M;i++)
    {
        pair<int,int> p;
        fscanf(f,"%d %d",&p.x,&p.y);
        if(p.x<t[1]||p.x>t[k])continue;
        int pos=0;
        for(int pas=1<<12;pas;pas>>=1)
            if(pos+pas<k&&t[pos+pas]<=p.x)
                pos+=pas;
        int rez=-1;
        col=0;
        if(ceva[p.x].size())
        {
           int tmp=-1;
           for(int pas=1<<12;pas;pas>>=1)
               if(tmp+pas<ceva[p.x].size()&&ceva[p.x][tmp+pas]<=p.y)
                  tmp+=pas;
            tmp++;
            col=((tmp>0&&ceva[p.x][tmp-1]==p.y)||tmp%2);
        }
        for(int pas=1<<12;pas;pas>>=1)
            if(rez+pas<V[pos].size()&&ok(V[pos][rez+pas],p))
                rez+=pas;
        rez++;
        int rezb=-1;
        if(pos>1&&t[pos]==p.x)
        {
           pos--;
           for(int pas=1<<12;pas;pas>>=1)
               if(rezb+pas<V[pos].size()&&ok(V[pos][rezb+pas],p))
                rezb+=pas;
        }
        rezb++;;
        R+=(rezb%2||rez%2||col);
        ///fprintf(stderr,"%d %d\n",i,(rez%2||col));
    }
    fprintf(g,"%d",R);
    fclose(f);///
    fclose(g);
    return 0;
}
