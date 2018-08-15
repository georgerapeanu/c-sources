#include <iostream>
using namespace std;
int C[405][405];
int L[405][405];
int len[405];
int V[405];
int N,M,K,P;
int rez=0;
int main()
{
    cin>>N>>K>>P;
    for(int i=1;i<=N;i++)
    {
        int sum=-1;
        cin>>M;len[i]=M;
        for(int j=1;j<=M;j++)
        {
            cin>>V[j];
        }
        for(int j=1;j<M;j++)
        {
            sum=V[j];
            int k=j-1;
            C[i][j]=1<<30;
            while(k>=0&&sum<=P)
            {
                if(C[i][j]>C[i][k]+(P-sum)*(P-sum))
                {
                    C[i][j]=C[i][k]+(P-sum)*(P-sum);
                    L[i][j]=L[i][k]+1;
                }
                sum+=1+V[k];
                k--;
            }
        }
        int k=M-1;sum=V[M];C[i][M]=1<<30;
        while(k>=0&&sum<=P)
        {
            if(C[i][M]>C[i][k])
            {
                C[i][M]=C[i][k];
                L[i][M]=L[i][k]+1;
            }
            sum+=1+V[k];
            k--;
        }
        rez+=C[i][M];
    }
    int sum=-1;
    for(int i=1;i<=N;i++)
    {
        if(sum+L[i][len[i]]<K)sum+=L[i][len[i]]+1;
        else {rez+=K-sum;sum=L[i][len[i]];}
    }
    cout<<rez+K-sum;
    return 0;
}
