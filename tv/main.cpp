#include <cstdio>
#define valo 86400
using namespace std;
FILE *f=fopen("tv.in","r");
FILE *g=fopen("tv.out","w");
int V[100005];
int tip,N,i,val,d,h,m,s,u,nr,maxim,rez;
char c[10];
int main()
{
    fscanf(f,"%d",&tip);
    fscanf(f,"%d",&N);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d %d:%d:%d",&d,&h,&m,&s);
        V[h*3600+60*m+s]++;
        V[h*3600+60*m+s+d]--;
    }
    fclose(f);
    if(tip==1)
    {
        for(i=0;i<valo;i++)
        {
            nr+=V[i];
            if(nr==0)
               rez++;
        }
        c[0]=rez/36000+'0';
        c[1]=(rez/3600)%10+'0';
        c[2]=':';
        rez%=3600;
        c[3]=rez/600+'0';
        c[4]=(rez/60)%10+'0';
        c[5]=':';
        rez%=60;
        c[6]=rez/10+'0';
        c[7]=rez%10+'0';
        fputs(c,g);
    }
    else
    {
        for(i=1;i<valo;i++)
        {
            nr+=V[i];
            if(nr>maxim)
            {
                maxim=nr;
                u=i;
            }
        }
        c[0]=u/36000+'0';
        c[1]=(u/3600)%10+'0';
        c[2]=':';
        u%=3600;
        c[3]=u/600+'0';
        c[4]=(u/60)%10+'0';
        c[5]=':';
        u%=60;
        c[6]=u/10+'0';
        c[7]=u%10+'0';
        fputs(c,g);
    }
    fclose(g);
    return 0;
}
