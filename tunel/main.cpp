#include <cstdio>
#include <iostream>
#include <map>
#include <cstring>
using namespace std;
FILE *f=fopen("tunel.in","r");
FILE *g=fopen("tunel.out","w");
char A[10];
char B[10];
int i,j,N,nr,poz[1005];
map <string,int> M;
int main()
{
    fscanf(f,"%d\n",&N);
    for(i=1;i<=N;i++)
    {
        fgets(A,10,f);
        M[A]=i;
    }
    for(i=1;i<=N;i++)
    {
        fgets(B,10,f);
        poz[M[B]]=i;
    }
    for(j=1;j<=N;j++)
    {
        for(i=1;i<j;i++)
        {
            if(poz[j]<poz[i])
                {nr++;break;}
        }
    }
    fprintf(g,"%d",nr);
    fclose(f);
    fclose(g);
    return 0;
}
