#include <cstdio>
#include <set>
#define mp make_pair
using namespace std;
FILE *f=fopen("roata.in","r");
FILE *g=fopen("roata.out","w");
int rot[100005];
int N,P;
long long suma;
set<pair<long long,int> > Ev;
int roata[100005];
int ord[100005];
int len=0;
int main()
{
    fscanf(f,"%d%d",&N,&P);
    for(int i=1;i<=P;i++)
    {
        fscanf(f,"%d",&rot[i]);
        suma+=rot[i];
    }
    int ind=0;
    for(int i=1;i<=P&&i<=N;i++)
    {
        Ev.insert(mp(i+1LL*rot[i]*N,i));
        roata[i]=i;
    }
    ind=min(P,N)+1;
    int urot;
    while(!Ev.empty())
    {
        ord[++len]=(*Ev.begin()).second;
        urot=roata[ord[len]];
        if(ind<=P)
        {
            roata[ind]=roata[ord[len]];
            Ev.insert(mp((*Ev.begin()).first+1LL*rot[ind]*N,ind));
            ind++;
        }
        Ev.erase(Ev.begin());
    }
    fprintf(g,"%lld\n",suma);
    for(int i=1;i<=len;i++)fprintf(g,"%d ",ord[i]);
    fprintf(g,"\n%d",urot);
    fclose(f);
    fclose(g);
    return 0;
}
