#include <cstdio>
#include <queue>
#define pb push_back
#define NMAX 100005
#define x first.first
#define y first.second
#define ev second
using namespace std;
FILE *f=fopen("bulevard.in","r");
FILE *g=fopen("bulevard.out","w");
int N,V[NMAX],T,rez,a,b;
vector<pair<pair<int,int>,int> > D;/// D[i].x-indicele din vectorul V a primului eveniment care se intampla in timpul politistului plasat pe i(kindof)
///.y unde se termina
///.ev cate evenimente au loc
int Y[NMAX];///cel mai bun indice din vector pentru plasarea celuilalt politist in perioada evenimentelor i,...,N
int main()
{
    fscanf(f,"%d",&N);
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d",&V[i]);
    }
    fscanf(f,"%d",&T);
    int j=0;
    D.pb(make_pair(make_pair(0,0),0));
    for(int i=1;i<=N;i++)
    {
        j=max(i,j);
        while(j<N&&V[j+1]-V[i]<=T) j++;
        D.pb(make_pair(make_pair(i,j),j-i+1));
    }
    for(int i=N;i;i--)
    {
        if(D[i].ev>=D[Y[i+1]].ev) Y[i]=i;
        else Y[i]=Y[i+1];
        int rez1,a1,b1;
        rez1=D[i].ev+D[Y[D[i].y+1]].ev;
        a1=max(0,V[D[i].y]-T);
        b1=max(0,V[D[Y[D[i].y+1]].y]-T);///pare ciudat,dar daca intelegi Y si D ce rol au intelegi de ce e bine
        if(rez1>rez||(rez1==rez&&(a1<a||(a1==a&&a1+b1<a+b)))) rez=rez1,a=a1,b=b1;
    }
    fprintf(g,"%d\n%d %d",rez,a,b);
    fclose(f);
    fclose(g);
    return 0;
}
