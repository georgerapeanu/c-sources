#include <cstdio>
using namespace std;
int n,i[1000000],d[1000000],j;
long best[1000000],rest;
int max(int a,int b)
{
    return a>b ? a:b;
}
int main()
{
    FILE *f;
    f=fopen("pachete.in","r");
    fscanf(f,"%d",&n);
    for(j=0;j<n;j++)
    {
        fscanf(f,"%d %d",&i[j],&d[j]);
    }
    fclose(f);
    for(j=n-1;j>=0;j--)
    {
        best[j]=d[j]+max(0,best[j+1]-i[j]);
    }
    f=fopen("pachete.out","w");
    fprintf(f,"%ld",best[0]);
    fclose(f);
    return 0;
}
