#include <cstdlib>
#include <cstdio>
#include <vector>
#include <deque>
#include <algorithm>
#define x first
#define y second
#define inf (1LL<<60)
#define tp long long
#define ab(x) (x<0 ? -x:x)
using namespace std;
FILE *f=fopen("elmer.in","r");
FILE *g=fopen("elmer.out","w");
pair<tp,tp> duck[1005];
pair<tp,tp> Z[1005];
vector<tp> Ev;
deque< pair<tp,tp> > D;
tp N,M;
tp L[1005];
tp R[1005];
bool cmp(tp a,tp b)
{
    if(ab(a)!=ab(b))return ab(a)<ab(b);
    else return a>b;
}
tp ce(long double a)
{
    if(a-(tp)a>1e-8)return (tp)a+1;
    else return (tp)a;
}
tp det(pair<tp,tp> a,pair<tp,tp> b,pair<tp,tp> c)
{
    return (1LL*a.x*b.y+1LL*b.x*c.y+1LL*c.x*a.y-1LL*a.x*c.y-1LL*b.x*a.y-1LL*c.x*b.y);
}
tp findmin(pair<tp,tp> a)
{
    if(a.y<=D.front().y)return -inf;
    pair<tp,tp> b=D.front();
    tp X=((1LL*a.x*b.y-1LL*b.x*a.y)/(b.y-a.y)+((1LL*a.x*b.y-1LL*b.x*a.y)%(b.y-a.y)!=0));
    return X;
}
tp findmax(pair<tp,tp> a)
{
    if(a.y<=D.front().y)return inf;
    pair<tp,tp> b=D.front();
    tp X=(1LL*a.x*b.y-1LL*b.x*a.y)/(b.y-a.y);
    return X;
}
int main()
{
    fscanf(f,"%lld",&N);
    Z[1]={0,0};
    for(int i=1;i<=N;i++)fscanf(f,"%lld %lld",&duck[i].x,&duck[i].y);
    fscanf(f,"%lld",&M);
    for(int i=2;i<=M+1;i++)fscanf(f,"%lld %lld",&Z[i].x,&Z[i].y);
    Z[M+2]={inf,0};
    M+=2;
    sort(R+1,R+1+N);
    sort(Z+1,Z+1+M);
    for(int i=1;i<=N;i++)
    {
        tp lb=lower_bound(Z+1,Z+1+M,duck[i])-Z-1;
        D.clear();
        for(int j=lb;j;j--)
        {
            while(!D.empty()&&det(duck[i],D.back(),Z[j])<=0)D.pop_back();
            D.push_back(Z[j]);
            L[j]=-inf;
            R[j]=findmin(duck[i]);
        }
        D.clear();
        for(int j=lb+1;j<=M;j++)
        {
            while(!D.empty()&&det(duck[i],D.back(),Z[j])>=0)D.pop_back();
            D.push_back(Z[j]);
            L[j]=findmax(duck[i]);
            R[j]=inf;
        }
        for(int j=1;j<M;j++)
        {
            tp l=max(L[j],Z[j].x+1);
            tp r=min(R[j+1],Z[j+1].x-1);
            if(l<=r)
            {
                Ev.push_back(l);
                Ev.push_back(-r);
            }
        }
    }

    sort(Ev.begin(),Ev.end(),cmp);
    tp nr=0,rez=0;
    for(auto it:Ev)
    {
        if(it<0)nr--;
        else nr++;
        rez=max(rez,nr);
    }
    fprintf(g,"%lld",rez);
    fclose(f);
    fclose(g);
    return 0;
}
