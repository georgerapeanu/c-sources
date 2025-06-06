#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("2numere.in","r");
FILE *g=fopen("2numere.out","w");
int A[20];
int B[20];
int FA[10];
int FB[10];
int C[20];
int i,j,nr,cif1,cif2,dif,n1,n2,x,y,N;
int main()
{
    fscanf(f,"%d",&N);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d",&A[i]);
        FA[A[i]]++;
    }
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d",&B[i]);
        FB[B[i]]++;
    }
    for(i=0;i<=9;i++)
    {
        while(FA[i]&&FB[i])
            {C[++C[0]]=i;FA[i]--;FB[i]--;}
        while(FA[i])
            {A[++A[0]]=i;FA[i]--;}
        while(FB[i])
            {B[++B[0]]=i;FB[i]--;}
    }
    cif1=10000000;
    for(i=1;i<=A[0];i++)
    {
        for(j=1;j<=B[0];j++)
        {
            if(A[i]-B[j]<cif1-cif2&&A[i]-B[j]>=0)
            {
                cif1=A[i];
                cif2=B[j];
                x=i;
                y=j;
            }
        }
    }
    for(i=1;i<=C[0];i++)
    {
        n1=n1*10+C[i];
    }
    n2=n1;
    if(A[0])
    {
        n1=n1*10+cif1;
        for(i=1;i<=A[0];i++)
        {
            if(i!=x)
                n1=n1*10+A[i];
        }
    }
    if(B[0])
    {
        n2=n2*10+cif2;
        for(j=B[0];j>0;j--)
            if(j!=y)
                n2=n2*10+B[j];
    }
    fprintf(g,"%d\n%d\n%d",n1,n2,n1-n2);
    fclose(f);
    fclose(g);
    return 0;
}
