#include <cstdio>
using namespace std;
FILE *g=fopen("hack.out","w");
const int dx[]={-1,0,1,0};
const int dy[]={0,1,0,-1};
int l=0;
int st=1;
char B[55][55];
int X,Y;
bool ok;
int main()
{
    X=25;Y=26;
    fprintf(g,"50 50 25 26\n");
    for(int i=1;i<=50;i++) for(int j=1;j<=50;j++) B[i][j]='0';
    while(1)
    {
        B[X][Y]='1';
        for(int i=1;i<=l;i++)
        {
            X+=dx[st];Y+=dy[st];
            if(X<=0||X>50||Y<=0||Y>50){ok=1;break;}
            B[X][Y]='1';
        }
        if(ok==1)
            break;
        l++;
        st=(st+1)%4;
    }
    for(int i=1;i<=50;i++)
    {
        fputs(B[i]+1,g);
        fputc('\n',g);
    }
    fclose(g);
    return 0;
}
