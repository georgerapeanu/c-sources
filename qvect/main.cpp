#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;
FILE *f=fopen("qvect.in","r");
FILE *g=fopen("qvect.out","w");
int N,M;
vector<int> V[101];
int eval(int i,int j,int val)
{
    int nr=0;
    for(int k=i;k<=j;k++)
    {
        int st,dr;
        st=0;
        dr=V[k].size()-1;
        while(st<dr)
        {
            if(V[k][(st+dr+1)/2]<=val)
                st=(st+dr+1)/2;
            else
                dr=(st+dr+1)/2-1;
        }
        nr+=(dr+1-(dr<0||(dr==0&&V[k][dr]>val)));
    }
    return nr;
}
int c2(int i,int j)
{
    int nr=0;
    for(int l=i;l<=j;l++)
        nr+=V[l].size();
    nr/=2;
    int st=-1000000000,dr=1000000000,last;
    while(st<=dr)
    {
        int mid=(st+dr)/2;
        if(eval(i,j,mid)>=nr)
        {
            last=mid;
            dr=mid-1;
        }
        else
            st=mid+1;
    }
    return last;
}
int c1(int i,int j)
{
    int rez=2000000000;
    int n=V[i].size(),m=V[j].size();
    int a=0,b=0;
    while(1)
    {
        if(a==n-1&&b==m-1) break;
        rez=min(rez,abs(V[i][a]-V[j][b]));
        if(a<n-1&&(V[i][a]<V[j][b]||b==m-1)) a++;
        else b++;
    }
    return rez;
}
int main()
{
    fscanf(f,"%d%d",&N,&M);
    for(int i=1;i<=N;i++)
    {
        int nr;
        fscanf(f,"%d",&nr);
        for(int j=1;j<=nr;j++)
        {
            int val;
            fscanf(f,"%d",&val);
            V[i].push_back(val);
        }
    }
    for(int i=1;i<=M;i++)
    {
        int c,a,b;
        fscanf(f,"%d%d%d",&c,&a,&b);
        if(c==1) fprintf(g,"%d\n",c1(a,b));
        else fprintf(g,"%d\n",c2(a,b));
    }
    fclose(f);
    fclose(g);
    return 0;
}
