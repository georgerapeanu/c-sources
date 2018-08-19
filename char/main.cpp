#include <cstdio>
#include <set>
#include <algorithm>
using namespace std;
FILE *f=fopen("char.in","r");
FILE *g=fopen("char.out","w");
int putere[27],N,M,val,nr,i,ultim,maxim,rez;
char c[10005];
set <char> S;
pair <int,int> V[10005];
int frecv[27];
bool cmp(pair<int,int> a,pair<int,int> b)
{
    if(a.second!=b.second)
        return a.second<b.second;
    return a.first<b.first;
}
int main()
{
    fscanf(f,"%d\n",&N);
    fgets(c+1,10005,f);
    for(i=1;i<=N;i++)
        {
            S.insert(c[i]);
            frecv[c[i]-'a']++;
        }
    fscanf(f,"%d",&M);
    for(i=1;i<=M;i++)
    {
        fscanf(f,"%d",&val);
        if(val>maxim)
        {
            nr=frecv[*(S.begin())-'a'];
            maxim=val;
        }
        else if(val==maxim)
            nr+=frecv[*(S.begin())-'a'];
        putere[*(S.begin())-'a']=val;
        S.erase(S.begin());
    }
    rez=nr;
    for(i=1;i<=N;i++)
    {
        V[i]=make_pair(max(0,i-putere[c[i]-'a']),min(N,i+putere[c[i]-'a']));
    }
    sort(V+1,V+1+N,cmp);
    ultim=-1;nr=0;
    for(i=1;i<=N;i++)
    {
        if(V[i].first>ultim)
        {
            nr++;
            ultim=V[i].second;
        }
    }
    fprintf(g,"%d\n%d",rez,nr);
    fclose(f);
    fclose(g);
    return 0;
}
