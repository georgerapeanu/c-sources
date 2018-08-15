#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
FILE *f=fopen("inventie.in","r");
FILE *g=fopen("inventie.out","w");
int N;
unsigned long long mina=999999999999999999;
unsigned long long minb=999999999999999999;
unsigned long long maxa,maxb;
int i,nrcf;
unsigned long long a,b,d,e,p10,lA,lB,lC;
char A[40];
char B[40];
char C[40];
int main()
{
    fscanf(f,"%d",&N);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%llu %llu",&a,&b);
        if(a>b)
        {
            d=a-b;
        }
        else
            d=b-a;
        e=a+b;
        if(d!=0)
            fprintf(g,"%llu%llu\n",d,e);
        else
            fprintf(g,"%llu\n",e);
        if(e&1)
        {
            sprintf(A,"%llu%llu",d,e);lA=strlen(A);
            sprintf(B,"%llu%llu",mina,minb);lB=strlen(B);
            sprintf(C,"%llu%llu",maxa,maxb);lC=strlen(C);
            if(lA<lB)
            {
                mina=d;
                minb=e;
            }
            else if(lA==lB)
            {
                if(strcmp(A,B)==-1)
                {mina=d;
                    minb=e;}
            }
            if(lA>lC)
            {
                maxa=d;
                maxb=e;
            }
            else if(lA==lC)
            {
                if(strcmp(A,C)==1)
                {maxa=d;
                    maxb=e;}
            }
        }

    }
    if(maxa==0&&maxb==0)
        fprintf(g,"0");
    else
        {
            if(mina)
                fprintf(g,"%llu",mina);
            fprintf(g,"%llu\n",minb);
            if(maxa)
                fprintf(g,"%llu",maxa);
            fprintf(g,"%llu\n",maxb);
        }
    fclose(f);
    fclose(g);
    return 0;
}
