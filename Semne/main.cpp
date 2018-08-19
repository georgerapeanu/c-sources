#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <vector>
#define pb push_back
using namespace std;
FILE *f=fopen("semne.in","r");
FILE *g=fopen("semne.out","w");
int N;
int V[50005];
long long S,s;
char C[50005];
vector<int> p,m;
int main()
{
    srand(time(NULL));
    fscanf(f,"%d %lld",&N,&S);
    memset(C,'+',N);
    for(int i=0;i<N;i++)
    {
        fscanf(f,"%d",&V[i]);
        p.pb(i);
        s+=V[i];
    }
    while(s!=S)
    {
        if(s>S){int poz=rand()%p.size();C[p[poz]]='-';s-=2*V[p[poz]];m.pb(p[poz]);p[poz]=p.back();p.pop_back();}
        else {int poz=rand()%m.size();C[m[poz]]='+';s+=2*V[m[poz]];p.pb(m[poz]);m[poz]=m.back();m.pop_back();}
    }
    fputs(C,g);
    fclose(f);
    fclose(g);
    return 0;
}
