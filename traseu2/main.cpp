#include <cstdio>
#include <cstring>
#include <map>
using namespace std;
FILE *f=fopen("traseu2.in","r"),*g=fopen("traseu2.out","w");
int n;
char c[260];
bool obst[105][105];
int i,j,x,y,N,lg;
map <char,pair<int,int> > sens;
int main(){
    sens['N']=pair<int,int>(-1,0);
    sens['E']=pair<int,int>(0,1);
    sens['S']=pair<int,int>(1,0);
    sens['V']=pair<int,int>(0,-1);
    fscanf(f,"%d%d%d",&N,&x,&y);
    for(i=1;i<=N;i++)
        for(j=1;j<=N;j++)
            fscanf(f,"%d",&obst[i][j]);
    fscanf(f,"%c");
    fgets(c,260,f);
    lg=strlen(c);
    for(i=0;i<lg;i++)
    {
        if(obst[sens[c[i]].first+x][sens[c[i]].second+y]==0)
        {
            if(x+sens[c[i]].first<=N&&x+sens[c[i]].first>=1&&y+sens[c[i]].second<=N&&y+sens[c[i]].second>=1)
            {
                x+=sens[c[i]].first;
                y+=sens[c[i]].second;
            }
            else
            i=lg;
        }
    }
    fprintf(g,"%d %d",x,y);
    fclose(f);
    fclose(g);
    return 0;
}
