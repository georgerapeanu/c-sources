#include <cstdio>
#include <set>
#define mp make_pair
#define x first
#define y second
using namespace std;
FILE *f=fopen("memcpy.in","r");
FILE *g=fopen("memcpy.out","w");
short N,M,X,Y,NX,NY;
set<pair<short,short> > S;
bool in(short x,short y,short stx,short sty,short drx,short dry)
{
    return (stx<=x&&x<=drx&&sty<=y&&y<=dry);
}
int main()
{
    fscanf(f,"%hd%hd%hd%hd%hd%hd",&N,&M,&X,&Y,&NX,&NY);
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=M;j++)
        {
            if(in(NX+i-1,NY+j-1,X,Y,X+N-1,Y+M-1))
                ;
            else
                S.insert(mp(X+i-1,Y+j-1));
        }
    }
    int hash = 0, mod = 1e9 + 7;
    for(int i=1;i<=N*M;i++)
    {
        pair<short,short> raspuns=(*S.begin());
        S.erase(S.begin());
        hash = (1LL * i * raspuns.x * raspuns.y+hash) % mod;
        if(in(raspuns.x,raspuns.y,NX,NY,NX+N-1,NY+M-1))
        {
            pair<short,short> tmp=raspuns;
            tmp.x=(tmp.x-NX+X);
            tmp.y=(tmp.y-NY+Y);
            S.insert(tmp);
        }
    }
    fprintf(g,"%d",hash);
    fclose(f);
    fclose(g);
    return 0;
}
