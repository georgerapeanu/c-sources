#include <cstdio>
#include <vector>
#include <bitset>
using namespace std;
FILE *f=fopen("zaharel.in","r");
FILE *g=fopen("zaharel.out","w");
int N,M,x,y;
char c;
int R[1005];
int B[1005];
int stpos;
vector<pair<int,int> > V;
int VB[1005],VR[1005];
bool rfst;
void solve(int x,int y,bool c,int pas)
{
    if(!c)
    {
        if(VR[x]){stpos=VR[x];rfst=1;return ;}
        else VR[x]=pas;
        V.push_back({x,y});
        solve(B[y],y,1,pas+1);
    }
    else
    {
        if(VB[y]){stpos=VB[y];return ;}
        else VB[y]=pas;
        V.push_back({x,y});
        solve(x,R[x],0,pas+1);
    }
}
int main()
{
    fscanf(f,"%d %d\n",&N,&M);
    for(int i=1;i<=M;i++)
    {
        fscanf(f,"%d %d %c\n",&x,&y,&c);
        if(c=='R')
        {
            R[x]=y;
        }
        else
        {
            B[y]=x;
        }
    }
    V.push_back({0,0});
    solve(1,R[1],0,1);
    fprintf(g,"%d\n",(V.size()-stpos+1)/2);
    if(rfst)
    {
        for(int i=stpos;i<V.size();i+=2)fprintf(g,"%d %d ",V[i].first,V[i].second);
        fputc('\n',g);
        for(int i=stpos+1;i<V.size();i+=2)fprintf(g,"%d %d ",V[i].first,V[i].second);
    }
    else
    {
        for(int i=stpos+1;i<V.size();i+=2)fprintf(g,"%d %d ",V[i].first,V[i].second);
        fputc('\n',g);
        for(int i=stpos;i<V.size();i+=2)fprintf(g,"%d %d ",V[i].first,V[i].second);
    }
    fclose(f);
    fclose(g);
    return 0;
}
