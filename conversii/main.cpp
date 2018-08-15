#include <fstream>
using namespace std;
ifstream f("conversii.in");
ofstream g("conversii.out");
void cifre_romane()
{
    char c,c1;
    long nr=0;
    do
    {
        c=f.get();
        c1=f.get();
        if(c=='C'&&c1=='M')
        {
             nr+=900;
        }
        else if(c=='C'&&c1=='D')
        {
             nr+=400;
        }
        else if(c=='X'&&c1=='C')
        {
            nr+=90;
        }
        else if(c=='X'&&c1=='L')
        {
            nr+=40;
        }
        else if(c=='I'&&c1=='X')
        {
             nr+=9;
        }
        else if(c=='I'&&c1=='V')
        {
             nr+=4;
        }
        else
        {
            f.putback(c1);
            switch(c)
            {
                case 'M':nr+=1000;break;
                case 'D':nr+=500;break;
                case 'C':nr+=100;break;
                case 'L':nr+=50;break;
                case 'X':nr+=10;break;
                case 'V':nr+=5;break;
                case 'I':nr+=1;break;
            }
        }
    }
    while(c!=-1);
    g<<nr;
}
void adunare(int termen1[],int termen2[],int baza)
{
    while(termen1[0]>termen2[0])
    {
        for(int i=2;i<=termen2[0]+1;i++)
        termen2[i]=termen2[i-1];
        termen2[1]=0;
        termen2[0]++;
    }
    while(termen2[0]>termen1[0])
    {
      for(int i=2;i<=termen1[0]+1;i++)
        termen1[i]=termen1[i-1];
        termen1[1]=0;
        termen1[0]++;
    }
    for(int i=1;i<=termen1[0];i++)
    termen1[i]+=termen2[i];
    for(int i=2;i<=termen1[0];i++)
    if(termen1[i]>=baza)
    {termen1[i-1]+=termen1[i]/baza;termen1[i]%=baza;}
    while(termen1[1]>baza)
    {
        for(int i=2;i<=termen1[0]+1;i++)
        termen1[i]=termen1[i-1];
        termen1[1]=termen1[2]/baza;
        termen1[2]%=baza;
        termen1[0]++;
    }
    for(int i=1;i<=termen1[0];i++)
    g<<termen1[i];
}
void scadere(int termen1[],int termen2[],int baza)
{
    while(termen1[0]>termen2[0])
    {
        for(int i=2;i<=termen2[0]+1;i++)
        termen2[i]=termen2[i-1];
        termen2[1]=0;
        termen2[0]++;
    }
    while(termen2[0]>termen1[0])
    {
      for(int i=2;i<=termen1[0]+1;i++)
        termen1[i]=termen1[i-1];
        termen1[1]=0;
        termen1[0]++;
    }
    for(int i=1;i<=termen1[0];i++)
    termen1[i]-=termen2[i];
    for(int i=termen1[0];i>=2;i--)
    if(termen1[i]<0)
    {
        termen1[i-1]--;
        termen1[i]+=baza;
    }
      while(termen1[1]==0)
    {
        for(int i=1;i<termen1[0]+1;i++)
        termen1[i]=termen1[i+1];
        termen1[0]--;
    }
    for(int i=1;i<=termen1[0];i++)
    g<<termen1[i];
}
int main()
{
    int n,m,a[200]={0},b[200]={0};
    f>>n>>m;
    for(int i=1;i<=n;i++)
    f>>a[i];
    for(int i=1;i<=m;i++)
    f>>b[i];
    a[0]=n;
    b[0]=m;
    scadere(a,b,8);
    return 0;
}
