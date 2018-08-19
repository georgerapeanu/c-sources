#include <cstdio>
#include <stack>
using namespace std;
FILE *f=fopen("maxp.in","r");
FILE *g=fopen("maxp.out","w");
stack <int> S;
int st[200005];
int dr[200005];
int V[200005];
int N;
long long rez,tmp;
int nrmax;
int main()
{
    fscanf(f,"%d",&N);
    V[0]=1000000;
    V[N+1]=1000000;
    S.push(0);
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d",&V[i]);
        while(V[S.top()]<V[i])
            S.pop();
        st[i]=S.top();
        S.push(i);
    }
    while(!S.empty())
        S.pop();
    S.push(N+1);
    for(int i=N;i>=1;i--)
    {
        while(V[S.top()]<V[i])
            S.pop();
        dr[i]=S.top();
        S.push(i);
        tmp=((long long)(dr[i]-i))*(i-st[i]);
        if(rez<tmp)
        {
            rez=tmp;
            nrmax=1;
        }
        else if(rez==tmp)
        {
            nrmax++;
        }
    }
    fprintf(g,"%lld\n%d",rez,nrmax);
    fclose(f);
    fclose(g);
    return 0;
}
