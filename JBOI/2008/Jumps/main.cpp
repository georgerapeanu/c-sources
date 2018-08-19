#include <iostream>
#define MOD 1000000
using namespace std;
struct matrix{
    int n,m;
    int a[9][9];
    matrix operator *(matrix b)
    {
        matrix rez;
        rez.n=n;
        rez.m=b.m;
        for(int i=0;i<9;i++)for(int j=0;j<9;j++)rez.a[i][j]=0;
        for(int i=0;i<n;i++)
            for(int j=0;j<b.m;j++)
                for(int k=0;k<m;k++)
                    rez.a[i][j]=(rez.a[i][j]+1LL*a[i][k]*b.a[k][j])%MOD;
        return rez;
    }
};
matrix lgpow(matrix b,int e)
{
    matrix p;
    p.n=p.m=9;
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
            p.a[i][j]=(i==j);
    while(e)
    {
        if(e&1)p=p*b;
        b=b*b;
        e>>=1;
    }
    return p;
}
int N;
matrix b;
matrix p;
int main()
{
    cin>>N;
    if(N<4){cout<<N;return 0;}
    b.n=b.m=9;
    b.a[0][3]=1;
    b.a[1][4]=1;
    b.a[2][5]=1;
    b.a[3][6]=1;
    b.a[4][7]=1;
    b.a[5][8]=1;
    b.a[6][8]=1;b.a[6][7]=1;b.a[6][6]=1;
    b.a[7][5]=1;b.a[7][4]=1;
    b.a[8][2]=1;
    b=lgpow(b,N-3);
    p.n=9;p.m=1;p.a[0][0]=1;p.a[3][0]=1;p.a[4][0]=1;p.a[6][0]=2;p.a[7][0]=0;p.a[8][0]=1;
    p=b*p;
    cout<<(p.a[6][0]+p.a[7][0]+p.a[8][0])%MOD;
    return 0;
}
