#include <cstdio>
using namespace std;
int x,y,h,l,r,ci,cj;
double i,j;
int ceil(double x)
{
    return ((x==int(x)) ? x:(x+1));
}
int main()
{
    FILE *f;
    f=fopen("patrate.in","r");
    fscanf(f,"%d%d%d%d",&l,&h,&x,&y);
    fclose(f);
    i=double(x)/l;
    j=double(y)/h;
    ci=int(i);
    cj=int(j);
    if(cj==0)
    cj=ci;
    else
    {
            r=ci%cj;
    while(r!=0)
    {
        ci=cj;
        cj=r;
        r=ci%cj;
    }
    }
    f=fopen("patrate.out","w");
    fprintf(f,"%d",ceil(i+j)-cj);
    fclose(f);
    return 0;
}
