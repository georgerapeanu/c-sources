#include <cstdio>
using namespace std;
FILE *f=fopen("cpr.in","r");
FILE *g=fopen("cpr.out","w");
int N;
bool ok;
int st,dr;
int main()
{
    fscanf(f,"%d",&N);
    if(N<=4)
    {
        if(N==4) fprintf(g,"3\n3 3 0\n2 2 3\n4 4 0");
        if(N==3) fprintf(g,"2\n3 3 0\n2 2 3");
        if(N==2) fprintf(g,"1\n2 2 0");
        if(N==1) fprintf(g,"0");
        return 0;
    }
    ok=(N%2!=1);
    N-=ok;
    fprintf(g,"%d\n",2+(N-4+1)/2+ok);
    fprintf(g,"%d %d %d\n",(N+1)/2,N-1,0);
    fprintf(g,"%d %d %d\n",2,N,N-2);
    st=2;dr=N-2;
    while(st<dr){fprintf(g,"%d %d %d\n",dr,st,dr+1);dr--;st++;}
    if(ok)fprintf(g,"%d %d %d\n",N+1,N+1,0);
    fclose(f);
    fclose(g);
    return 0;
}
