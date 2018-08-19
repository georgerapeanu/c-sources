#include <cstdio>
using namespace std;
FILE *f;
int main()
{
    short n=0,p=0,q=0;
    f=fopen("viespi.in","r");
    fscanf(f,"%hd %hd %hd",&n,&p,&q);
    fclose(f);
    short i=0,temp=0;
    for(i=3;i<=n;i++)
    {
        temp=4*q-p;
        p=q;
        q=temp;
    }
    f=fopen("viespi.out","w");
    fprintf(f,"%hd",q);
    fclose(f);
    return 0;
}
