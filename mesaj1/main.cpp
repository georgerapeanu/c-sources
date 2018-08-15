#include <cstdio>
#include <fstream>
#include <algorithm>
#define inf 2005
using namespace std;
FILE *f=fopen("mesaj1.in","r");
FILE *g=fopen("mesaj1.out","w");
char rez[2005][27];
int N,K,cnt,i,j,minim=inf;
typedef pair<char,int> data;
data V[27];
int frecv[65];
char C[2005],c,frecvent;
int carperlin,rest;
int main()
{
    fscanf(f,"%d\n",&N);
    for(i=1;i<=N;i++)
    {V[i].second=i;fscanf(f,"%c",&V[i].first);}
    sort(V+1,V+1+N);
    fscanf(f,"%d\n",&K);
    carperlin=K/N;
    rest=K%N;
    fgets(C,2005,f);
    for(i=0;i<K;i++)
    {
        if(C[i]!=' ')
            frecv[C[i]-'A']++;
    }
    for(c='A';c<='Z';c++)
    {
        if(frecv[c-'A']<minim&&frecv[c-'A']>0)
            {minim=frecv[c-'A'];frecvent=c;}
    }
    for(c='a';c<='z';c++)
    {
        if(frecv[c-'A']<minim&&frecv[c-'A']>0)
            {minim=frecv[c-'A'];frecvent=c;}
    }
    fprintf(g,"%c\n",frecvent);
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=carperlin+(V[i].second<=rest);j++)
        {
            rez[j][V[i].second]=C[cnt++];
        }
    }
    for(i=1;i<=carperlin+rest;i++)
        fputs(rez[i]+1,g);
    fclose(f);
    fclose(g);
    return 0;
}
