#include <cstdio>
using namespace std;
FILE *f=fopen("zar.in","r");
FILE *g=fopen("zar.out","w");
int V[7];
int S[7];
int rez[1005],i;
char C[1005];
int N,l,c,M;
void up()
{
    int tmp;
    tmp=V[1];
    V[1]=V[5];
    V[5]=V[2];
    V[2]=V[6];
    V[6]=tmp;
}
void down()
{
    int tmp=V[6];
    V[6]=V[2];
    V[2]=V[5];
    V[5]=V[1];
    V[1]=tmp;
}
void left()
{
    int tmp=V[1];
    V[1]=V[4];
    V[4]=V[2];
    V[2]=V[3];
    V[3]=tmp;
}
void right()
{
    int tmp=V[1];
    V[1]=V[3];
    V[3]=V[2];
    V[2]=V[4];
    V[4]=tmp;
}
int main()
{
    fscanf(f,"%d\n%d %d\n",&N,&l,&c);
    for(i=1;i<=6;i++)
        {fscanf(f,"%d",&V[i]);S[i]=V[i];}
    fscanf(f,"%d\n",&M);
    fgets(C+1,1005,f);
    i=1;
    rez[++rez[0]]=V[1];
    while(i<=M&&l>0&&l<=N&&c>0&&c<=N)
    {
        switch(C[i])
        {
            case 'u':up();l--;if(!(l>0&&l<=N&&c>0&&c<=N))break;S[1]+=V[1];S[2]+=V[2];S[3]+=V[3];S[4]+=V[4];S[5]+=V[5];S[6]+=V[6];rez[++rez[0]]=V[1];break;
            case 'd':down();l++;if(!(l>0&&l<=N&&c>0&&c<=N))break;S[1]+=V[1];S[2]+=V[2];S[3]+=V[3];S[4]+=V[4];S[5]+=V[5];S[6]+=V[6];rez[++rez[0]]=V[1];break;
            case 'l':left();c--;if(!(l>0&&l<=N&&c>0&&c<=N))break;S[1]+=V[1];S[2]+=V[2];S[3]+=V[3];S[4]+=V[4];S[5]+=V[5];S[6]+=V[6];rez[++rez[0]]=V[1];break;
            case 'r':right();c++;if(!(l>0&&l<=N&&c>0&&c<=N))break;S[1]+=V[1];S[2]+=V[2];S[3]+=V[3];S[4]+=V[4];S[5]+=V[5];S[6]+=V[6];rez[++rez[0]]=V[1];break;

        }
        i++;
    }
    for(i=1;i<=6;i++)
        fprintf(g,"%d ",S[i]);
    fprintf(g,"\n");
    for(i=1;i<=rez[0];i++)
        fprintf(g,"%d ",rez[i]);
    fclose(f);
    fclose(g);
    return 0;
}
