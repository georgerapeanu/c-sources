#include <cstdio>
#include <queue>
#define val first
#define poz second
using namespace std;
FILE *f=fopen("auto.in","r");
FILE *g=fopen("auto.out","w");
int V[9005];
int N;
int S;
bool check(int k)
{
    queue<pair<int,int> > Q;
    int sum=0;
    for(int i=1;i<=N;i++)
    {
        while(!Q.empty()&&Q.front().poz<=i-k)
        {sum-=Q.front().val;Q.pop();}
        int v=V[i]-sum;
        if(v<0)
            return 0;
        else
        {
            if(i<=N-k+1)
            {
                sum+=v;
                Q.push(make_pair(v,i));
            }
            else
            {
                if(v!=0) return 0;
            }
        }
    }
    return 1;
}
int main()
{
    int T;
    fscanf(f,"%d\n",&T);
    while(T--)
    {
        fscanf(f,"%d",&N);
        S=0;
        for(int i=1;i<=N;i++)
            {fscanf(f,"%d",&V[i]);S+=V[i];}
        for(int d=1;d<=N&&d<=S;d++)
            if(S%d==0&&check(d))
                fprintf(g,"%d ",d);
        fputc('\n',g);
    }
    fclose(f);
    fclose(g);
    return 0;
}
