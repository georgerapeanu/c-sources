#include <cstdio>
using namespace std;
FILE *f=fopen("maxsecv.in","r");
FILE *g=fopen("maxsecv.out","w");
int N;
int m1,m2;
int val,nr;
int main()
{
    fscanf(f,"%d",&N);
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d",&val);
        if(val==1)
            {nr++;continue;}
        if(m1<nr) {m2=m1;m1=nr;}
        else if(m2<nr) m2=nr;
        nr=0;
    }
    if(m1<nr) {m2=m1;m1=nr;}
        else if(m2<nr) m2=nr;
    fprintf(g,"%d",m1+m2);
    return 0;
}
