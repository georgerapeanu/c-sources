#include <cstdio>
#include <cstring>
using namespace std;
FILE *f=fopen("doi.in","r");
FILE *g=fopen("doi.out","w");
int N[2005];
char C[505];
int A[505];
int T;
int nr;
void scade()
{
    N[1]--;
    int i=1;
    while(N[i]<0&&i<N[0])
    {
        N[i+1]--;
        N[i]+=2;
        i++;
    }
    while(N[0]>1&&N[N[0]]==0) N[0]--;
}
void aduna()
{
    N[1]++;
    int i=1;
    while(N[i]>1)
    {
        N[i]-=2;
        N[i+1]++;
        i++;
        if(i>N[0])
            N[0]=i;
    }
}
void imparte()
{
    for(int i=1;i<N[0];i++)
        N[i]=N[i+1];
    N[N[0]]=0;
    N[0]--;
}
bool par()
{
    return (N[1]==0);
}
bool zero(int N[])
{
    return (N[0]==1&&N[1]==0);
}
void imp()
{
    for(int i=A[0];i;i--)
    {
        if(A[i]%2==1) A[i-1]+=10;
        A[i]/=2;
    }
    while(A[0]>1&&A[A[0]]==0) A[0]--;
}
int main()
{
    fscanf(f,"%d\n",&T);
    while(T--)
    {
        fgets(C+1,505,f);
        A[0]=strlen(C+1);A[0]-=(C[A[0]]=='\n');
        for(int i=1;i<=A[0];i++) A[i]=C[A[0]-i+1]-'0';
        N[0]=0;nr=0;
        while(!zero(A))
        {
            N[++N[0]]=(A[1]%2);
            imp();
        }
        while(!zero(N))
        {
            if(!par())
            {
                if(N[0]!=1&&N[1]==1&&N[2]==1&&(!(N[0]==2&&N[1]==1&&N[2]==1)))
                    aduna();
                else
                    scade();
                nr++;
            }
            if(zero(N)) break;
            imparte();
            nr++;
        }
        fprintf(g,"%d\n",nr);
    }
    fclose(f);
    fclose(g);
    return 0;
}
