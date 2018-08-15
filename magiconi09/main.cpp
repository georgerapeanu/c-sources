#include <cstdio>
#include <cstdlib>
#include <deque>
#define x first
#define y second
using namespace std;
FILE *f=fopen("magic.in","r");
FILE *g=fopen("magic.out","w");
int N;
int c,nr;
deque <int> S;
char C[55];
char V[6][6];
pair<int,int> ord[55];
int v,o,rez;
void btr(int pas,int nr)
{
    int tmp=nr;
    if(pas%N==1&&pas!=1)
    {
        if(!S.empty()&&S.back()>=nr) return;
        tmp=0;
        S.push_back(nr);
    }
    if(pas>2*N*N)
    {
        rez++;
        if(c==2)
        {
            fputs(C+1,g);
            exit(0);
        }
        S.pop_back();
        return ;
    }
    if(V[ord[pas].x][ord[pas].y]!='\0')
    {
        C[pas]=V[ord[pas].x][ord[pas].y];
        btr(pas+1,tmp*10+V[ord[pas].x][ord[pas].y]-'0');
    }
    else
    {
        V[ord[pas].x][ord[pas].y]=C[pas]='1';
        btr(pas+1,tmp*10+1);
        V[ord[pas].x][ord[pas].y]=C[pas]='9';
        btr(pas+1,tmp*10+9);
        V[ord[pas].x][ord[pas].y]=C[pas]='\0';
    }
    if(!tmp) S.pop_back();
}
int main()
{
    fscanf(f,"%d%d",&c,&N);
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d",&o);
        for(int j=N*(o-1)+1;j<=o*N;j++)
        {
            ord[j]=make_pair(i,j-N*(o-1));
        }
    }
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d",&v);
        for(int j=N*(v-1)+1;j<=v*N;j++)
        {
            ord[j]=make_pair(j-N*(v-1),i);
        }
    }
    btr(1,0);
    fprintf(g,"%d",rez);
    fclose(f);
    fclose(g);
    return 0;
}
