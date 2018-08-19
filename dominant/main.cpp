#include <cstdio>
#include <iostream>
#include <cstring>
#include <unordered_map>
using namespace std;
FILE *f=fopen("dominant.in","r");
FILE *g=fopen("dominant.out","w");
int c,val;
char S[300005];
int N,rez,nr;
unordered_map <int,int> M;
int main()
{
    fscanf(f,"%d\n",&c);
    fgets(S+1,300005,f);
    N=strlen(S+1);
    M[0]=0;
    for(int i=1;i<=N;i++)
    {
        val+=(S[i]=='1' ? 1:-1);
        if(M.find(val)==M.end())
        {
            M[val]=i;
        }
        if(M.find(val-1)!=M.end())
        {
            if(rez<i-M[val-1])
            {
                rez=i-M[val-1];
                nr=1;
            }
            else if(rez==i-M[val-1])
                nr++;
        }
    }
    if(c==1)
        fprintf(g,"%d",rez);
    else
        fprintf(g,"%d",nr);
    fclose(f);
    fclose(g);
    return 0;
}
