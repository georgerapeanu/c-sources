#include <cstdio>
#include <queue>
using namespace std;
FILE *f=fopen("multiplu.in","r");
FILE *g=fopen("multiplu.out","w");
queue <int> Q;
bool rest[2000001];
int div,a,b,r,c,tata[2000001];
bool muchie[2000001];
int afisare(int nr)
{
    if(tata[nr]!=0)
    afisare(tata[nr]);
    fprintf(g,"%d",muchie[nr]);
}
int main()
{
    fscanf(f,"%d %d",&a,&b);
    r=a%b;
    div=b;
    c=a;
    while(r)
    {
        c=div;
        div=r;
        r=c%div;
    }
    div=(a*b)/div;
    tata[1%div]=0;
    muchie[1%div]=1;
    rest[1%div]=1;
    Q.push(1%div);
    while(!Q.empty()&&!rest[0])
    {
        c=Q.front();
        Q.pop();
        if(!rest[(c*10)%div])
        {
            rest[(c*10)%div]=1;
            tata[(c*10)%div]=c;
            muchie[(c*10)%div]=0;
            Q.push((c*10)%div);
        }
         if(!rest[(c*10+1)%div])
        {
            rest[(c*10+1)%div]=1;
            tata[(c*10+1)%div]=c;
            muchie[(c*10+1)%div]=1;
            Q.push((c*10+1)%div);
        }
    }
    afisare(0);
    fclose(f);
    fclose(g);
    return 0;
}
