#include <cstdio>
#include <algorithm>
#define rad 100
using namespace std;
FILE *f=fopen("qxy.in","r");
FILE *g=fopen("qxy.out","w");
int N;
int M;
const int LEN=10000;
char buff[LEN];
int ind=LEN-1;
int V[10005];
int i32()
{
    while(buff[ind]<'0'||buff[ind]>'9'){
        if(++ind>=LEN){
            ind=0;
            fread(buff,1,LEN,f);
        }
    }
    int nr=0;
    while(buff[ind]>='0'&&buff[ind]<='9'){
        nr=nr*10+buff[ind]-'0';
        if(++ind>=LEN){
            ind=0;
            fread(buff,1,LEN,f);
        }
    }
    return nr;
}
int fr[rad+1][1005];
int main()
{
    N=i32();
    for(int i=1;i<=N;i++)
    {
        V[i]=i32();
        fr[i/rad][V[i]]++;
    }
    for(int i=1;i<=N/rad;i++)
    {
        for(int j=1;j<=1000;j++)
            fr[i][j]+=fr[i][j-1];
    }

    M=i32();
    while(M--)
    {
        int i,j,x,y;
        i=i32();j=i32();x=i32();y=i32();
        int rez=0;
        while(i<=j&&i%rad!=0)
        {
            rez+=(V[i]>=x&&V[i]<=y);
            i++;
        }
        while(i+rad<=j)
        {
            rez+=fr[i/rad][y]-(x==0? 0:fr[i/rad][x-1]);
            i+=rad;
        }
        while(i<=j)
        {
            rez+=(V[i]>=x&&V[i]<=y);
            i++;
        }
        fprintf(g,"%d\n",rez);
    }
    fclose(f);
    fclose(g);
    return 0;
}
