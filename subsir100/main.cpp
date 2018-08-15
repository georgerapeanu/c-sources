#include <cstdio>
#include <map>
#define MOD 1000003
using namespace std;
FILE *f=fopen("subsir100.in","r");
FILE *g=fopen("subsir100.out","w");
map <int,int> frecv;
int N,i,val;
long long rez=1;
int main()
{
    fscanf(f,"%d",&N);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d",&val);
        frecv[val]++;
    }
    for(map <int,int> ::iterator it=frecv.begin();it!=frecv.end();it++)
    {
        rez*=((long long)(*it).second+1);
        rez%=MOD;
    }
    rez--;
    if(rez<0)
        rez+=MOD;
    fprintf(g,"%lld",rez);
    fclose(f);
    fclose(g);
    return 0;
}
