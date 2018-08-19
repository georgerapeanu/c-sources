//#include <cstdio>
#include <bitset>
#include <fstream>
#include <algorithm>
using namespace std;
//FILE *f=fopen("placute.in","r");
//FILE *g=fopen("placute.out","w");
ifstream f("placute.in");
ofstream g("placute.out");
long long N,K;
long long gr,c,i,j;
typedef struct{long long kg,cl;} porc;
porc a;
bitset <100005> U;
bool cmp(porc a,porc b)
{
        return a.kg<b.kg;
}
porc V[100005];
int main()
{
    //fscanf(f,"%lld %lld",&N,&K);
    f>>N>>K;
    for(i=1;i<=N;i++)
    {
        //fscanf(f,"%lld %lld",&V[i].kg,&V[i].cl);
        f>>V[i].kg>>V[i].cl;
    }
    sort(V+1,V+1+N,cmp);
    i=N;
    j=N-1;
    while(i>0)
    {
        if(U[i])
            {i--;continue;}
        if(a.cl!=V[i].cl)
        {
            gr+=V[i].kg;
            a=V[i];
            i--;
        }
        else
        {
            if(j>=i)
                j=i-1;
            while(j>0&&a.cl==V[j].cl)
            {
                j--;
            }
            if(j<=0)
                break;
            a=V[j];
            gr+=V[j].kg;
            U[j]=1;
            j--;
        }
    }
    //fprintf(g,"%lld",gr);
    g<<gr;
   // fclose(f);
    //fclose(g);
    f.close();
    g.close();
    return 0;
}
