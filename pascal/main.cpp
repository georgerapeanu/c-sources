#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("pascal.in","r");
FILE *g=fopen("pascal.out","w");
int a[5000005];
int b[5000005];
int c[5000005];
int R,D,rez;
int main()
{
    fscanf(f,"%d %d",&R,&D);
    for(int i=1;i<=R;i++)
    {
        if(i%2==0)a[i]=a[i/2]+1;
        if(i%3==0)b[i]=b[i/3]+1;
        if(i%5==0)c[i]=c[i/5]+1;
    }
    int s1,s2,s3;s1=s2=s3=0;
    for(int i=1;i<=R;i++)
    {
        s1+=a[R-i+1]-a[i];
        s2+=b[R-i+1]-b[i];
        s3+=c[R-i+1]-c[i];
        if(D==2&&s1>0)rez++;
        else if(D==3&&s2>0)rez++;
        else if(D==5&&s3>0)rez++;
        else if(D==4&&s1/2>0)rez++;
        else if(D==6&&s1>0&&s2>0)rez++;
    }
    fprintf(g,"%d",rez);
    fclose(f);
    fclose(g);
    return 0;
}
