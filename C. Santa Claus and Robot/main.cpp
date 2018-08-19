#include <cstdio>
#include <cmath>
#include <unordered_map>
#define NMAX 200005
using namespace std;
int rez=1;
int x,y;
int nx,ny;
int d;
int N;
unordered_map <char,pair<int,int> > moves;
char C[NMAX];
int main()
{
    moves['L']=make_pair(0,-1);
    moves['U']=make_pair(1,0);
    moves['R']=make_pair(0,1);
    moves['D']=make_pair(-1,0);
    scanf("%d\n",&N);
    gets(C+1);
    for(int i=1;i<=N;i++)
    {
        nx+=moves[C[i]].first;
        ny+=moves[C[i]].second;
        d++;
        if(abs(nx-x)+abs(ny-y)!=d)
        {
            rez++;
            d=1;
            x=nx-moves[C[i]].first;
            y=ny-moves[C[i]].second;
        }
    }
    printf("%d",rez);
    return 0;
}
