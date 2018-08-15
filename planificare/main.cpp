#include <cstdio>
#include <algorithm>
#include <set>
#define tip first.second
#define ind second.first
#define Y second.second
using namespace std;
FILE *f=fopen("planificare.in","r");
FILE *g=fopen("planificare.out","w");
multiset<int> S;
pair<pair<int,int>,pair<int,int> > E[200005];
int N,K,nr,x,y;
class cmp
{
    bool operator() (int a,int b) {return a<=b;}
};
int main()
{
    fscanf(f,"%d%d",&N,&K);
    for(int i=1;i<=N;i++)
    {fscanf(f,"%d %d",&x,&y);E[2*i-1]=make_pair(make_pair(x,1),make_pair(i,y));E[2*i]=make_pair(make_pair(y,-1),make_pair(i,y));}
    sort(E+1,E+1+2*N);///impartire pe evenimente,in/out
    ///daca ev de iesire scoatem intervalul(daca exista) din multiset
    ///daca ev de intrate
    ///cazul 1:in set avem<K elem-il bagam,de ce nu?
    ///cazul 2:exista un ev care e eliberat mai tarziu in set.e mai prost.il punem pe asta nou in schimb
    for(int i=1;i<=2*N;i++)
    {
        multiset<int> :: iterator it;
        if(E[i].tip==-1)
        {
            S.erase(E[i].Y);
        }
        else
        {
            multiset <int> ::iterator it;
            if(S.size()<K)
            {S.insert(E[i].Y);nr++;}
            else
            {
                it=S.end();
                it--;
                if(*it>E[i].Y)
                {
                    S.erase(it);
                    S.insert(E[i].Y);
                }
            }
        }
    }
    fprintf(g,"%d",nr);
    return 0;
}
