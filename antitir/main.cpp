#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("antitir.in","r");
FILE *g=fopen("antitir.out","w");
long long X[1000005];
long long Y[1000005];
int N,i;
long long test()
{
    long long s=0;
    for(int i=1;i<=N;i++)
        s+=( X[i]-X[(1+N)/2]<0 ? X[(1+N)/2]-X[i]:X[i]-X[(1+N)/2] )+ ( Y[i]-Y[(1+N)/2]<0 ? Y[(1+N)/2]-Y[i]:Y[i]-Y[(1+N)/2] );
    return s;
}
void qsx(int st,int dr,int poz)
{
    int pivot=X[dr],j=st;
    for (int i=st;i<dr;i++)
    {
        if(X[i]<=pivot)
        {
            swap(X[i],X[j]);
            j++;
        }
    }
    swap(X[j],X[dr]);
    if(j-st+1==poz)
        ;
    else if(j-st+1>poz)
        qsx(st,j-1,poz);
    else
        qsx(j+1,dr,poz-j+st-1);
}
void qsy(int st,int dr,int poz)
{
    int pivot=Y[dr],j=st;
    for (int i=st;i<dr;i++)
    {
        if(Y[i]<=pivot)
        {
            swap(Y[i],Y[j]);
            j++;
        }
    }
    swap(Y[j],Y[dr]);
    if(j-st+1==poz)
        ;
    else if(j-st+1>poz)
        qsy(st,j-1,poz);
    else
        qsy(j+1,dr,poz-j+st-1);
}
int main()
{
    fscanf(f,"%lld",&N);
    for(i=1;i<=N;i++)
        fscanf(f,"%lld %lld",&X[i],&Y[i]);
    qsx(1,N,(N+1)/2);
    qsy(1,N,(N+1)/2);
    fprintf(g,"%lld",test());
    fclose(f);
    fclose(g);
    return 0;
}
