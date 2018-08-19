#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
FILE *f=fopen("trapez.in","r");
FILE *g=fopen("trapez.out","w");
pair<int ,int> puncte[1000005];
long long N,i,j,ci,nr;
long long rez;
double m[1000005];
int main()
{
    fscanf(f,"%lld",&N);
    for(i=1;i<=N;i++)
        fscanf(f,"%lld %lld",&puncte[i].first,&puncte[i].second);
    for(i=1;i<=N;i++)
    {
        for(j=i+1;j<=N;j++)
        {
            m[++nr]=double(puncte[i].second-puncte[j].second)/double(puncte[i].first-puncte[j].first);
        }
    }
    sort(m+1,m+nr+1);
    m[nr+1]=-1000000000;
    for(i=1;i<nr;i++)
    {
        ci=i;
        while(m[i]==m[i+1]&&i<=nr)
            i++;
        rez+=(i-ci+1)*(i-ci)/2;
    }
    fprintf(g,"%lld",rez);
    return 0;
}
