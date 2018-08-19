#include <cstdio>
using namespace std;
FILE *f=fopen("cocochanel.in","r");
FILE *g=fopen("cocochanel.out","w");
int C[100005];
int G,maxi;
int N,M;
const int LEN=10000000;
int ind=LEN-1;
char buff[LEN];
int i32()
{
    int nr=0;
    while('0'>buff[ind]||'9'<buff[ind]){
        if(++ind>=LEN){
            fread(buff,1,LEN,f);
            ind=0;
        }
    }
    while('0'<=buff[ind]&&'9'>=buff[ind]){
        nr=nr*10+buff[ind]-'0';
        if(++ind>=LEN){
            fread(buff,1,LEN,f);
            ind=0;
        }
    }
    return nr;
}
int main()
{
    N=i32();M=i32();
    for(int i=1;i<=N;i++)C[i]=i32();
    for(int i=1;i<=M;i++){G=i32();if(G>maxi)maxi=G;}
    for(int i=1;i<=N;i++)
    {
        int nr=maxi/C[i],rez=0;
        while(nr)
        {
            rez++;
            nr>>=1;
        }
        fprintf(g,"%d\n",(rez<=M ? rez:M));
    }
    fclose(f);
    fclose(g);
    return 0;
}
