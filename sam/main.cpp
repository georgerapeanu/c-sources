#include <cstdio>
#include <fstream>
#define NMAX 100005
#define MOD 1000003
#define LEN 300000
#define mp make_pair
#define zeros(x) (x&(-x))
using namespace std;
FILE *f=fopen("sam.in","r");
FILE *g=fopen("sam.out","w");
int dp[2][NMAX];
int nr[2][NMAX];
int D[2][NMAX],NR[2][NMAX];
int N;
int sol=1,len;
void update(int poz,int j)
{
    for(int i=poz;i<=N;i+=zeros(i))
    {
        if(dp[j][i]<D[j][poz])
        {
            dp[j][i]=D[j][poz];nr[j][i]=NR[j][poz];
        }
        else if(dp[j][i]==D[j][poz])
        {
            nr[j][i]=(nr[j][i]+NR[j][poz])%MOD;
        }
    }
}
pair<int,int> q(int st,int dr,int j)
{
    int l=0,n=1;
    for(int i=dr;i>=st;)
    {
        if(i-zeros(i)+1>=st)
        {
            if(l<dp[j][i]){l=dp[j][i];n=nr[j][i];}
            else if(l==dp[j][i]){n=(n+nr[j][i])%MOD;}
            i-=zeros(i);
        }
        else
        {
            if(l<D[j][i]){l=D[j][i];n=NR[j][i];}
            else if(l==D[j][i]){n=(n+NR[j][i])%MOD;}
            i--;
        }
    }
    return mp(l+1,n);
}
int val;
int ind=LEN-1;
char buffer[LEN];
char getch()
{
    ind++;
    if(ind==LEN) {fread(buffer,LEN,1,f);ind=0;}
    return buffer[ind];
}
int i32()
{
    int rez=0;
    char c=getch();
    while(!isdigit(c))
        c=getch();
    while(isdigit(c))
    {
        rez=rez*10+c-'0';
        c=getch();
    }
    return rez;
}
int main()
{
    N=i32();
    int minim=NMAX,maxim=0;
    for(int i=1;i<=N;i++)
    {
        val=i32();maxim=max(maxim,val);minim=min(minim,val);
        pair<int,int> p1,p2;
        p1=q(minim,val,1);
        p2=q(val,maxim,0);
        D[0][val]=p1.first;NR[0][val]=p1.second;update(val,0);
        D[1][val]=p2.first;NR[1][val]=p2.second;update(val,1);
        if(len<D[0][val]||len<D[1][val]) sol=0;
        len=max(len,max(D[0][val],D[1][val]));
        sol=(sol+(len==D[0][val])*NR[0][val]+(len==D[1][val])*NR[1][val])%MOD;
    }
    fprintf(g,"%d",sol);
    fclose(f);
    fclose(g);
    return 0;
}
