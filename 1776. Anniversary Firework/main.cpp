#include <cstdio>
using namespace std;
int N;
double C[405][405],A[405][405];///C-probabilitatea ca timpul lansarii a i rachete sa fie cel mult j
///A-probabilitate ca timpul lansarii a i rachete sa fie exact j
int main()
{
    scanf("%d",&N);
    A[0][0]=A[1][0]=1.0;
    for(int i=0;i<=400;i++)
        C[1][i]=C[0][i]=1.0;
    for(int i=2;i<=N-2;i++)
    {
        for(int j=1;j<=401;j++)
        {
            for(int k=1;k<=i;k++)
            {
                A[i][j]+=(C[k-1][j-1]*A[i-k][j-1]+A[k-1][j-1]*C[i-k][j-1]-A[k-1][j-1]*A[i-k][j-1])/double(i);
            }
            C[i][j]=C[i][j-1]+A[i][j];
        }
    }
    double rez=0;
    for(int i=0;i<=400;i++)
        rez=rez+i*10.0*A[N-2][i];

    rez+=10.0;
    printf("%.12f",rez);
    return 0;
}

