#include <cstdio>
#include <unordered_map>
using namespace std;
FILE *f=fopen("patrate6.in","r");
FILE *g=fopen("patrate6.out","w");
unordered_map<int,int> M;
int N;
int val;
int maxim;
int main()
{
    fscanf(f,"%d",&N);
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d",&val);
        M[val]++;
        maxim=max(maxim,val);
        while(M[val]>=4)
        {
            maxim=max(maxim,val+1);
            M[val+1]++;
            M.erase(val);
            val++;
        }
    }
    if(M.size()>1||(*M.begin()).second>1)
        fprintf(g,"%d",maxim+1);
    else
        fprintf(g,"%d",maxim);
    fclose(f);
    fclose(g);
    return 0;
}
