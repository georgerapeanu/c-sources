#include <cstdio>
#include <algorithm>
#include <bitset>
#define a first.first
#define b first.second
#define nr second
using namespace std;
FILE *f=fopen("gramezi.in","r");
FILE *g=fopen("gramezi.out","w");
int N,rez1,rez2;
bitset <30005> activ;
pair<pair<int,int>,int> A[30005],B[30005];
int main()
{
    fscanf(f,"%d",&N);
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d %d",&A[i].b,&B[i].b);
        A[i].nr=B[i].nr=i;
        A[i].a=B[i].a=A[i].b+B[i].b;
    }
    sort(A+1,A+1+N);
    sort(B+1,B+1+N);
    if(N%2==1)
    {
        int i1=N,i2=N;
        for(int i=N;i>1;i-=2)
        {
            while(activ[A[i1].nr])
                i1--;
            rez1+=A[i1].b;
            activ[A[i1].nr]=1;
            while(activ[B[i2].nr])
                i2--;
            rez2+=B[i2].b;
            activ[B[i2].nr]=1;
        }
         while(activ[A[i1].nr])
                i1--;
            rez1+=A[i1].b;
            activ[A[i1].nr]=1;
    }
    else
    {
        int i1=N,i2=N;
        for(int i=N;i;i-=2)
        {
            while(activ[A[i1].nr])
                i1--;
            rez1+=A[i1].b;
            activ[A[i1].nr]=1;
            while(activ[B[i2].nr])
                i2--;
            rez2+=B[i2].b;
            activ[B[i2].nr]=1;
        }
    }
    fprintf(g,"%d %d",rez1,rez2);
    fclose(f);
    fclose(g);
    return 0;
}
