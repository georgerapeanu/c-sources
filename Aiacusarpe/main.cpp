#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f = fopen("aiacusarpe.in","r");
FILE *g = fopen("aiacusarpe.out","w");
int x = 1,y = 1,N,M;
int T;
char C[1000005];
int D[1005][1005];
int dx[280];
int dy[280];
int rez = 1,len = 1;
bool in(int x,int y){
    return x && y && x <= N && y <= M;
}
int main()
{
    dx['N'] = -1;dy['N'] = 0;
    dx['E'] = 0;dy['E'] = 1;
    dx['S'] = 1;dy['S'] = 0;
    dx['V'] = 0;dy['V'] = -1;
    fscanf(f,"%d %d %d\n",&N,&M,&T);
    fgets(C + 1,1000005,f);
    D[x][y] = 1;
    for(int i = 1;i <= T;i++){
        if(!in(x + dx[C[i]],y + dy[C[i]])){
            break;
        }
        x += dx[C[i]];
        y += dy[C[i]];
        if(D[x][y]){
            len = min(len,D[x - dx[C[i]]][y - dy[C[i]]] - D[x][y]);
        }
        D[x][y] = D[x - dx[C[i]]][y - dy[C[i]]] + 1;
        len++;
        rez = max(rez,len);
    }
    fprintf(g,"%d",rez);
    fclose(f);
    fclose(g);
    return 0;
}
