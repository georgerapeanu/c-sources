#include <cstdio>
#include <vector>
#define NMAX 110
using namespace std;
FILE *f=fopen("seif1.in","r");
FILE *g=fopen("seif1.out","w");
int N,K,i,j,M[NMAX][NMAX];
pair <int,int> sens;
vector <int> rez;
int main(){
    fscanf(f,"%d %d",&N,&K);
    K%=2*N;
    for(i=1;i<=N;i++)
        for(j=1;j<=N;j++)
            fscanf(f,"%d",&M[i][j]);
    i=1;
    j=N/2;
    sens=pair<int,int>(1,-1);
    while(i!=1||j!=N/2+1){
        rez.push_back(M[i][j]);
        if(i==N/2&&j==1)
        {
            sens=pair<int,int>(1,1);
            i++;
        }
        else if(i==N&&j==N/2)
        {
            sens=pair<int,int>(-1,1);
            j++;
        }
        else if(i==N/2+1&&j==N)
        {
            sens=pair<int,int>(-1,-1);
            i--;
        }
        else
        {
            i+=sens.first;
            j+=sens.second;
        }
    }
    rez.push_back(M[i][j]);
    for(i=0;i<2*N;i++)
    {
        rez.push_back(rez[i]);
    }
    for(i=K;i<2*N+K;i++)
    {
        fprintf(g,"%d ",rez[i]);
    }
    fclose(f);
    fclose(g);
    return 0;
}
