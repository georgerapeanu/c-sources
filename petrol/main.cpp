#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
FILE *f=fopen("petrol.in","r");
FILE *g=fopen("petrol.out","w");
pair<double,int> D[105],E[105];
double d,e,rez;
int N,i;
int main()
{
    fscanf(f,"%d %lf %lf",&N,&e,&d);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%lf %lf",&E[i].first,&D[i].first);
        D[i].first=d/D[i].first;
        D[i].second=i;
        E[i].first=e/E[i].first;
        E[i].second=i;
    }
    sort(D+1,D+1+N);
    sort(E+1,E+1+N);

    if(D[N].second!=E[N].second)
        rez=D[N].first+E[N].first;
    else
        rez=max(D[N].first+E[N-1].first,D[N-1].first+E[N].first);
    fprintf(g,"%f",rez);
    fclose(f);
    fclose(g);
    return 0;
}
