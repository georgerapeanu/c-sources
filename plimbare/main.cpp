#include <cstdio>
#include <cmath>
using namespace std;
FILE *f,*g;
int i,n,ck,k,nr,suma,coo;
bool v[25],temp;
char s[24][4];
int main()
{
    f=fopen("plimbare.in","r");
    g=fopen("plimbare.out","w");
    fscanf(f,"%d %d",&n,&k);
    ck=k;
    nr=pow(2,n-1);
    for(i=0;i<n;i++)
    {
        if(n-i-1<10)
        {
            s[i][0]='0'+(n-i-1);
        }
        else
        {
            s[i][0]='0'+(n-i-1)/10;
            s[i][1]='0'+(n-i-1)%10;
        }
    }
    while(k!=0)
    {
        v[++coo]=k%2;
        k/=2;
    }
    for(i=1;i<=coo/2;i++)
    {
        temp=v[i];
        v[i]=v[coo-i+1];
        v[coo-i+1]=temp;
    }
    if(coo<n)
    while(coo<n)
    {
        for(i=coo+1;i>=1;i--)
        v[i]=v[i-1];
        v[1]=0;
        coo++;
    }
    if(s[0][1]=='\0')
    s[0][1]='+';
    else
    s[0][2]='+';
    suma+=nr;nr/=2;
    for(i=1;i<=n;i++)
    {
       if(v[i]==1)
       {
           if(n-i-1<10)
          s[i][1]='+';
          else
          s[i][2]='+';
          suma+=nr;
       }
       else
       {
           if(n-1-i<10)
          s[i][1]='-';
          else
          s[i][2]='-';
          suma-=nr;
       }
       nr/=2;
    }
    if(suma==ck)
    {
        for(i=0;i<n;i++)
        fprintf(g,"%s\n",s[i]);
    }
    else
    fprintf(g,"%d",0);
    fclose(f);
    fclose(g);
    return 0;
}
