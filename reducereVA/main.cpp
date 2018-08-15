#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("reducere.in","r");
FILE *g=fopen("reducere.out","w");
double X[1<<16];
double Y[1<<16];
int G[1<<16];
double dp[1<<16];
int N;
double dist(double x1,double y1,double x2,double y2)
{
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
int main()
{
    fscanf(f,"%d\n",&N);
    int CONF=(1<<N)-1;
    for(int i=1;i<=CONF;i++)dp[i]=1e9;
    for(int i=1;i<=N;i++)
    {
        double x,y;
        fscanf(f,"%lf %lf",&x,&y);
        X[1<<(i-1)]=x;
        Y[1<<(i-1)]=y;
        G[1<<(i-1)]=1;
        dp[1<<(i-1)]=0;
    }
    for(int conf=1;conf<=CONF;conf++)
    {
        int aconf=(conf-1)&conf;
        for(int conf2=aconf;conf2;conf2=(conf2-1)&aconf)
        {
            double newcost=dp[conf2]+dp[conf2^conf]+G[conf2]*G[conf^conf2]*dist(X[conf2],Y[conf2],X[conf^conf2],Y[conf^conf2]);
            if(newcost<dp[conf])
            {
                dp[conf]=newcost;
                if(!G[conf])
                {
                    G[conf]=G[conf2]+G[conf^conf2];
                    X[conf]=(X[conf2]*G[conf2]+X[conf^conf2]*G[conf^conf2])/G[conf];
                    Y[conf]=(Y[conf2]*G[conf2]+Y[conf^conf2]*G[conf^conf2])/G[conf];
                }
            }
        }
    }
    fprintf(g,"%.6f",dp[CONF]);
    fclose(f);
    fclose(g);
    return 0;
}
