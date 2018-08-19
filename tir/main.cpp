#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("tir.in","r");
FILE *g=fopen("tir.out","w");
int N,M,K,i,j,cost,l,maxim,x,y,lc;
int V[305][305];
struct {int x,y;} st,dr,v[305];
int main()
{
    fscanf(f,"%d %d %d",&N,&M,&K);
    if(M%2==1)
{
    for(i=1;i<=K;i++)
    {
        fscanf(f,"%d %d",&v[i].x,&v[i].y);
            st={v[i].x-(M+1)/2+1,v[i].y-(M+1)/2+1};
            dr={st.x+M-1,st.y+M-1};
            for(j=st.x;j<=dr.x;j++)
            {
                if(j<=N&&j>=1)
                {
                    for(l=st.y;l<=dr.y;l++)
                    {
                        if(l>=1&&l<=N)
                        {
                            lc=0;
                            lc=j-st.x+1;
                            if(dr.x-j+1<lc)
                                lc=dr.x-j+1;
                            if(l-st.y+1<lc)
                                lc=l-st.y+1;
                            if(dr.y-l+1<lc)
                                lc=dr.y-l+1;
                            V[j][l]+=lc;
                        }
                    }
                }
            }
    }
    for(i=(M+1)/2;i<=N-(M+1)/2+1;i++)
    {
        for(j=(M+1)/2;j<=N-(M+1)/2+1;j++)
        {
            if(maxim<V[i][j])
            {
                maxim=V[i][j];
                x=i;
                y=j;
            }
        }
    }
        fprintf(g,"%d\n%d %d",maxim,x-(M+1)/2+1,y-(M+1)/2+1);
}
    else
    {
         for(i=1;i<=K;i++)
    {
        fscanf(f,"%d %d",&v[i].x,&v[i].y);
    }
    for(i=1;i<=N-M+1;i++)
    {
        for(j=1;j<=N-M+1;j++)
        {
            cost=0;
            for(l=1;l<=K;l++)
            {
                lc=v[l].x-i+1;
                if(lc>i+M-v[l].x)
                    lc=i+M-v[l].x;
                if(lc>v[l].y-j+1)
                    lc=v[l].y-j+1;
                if(lc>j+M-v[l].y)
                    lc=j+M-v[l].y;
                if(lc>0)
                cost+=lc;
            }
            if(cost>maxim)
                {maxim=cost;x=i;y=j;}
        }
    }
    fprintf(g,"%d\n%d %d",maxim,x,y);
    }
    fclose(f);
    fclose(g);
    return 0;
}
