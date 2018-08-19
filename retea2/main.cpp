#include <fstream>
#include <cmath>
#include <algorithm>
using namespace std;
ifstream f("retea2.in");
ofstream g("retea2.out");
int N,M;
typedef struct{double x,y;} punct;
double dist[2100],rez,minim;
punct ge[2100];
punct p[2100];
bool viz[2100];
int i,j,x,nrc;
char afis[2100];
double D(punct A,punct B)
{
    return sqrt(pow(A.x-B.x,2)+pow(A.y-B.y,2));
}
int main()
{
    f>>N>>M;
    for(i=1;i<=N;i++)
    {
        f>>ge[i].x>>ge[i].y;
    }
    for(i=1;i<=N;i++)
    {
        f>>p[i].x>>p[i].y;
        dist[i]=D(p[i],ge[1]);
        for(j=2;j<=N;j++)
            dist[i]=min(dist[i],D(p[i],ge[j]));
    }
    for(i=1;i<=M;i++)
    {
        minim=9999999999;
        x=0;
        for(j=1;j<=M;j++)
        {
            if(dist[j]<minim&&!viz[j])
                {minim=dist[j];x=j;}
        }
        viz[x]=1;
        for(j=1;j<=M;j++)
        {
            if(!viz[j])
            dist[j]=min(dist[j],D(p[x],p[j]));
        }
        rez+=minim;
    }
    x=rez;
    while(x)
    {
        nrc++;
        x/=10;
    }
    x=sprintf(afis,"%lf",rez);
    g<<afis;
    f.close();
    g.close();
    return 0;
}
