#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("fibonacci.in","r");
FILE *g=fopen("fibonacci.out","w");
short V[50005],X[50005];
short i,N,M,j,c,l1,l2;
short a,b;
bool ok;
int main()
{
    fscanf(f,"%d",&N);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d",&M);
        for(j=M;j>0;j--)
        {
            fscanf(f,"%hd",&V[j]);
        }
        l1=M;
        fscanf(f,"%d",&M);
        for(j=M;j>0;j--)
        {
            fscanf(f,"%hd",&X[j]);
        }
        l2=M;
       a=min(l1,l2);
       for(j=1;j<=a;j++)
       {
           if(X[j]==V[j]&&X[j]==1)
            X[j]=V[j]=0;
       }
       j=2;
       do
       {
            if(V[j]>=X[j])
           {V[j]-=X[j];X[j]=0;}
           j++;
           a=min(V[j-1],V[j-2]);
           V[j-1]-=a;
           V[j-2]-=a;
           V[j]+=a;
       }
        while(j<=l1||V[j]);
        l1=j;
         j=2;
       do
       {
            if(X[j]>=V[j])
            {X[j]-=V[j];V[j]=0;}
           j++;
           a=min(X[j-1],X[j-2]);
           X[j-1]-=a;
           X[j-2]-=a;
           X[j]+=a;
       }
        while(j<=l2||X[j]);
        l2=j;
        if(l1!=l2)
            fprintf(g,"NU\n");
        else
        {
            ok=1;
            for(j=1;j<=l1&&ok;j++)
                if(V[j]!=X[j])
                    ok=0;
            if(ok)
                fprintf(g,"DA\n");
            else
                fprintf(g,"NU\n");
        }
        a=max(l1,l2);
        for(j=1;j<=a;j++)
            V[j]=X[j]=0;
    }
    fclose(f);
    fclose(g);
    return 0;
}
