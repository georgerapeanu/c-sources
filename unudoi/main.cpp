#include <cstdio>
#include <cstring>
#include <fstream>
#include <algorithm>
#include <set>
using namespace std;
FILE *f=fopen("unudoi.in","r");
FILE *g=fopen("unudoi.out","w");
pair <int,int> A[100005];
int N,M,i,j,rez;
int main()
{
    fscanf(f,"%d %d",&N,&M);
    for(i=1;i<=N;i++)
        {fscanf(f,"%d",&A[i].first);A[i].second=1;}
    for(i=N+1;i<=N+M;i++)
        {fscanf(f,"%d",&A[i].first);A[i].second=2;}
        sort(A+1,A+1+N+M);

    for(i=1;i<=N+M;i++)
    {
        if(A[i].second==1)
        {while(i<=N+M&&A[i].second==A[i+1].second&&A[i].second==1)
            i++;
        rez++;}
    }
    fprintf(g,"%d",rez);
    fclose(f);
    fclose(g);
    return 0;
}
