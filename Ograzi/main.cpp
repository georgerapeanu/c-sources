#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
FILE *f=fopen("ograzi.in","r");
FILE *g=fopen("ograzi.out","w");
const int MOD=30103;
vector<pair<int,int> > HA[MOD];
int N,M,H,W,rez;
const int LEN=10000;
char buff[LEN];
int ind=LEN-1;
bool ok;
int i32()
{
    int rez=0;
    while(buff[ind]<'0'||buff[ind]>'9')
    {
        if(++ind>=LEN)
        {
            ind=0;
            fread(buff,1,LEN,f);
        }
    }
    while(buff[ind]>='0'&&buff[ind]<='9')
    {
        rez=rez*10+buff[ind]-'0';
        if(++ind>=LEN)
        {
            ind=0;
            fread(buff,1,LEN,f);
        }
    }
    return rez;
}
int hval(int x,int y)
{
    return (x*1013+y)%MOD;
}
int main()
{
    N=i32();M=i32();H=i32();W=i32();
    for(int i=1;i<=N;i++)
    {
        int x,y;
        x=i32();y=i32();
        HA[hval(x/H,y/W)].push_back({x,y});
    }
    for(int i=1;i<=M;i++)
    {
        int x,y;
        x=i32();y=i32();
        bool ok=0;
        for(auto it:HA[hval(x/H,y/W)])
        {
            if(ok)break;
            ok|=(it.first<=x&&x<=it.first+H&&it.second<=y&&y<=it.second+W);
        }
        if(x/H)for(auto it:HA[hval(x/H-1,y/W)])
        {
            if(ok)break;
            ok|=(it.first<=x&&x<=it.first+H&&it.second<=y&&y<=it.second+W);
        }
        if(y/W)for(auto it:HA[hval(x/H,y/W-1)])
        {
            if(ok)break;
            ok|=(it.first<=x&&x<=it.first+H&&it.second<=y&&y<=it.second+W);
        }
        if(x/H&&y/W)for(auto it:HA[hval(x/H-1,y/W-1)])
        {
            if(ok)break;
            ok|=(it.first<=x&&x<=it.first+H&&it.second<=y&&y<=it.second+W);
        }
        rez+=ok;
    }
    fprintf(g,"%d",rez);
    fclose(f);
    fclose(g);
    return 0;
}
