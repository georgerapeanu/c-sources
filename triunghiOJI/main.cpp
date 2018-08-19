#include <cstdio>
#include <iostream>
using namespace std;
FILE *f=fopen("triunghi4.in","r");
FILE *g=fopen("triunghi4.out","w");
long long linie[2][1005];
long long  N,i,j;
pair<long long,long long> data[1005];
int main()
{
    fscanf(f,"%lld",&N);
    for(i=1;i<=N;i++)
        fscanf(f,"%lld %lld",&data[i].first,&data[i].second);
    linie[N%2][1]=data[N].second;
    for(i=N-1;i>=1;i--)
    {
        linie[i%2][data[i].first]=data[i].second;
        for(j=data[i].first+1;j<=N-i+1;j++)
            linie[i%2][j]=linie[(i+1)%2][j-1]-linie[i%2][j-1];
        for(j=data[i].first-1;j>0;j--)
            linie[i%2][j]=linie[(i+1)%2][j]-linie[i%2][j+1];
    }
    for(i=1;i<=N;i++)
        fprintf(g,"%lld ",linie[1][i]);
    fclose(f);
    fclose(g);
    return 0;
}
