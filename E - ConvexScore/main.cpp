#include <cstdio>
#include <cmath>
#include <algorithm>
#define MOD 998244353
using namespace std;
pair<int,int> P[205];
double tmp[205];
int pw2[205];
int N;
int rez;
void fix(int &val)
{
    if(val<0)val+=MOD;
    if(val>=MOD)val-=MOD;
}
void baga(pair<int,int> a)
{
    int len=0;
    for(int i=1;i<=N;i++)
    {

        if(a<P[i])
        {
            tmp[++len]=atan2(P[i].second-a.second,P[i].first-a.first);
        }
    }
    sort(tmp+1,tmp+1+len);
    int cnt=(len>0);
    //printf("%d ",rez);
    fix(rez=rez-1);
    for(int i=2;i<=len;i++)
    {
        if(tmp[i]==tmp[i-1])
        {
            cnt++;
        }
        else
        {
            fix(rez-=(pw2[cnt]-1));
            cnt=1;
        }
    }
    fix(rez-=(pw2[cnt]-1));
//    printf("%d\n",rez);
}
int main()
{
    pw2[0]=1;
    for(int i=1;i<=200;i++)fix(pw2[i]=2*pw2[i-1]);
    scanf("%d",&N);rez=pw2[N]-1;
    for(int i=1;i<=N;i++)scanf("%d %d",&P[i].first,&P[i].second);
    for(int i=1;i<=N;i++)
    {
        baga(P[i]);
    }
    printf("%d",rez);
    return 0;
}
