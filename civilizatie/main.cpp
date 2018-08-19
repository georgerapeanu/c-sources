#include <cstdio>
#include <algorithm>
#include <bitset>
#include <vector>
#define pb push_back
#define mp make_pair
#define x first
#define y second
#define LEN 30000192
using namespace std;
FILE *f;
FILE *g=fopen("civilizatie.out","w");
int cer,N;
int X,Y;
int t;
pair<int,int> V[2005];
long long rez;
vector<pair<int,int> > E[200005];
int tostop[2005];
int Stopped[2005];
long long arie(long long x)
{
    return 2*x*x-2*x+1;
}
int gtime(int i,int j)///timpul intre 2 sate la momentul actual(cu satele oprite din momentul apelari)
{
    if(j==0)    return min(min(V[i].x,V[i].y),min(X-V[i].x+1,Y-V[i].y+1));
    int d=abs(V[i].x-V[j].x)+abs(V[i].y-V[j].y)+1;
    if(Stopped[j]!=-1) return d-Stopped[j];
    return d/2;
}
void ev(int i,int j)
{
    int t=gtime(i,j);
    E[t].pb(mp(i,j));
}
int ind;
char buffer[LEN];
void readinit(char *c)
{
    f=fopen(c,"r");
    ind=LEN-1;
}
char getch()
{
    ind++;
    if(ind==LEN) {fread(buffer,1,LEN,f);ind=0;}
    return buffer[ind];
}
int i32()
{
    char c=getch();
    while(!('0'<=c&&c<='9'))
        c=getch();
    int nr=0;
    while('0'<=c&&c<='9')
    {
        nr=nr*10+c-'0';
        c=getch();
    }
    return nr;
}
int main()
{
    readinit("civilizatie.in");
    cer=i32();
    X=i32();Y=i32();
    t=i32();
    N=i32();
    for(int i=1;i<=N;i++)
    {
        V[i].x=i32();
        V[i].y=i32();
        Stopped[i]=-1;
    }
    if(cer==1)
    {
        fprintf(g,"%lld",arie(t));
    }
    else
    {
        for(int i=1;i<=N;i++)
        {
            for(int j=N;j>=0;j--)
                if(i!=j)
                    ev(i,j);///presupunem ca  sunt numai cele 2 sate neinfluentate de celelalte
        }
        int active=N;
        for(int i=1;active;i++)
        {
            for(int j=E[i].size()-1;j>=0;j--)
            {
                pair<int,int> p=E[i][j];
                if(Stopped[p.first]==-1&&i==gtime(p.first,p.second))///daca la timul i avem o intalnire valida,oprim satul corespunzator
                {
                    tostop[++tostop[0]]=p.first;
                }
            }
            for(int j=tostop[0];j;j--)
            {
                if(Stopped[tostop[j]]==-1){Stopped[tostop[j]]=i;active--;}
                for(int z=1;z<=N;z++)
                    if(Stopped[z]==-1)
                        ev(z,tostop[j]);
            }
            tostop[0]=0;
        }
        int maxim=0;
        for(int i=1;i<=N;i++)
        {
            rez+=arie(Stopped[i]);
            maxim=max(maxim,Stopped[i]);
        }
        rez=1LL*X*Y-rez;
        fprintf(g,"%lld\n%d",rez,maxim);
    }
    fclose(f);
    fclose(g);
    return 0;
}
