#include <cstdio>
#include <deque>
using namespace std;
FILE *f=fopen("secv3.in","r");
FILE *g=fopen("secv3.out","w");
long double st,dr=1000;
int A[30005];
int B[30005];
int N,L,U;
deque<int> D;
long double S[30005];
bool check(long double rap)
{
    D.clear();
    for(int i=1;i<=N;i++)
    {
        long double val=A[i]-rap*B[i];
        S[i]=S[i-1]+val;
        while(!D.empty()&&D.front()<=i-U)D.pop_front();
        if(i-L>=0)
        {
            while(!D.empty()&&S[D.back()]>=S[i-L])D.pop_back();
            D.push_back(i-L);
        }
        if(!D.empty()&&S[D.front()]<=S[i])
            return 1;
    }
    return 0;
}
int main()
{
    fscanf(f,"%d %d %d",&N,&L,&U);
    for(int i=1;i<=N;i++)fscanf(f,"%d",&A[i]);
    for(int i=1;i<=N;i++)fscanf(f,"%d",&B[i]);
    while(dr-st>1e-8)
    {
        long double mid=(st+dr)/2;
        if(check(mid))
            st=mid;
        else
            dr=mid;
    }
    fprintf(g,"%.6Lf",st);
    fclose(f);
    fclose(g);
    return 0;
}
