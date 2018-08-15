#include <cstdio>
#include <iostream>
#include <cstring>
#define val first
#define sens second
using namespace std;
FILE *f=fopen("palalila2.in","r");
FILE *g=fopen("palalila2.out","w");
int N,i,j,rez;
char C[600000];
int main()
{
    fgets(C,600000,f);
    N=strlen(C)-1;
    i=0;
    while(i+1<N)
    {
        while(C[i]>=C[i+1]&&i+1<N)
        {
            i++;
        }
        rez++;
        if(i+1<N)
            rez++;
        while(C[i]<=C[i+1]&&i+1<N)
            i++;
    }
    fprintf(g,"%d",rez);
    return 0;
}
