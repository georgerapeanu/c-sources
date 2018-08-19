#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("taxi.in","r");
FILE *g=fopen("taxi.out","w");
int A,B,x1,x2,YY,y2,XM,YM,l;
int drx,dry,stx,sty;
int x,y;
int T;
int gcd(int a,int b)
{
    if(!b)
        return a;
    return gcd(b,a%b);
}
int main()
{
    fscanf(f,"%d",&T);
    while(T--)
    {
        fscanf(f,"%d%d%d%d%d%d",&A,&B,&x1,&YY,&x2,&y2);
        if(x1>x2)
        {
            swap(x1,x2);
            swap(YY,y2);
        }
        if((x1+x2)%2!=(YY+y2)%2)
            fprintf(g,"0");
        else if(x1==x2&&YY==y2)
        {
            fprintf(g,"%d",(A+1)*(B+1));
        }
        else if(x1==x2)
        {
            fprintf(g,"%d",A+1);
        }
        else if(YY==y2)
        {
            fprintf(g,"%d",B+1);
        }
        else if(YY<=y2)
        {
            fprintf(g,"%d",(B-y2+1)*(x1+1)+(YY+1)*(A-x2+1)+gcd(x2-x1,y2-YY)-1);
        }
        else
        {
            fprintf(g,"%d",(x1+1)*(y2+1)+(B-YY+1)*(A-x2+1)+gcd(x2-x1,YY-y2)-1);
        }
        fprintf(g,"\n");
    }
    fclose(f);
    fclose(g);
    return 0;
}
