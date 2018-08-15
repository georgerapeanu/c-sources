#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("blaturi.in","r");
FILE *g=fopen("blaturi.out","w");
int S[100005];
int N;
int P1,P2,S1,S2;
int rez=(1<<30);
int main()
{
    fscanf(f,"%d",&N);
    for(int i=1;i<=N;i++)
    {fscanf(f,"%d",&S[i]);S[i]+=S[i-1];}
    fscanf(f,"%d%d",&P1,&S1);
    fscanf(f,"%d%d",&P2,&S2);
    for(int i=0;i<=N;i++)
    {
        int cost=S[i]*P1+(S[N]-S[i])*P2;
        if(i>N-i)
        {
            cost+=S1*(2*i-N+-1);
        }
        else if(i==N-i)
        {
            ;
        }
        else
        {
            cost+=S2*(N-2*i-1);
        }
        rez=min(rez,cost);
    }
    fprintf(g,"%d",rez);
    fclose(f);
    fclose(g);
    return 0;
}
