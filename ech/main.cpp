#include <cstdio>
#include <cstring>
using namespace std;
FILE *f=fopen("ech.in","r");
FILE *g=fopen("ech.out","w");
char c[30];
short N[30];
int i,r,l;
void add(int val)
{
    N[N[0]]+=val;
    for(i=N[0];i>=2;i--)
    {N[i-1]+=N[i]/10;N[i]%=10;}
    if(N[1]>9)
    {
        for(i=N[0]+1;i>1;i--)
            N[i]=N[i-1];
        N[1]=N[2]/10;
        N[2]=N[2]%10;
        N[0]++;
    }
}
bool ech()
{
    int a=0,b=0;
    for(i=1;i<=N[0];i++)
        if(i%2==0)
            a+=N[i];
        else
            b+=N[i];
    return a==b;
}
void impart()
{
    int r;
    r=0;
    for(i=1;i<=N[0];i++)
    {
        r=r*10+N[i];
        r%=11;
    }
    if(r!=0)
        add(11-r);
    while(!ech())
        add(11);
}
int main()
{
    c[0]='.';
    fgets(c+1,30,f);
    N[0]=strlen(c)-2;
    for(i=1;i<=N[0];i++)
        N[i]=c[i]-'0';
    add(1);
    impart();
    for(i=1;i<=N[0];i++)
        c[i-1]=N[i]+'0';
    c[N[0]]='\0';
    fputs(c,g);
    fclose(f);
    fclose(g);
    return 0;
}
/*
//Lucia Miron
//numerele echilibrate sunt divizibile cu 11, verific doar aceste numere
#include <fstream>
using namespace std;
ifstream fin("ech.in");
ofstream fout("ech.out");
int n,v[50],r;
void aduna11(int r)
{
    int i,t,aux;
    t=r;
    for(i=1;i<=v[0];i++)
    {
        aux=v[i]+t;
        v[i]=aux%10;
        t=aux/10;
    }
    if(t)v[++v[0]]=t;
}

int main()
{
    citire();
    r=rest11();
    if(r)aduna11(11-r);
    else aduna11(11);
    while(!ech())aduna11(11);
    afis();
    fout.close();
    return 0;
}
*/
