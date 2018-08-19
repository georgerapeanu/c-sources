#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("suma3.in","r");
FILE *g=fopen("suma3.out","w");
pair<long long,long long> S[100005];
long long st,dr,i,N,rez=999999999;
int main()
{
    fscanf(f,"%lld",&N);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%lld",&S[i].first);
        S[i].first+=S[i-1].first;
        S[i].second=i;
    }
    sort(S,S+1+N);
    for(i=1;i<=N;i++)
    {
        if(S[i].first-S[i-1].first<rez)
        {
            rez=S[i].first-S[i-1].first;
            st=min(S[i].second,S[i-1].second)+1;
            dr=max(S[i].second,S[i-1].second);
        }
    }
    fprintf(g,"%lld %lld %lld",rez,st,dr);
    fclose(f);
    fclose(g);
    return 0;
}
