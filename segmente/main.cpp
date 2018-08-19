#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#define co second
#define x first.first
#define y first.second
#define mp make_pair
#define pb push_back
using namespace std;
FILE *f=fopen("segmente.in","r");
FILE *g=fopen("segmente.out","w");
typedef pair<pair<int,int>,int> segm;
int D[1005][1005];
int N,o,v;
vector<segm> O,V;
int inter(segm v,segm o)
{
    if(o.x<=v.co&&v.co<=o.y&&v.x<=o.co&&o.co<=v.y) return 0;
    if(o.x<=v.co&&v.co<=o.y) return min(abs(v.x-o.co),abs(v.y-o.co));
    if(v.x<=o.co&&o.co<=v.y) return min(abs(v.co-o.x),abs(v.co-o.y));
    return max(min(abs(v.x-o.co),abs(v.y-o.co)),min(abs(v.co-o.x),abs(v.co-o.y)));
}
int main()
{
    fscanf(f,"%d",&N);
    for(int i=1;i<=N;i++)
    {
        int X,Y,xx,yy;
        fscanf(f,"%d%d%d%d",&X,&Y,&xx,&yy);
        if(X==xx) V.pb(mp(mp(min(Y,yy),max(Y,yy)),X));
        else O.pb(mp(mp(min(X,xx),max(X,xx)),Y));
    }
    o=O.size();v=V.size();
    for(int i=0;i<v;i++) for(int j=0;j<o;j++)
    {
        D[i][j]=inter(V[i],O[j]);
    }
    int mini=(1<<30);
    if(o<v)
    {
        for(int i=0;i<o;i++)
        {
            for(int j=i+1;j<o;j++)
            {
                int min1=(1<<30);
                int min2=(1<<30);
                for(int k=0;k<v;k++)
                {
                    int val=max(D[k][i],D[k][j]);
                    if(val<min1) {min2=min1;min1=val;}
                    else if(val<min2){min2=val;}
                }
                mini=min(mini,min2);
            }
        }
    }
    else
    {
       for(int i=0;i<v;i++)
        {
            for(int j=i+1;j<v;j++)
            {
                int min1=(1<<30);
                int min2=(1<<30);
                for(int k=0;k<o;k++)
                {
                    int val=max(D[i][k],D[j][k]);
                    if(val<min1) {min2=min1;min1=val;}
                    else if(val<min2){min2=val;}
                }
                mini=min(mini,min2);
            }
        }
    }
    fprintf(g,"%d",mini);
    fclose(f);
    fclose(g);
    return 0;
}
