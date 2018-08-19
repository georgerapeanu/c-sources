#include <cstdio>
#include <algorithm>
using namespace std;
long long n,k,v[1000000],i;
bool gasit=0;
int find_k_elem(int k,int st,int dr)
{
    int u,p;
    u=st;
    p=dr;
    while(u!=p)
    {
        while(v[u]<=v[p]&&u<p)
            p--;
        swap(v[u],v[p]);
        while(v[u]<=v[p]&&u<p)
            u++;
        swap(v[u],v[p]);
    }
    if(k==u-st+1)
        return v[u];
    if(u-st>=k)
        return find_k_elem(k,st,u-1);
    return find_k_elem(k-u+st-1,u+1,dr);
}
int main()
{
    FILE *f,*g;
    f=fopen("selectie.in","r");
    g=fopen("selectie.out","w");
    fscanf(f,"%llu %llu",&n,&k);
    for(i=1;i<=n;i++)
    {
        fscanf(f,"%llu",&v[i]);
    }
    fprintf(g,"%d",find_k_elem(k,1,n));
    fclose(g);
    return 0;
}
