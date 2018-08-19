#include <cstdio>
#include <cstring>
using namespace std;
FILE *f,*g;
char a[6000],b[6000],c[6000];
int main()
{
    int n=0;
    f=fopen("sir.in","r");
    fscanf(f,"%d",&n);
    fclose(f);
    a[0]='a';
    b[0]='b';
    for(int i=3;i<=n;i++)
    {
        strcpy(c,b);
        strcat(b,a);
        strcpy(a,c);
        strcpy(c,"\0");
    }
    g=fopen("sir.out","w");
    if(n>=3)
    fprintf(g,"%s",b);
    else
    {
        if(n==1)
        fprintf(g,"%s",a);
        else
        fprintf(g,"%s",b);
    }
    fclose(g);
    return 0;
}
