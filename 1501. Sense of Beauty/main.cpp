#include <iostream>
#include <algorithm>
using namespace std;
int ant[1005][1005];
int N,nrA[1005],nrB[1005];
char A[1005],B[1005];
bool btr(int c1,int c2,int r,int n)
{
   if(r-n<-1||r-n>1)
        return 0;
    if(!c1&&!c2)
    {
        return 1;
    }
    else if(!c1)
    {
        if(btr(c1,c2-1,r+(B[c2]=='0'),n+(B[c2]=='1')))
        {
            ant[c1][c2]=2;
            return 1;
        }
    }
    else if(!c2)
    {
        if(btr(c1-1,c2,r+(A[c1]=='0'),n+(A[c1]=='1')))
        {
            ant[c1][c2]=1;
            return 1;
        }
    }
    else
    {
        if(btr(c1-1,c2,r+(A[c1]=='0'),n+(A[c1]=='1')))
        {
            ant[c1][c2]=1;
            return 1;
        }
        if(btr(c1,c2-1,r+(B[c2]=='0'),n+(B[c2]=='1')))
        {
            ant[c1][c2]=2;
            return 1;
        }
    }
    return 0;
}
int main()
{
    cin>>N;
    cin.getline(A,1005);
    A[0]='\0';
    cin.getline(A+1,1005);
    cin.getline(B+1,1005);
    reverse(A+1,A+1+N);
    reverse(B+1,B+1+N);
    for(int i=1;i<=N;i++)
    {
        nrA[i]=nrA[i-1]+(A[i]=='1' ? 1:-1);
        nrB[i]=nrB[i-1]+(B[i]=='1' ? 1:-1);
    }
    ///btr(N,N,0,0);
    for(int i=0;i<=N;i++)
    {
        for(int j=0;j<=N;j++)
        {
            if(!i&&!j)
                ant[i][j]=1;
            else if(abs(nrA[N]-nrA[i]+nrB[N]-nrB[j])>1)
                ;
            else if(!i)
            {
                if(ant[i][j-1])
                    ant[i][j]=2;
            }
            else if(!j)
            {
                if(ant[i-1][j])
                    ant[i][j]=1;
            }
            else
            {
                if(ant[i-1][j])
                    ant[i][j]=1;
                else if(ant[i][j-1])
                    ant[i][j]=2;
            }
        }
    }
    if(!ant[N][N])
    {
        cout<<"Impossible";
        return 0;
    }
    int i=N,j=N;
    while(i||j)
    {
        cout<<ant[i][j];
        if(ant[i][j]==1)
            i--;
        else
            j--;
    }
    return 0;
}
