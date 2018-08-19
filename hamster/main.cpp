#include <cstdio>
#include <algorithm>
#include <ctype.h>
#define LEN 1000000
using namespace std;
/** Funcţiile necesare parsării fişierului de intrare **/
FILE *_fin;
int _in_loc; char _in_buff[LEN];


void read_init(const char* nume) // Apelaţi această funcţie la începutul funcţiei <main>
{
    _fin = fopen(nume, "r");
    _in_loc = LEN-1;
}

char read_ch()
{
    ++_in_loc;
    if (_in_loc == LEN) {
        _in_loc = 0;
        fread(_in_buff, 1, LEN, _fin);
    }
    return _in_buff[_in_loc];
}

int read_u32() // Apelaţi această funcţie pentru a citi un număr ce se încadrează în categoria <unsigned int>
{
    int u32 = 0; char c;
    while (!isdigit(c = read_ch()) && c != '-');
    int sgn = 1;
    if (c == '-') {
        sgn = -1;
    } else {
        u32 = c - '0';
    }
    while (isdigit(c = read_ch())) {
        u32 = u32 * 10 + c - '0';
    }
    return u32 * sgn;
}

long long read_u64() // Apelaţi această funcţie pentru a citi un număr ce se încadrează în categoria <unsigned long long>
{
    long long u64 = 0; char c;
    while (!isdigit(c = read_ch()) && c != '-');
    long long sgn = 1;
    if (c == '-') {
        sgn = -1;
    } else {
        u64 = c - '0';
    }
    while (isdigit(c = read_ch())) {
        u64 = u64 * 10 + c - '0';
    }
    return u64 * sgn;
}
FILE *g=fopen("hamster.out","w");
int N,Q;
long long DP[3005][3005];
long long V[3005];
int D[3005];
int stq,drq;
int main()
{
    read_init("hamster.in");
    N=read_u32();Q=read_u32();
    for(int i=1;i<=N;i++)
    {
        V[i]=read_u64();
    }
    for(int i=2;i<=N;i++)
        DP[i][1]=DP[i-1][1]+V[i]-V[i-1];
    DP[1][1]=1;
    for(int j=2;j<=N;j++)
    {
        int k=j-2;
        stq=1;drq=0;
        D[++drq]=j-1;
        for(int i=j;i<=N;i++)
        {
            DP[i][j]=1LL<<62;
            while(k<i-1&&V[i]-V[k+2]>=DP[k+1][j-1]) k++;
            while(stq<=drq&&D[stq]<=k)stq++;
            if(k>j-2) DP[i][j]=V[i]-V[k+1];
            if(stq<=drq) DP[i][j]=min(DP[i][j],DP[D[stq]][j-1]);
            while(stq<=drq&&DP[i][j-1]<DP[D[drq]][j-1]) drq--;
            D[++drq]=i;
        }
    }
    for(int i=1;i<=Q;i++)
    {
        long long D;
        int K;
        K=read_u32();D=read_u64();
        int st=1,dr=K;
        while(st<dr)
        {
            int mid=(st+dr)/2;
            if(DP[K][mid]>D)
                st=mid+1;
            else
                dr=mid;
        }
        fprintf(g,"%d\n",st);
    }
    fclose(g);
    return 0;
}
