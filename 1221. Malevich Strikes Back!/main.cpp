#include <iostream>
#define NMAX 105
using namespace std;
int N;
int S[NMAX][NMAX];
int M[NMAX][NMAX],rez;
int main()
{   while(1)
    {
        rez=1;
        cin>>N;
        if(!N)
            break;
        for(int i=1;i<=N;i++)
        {
            for(int j=1;j<=N;j++)
            {
                cin>>M[i][j];
                M[i][j]+=M[i-1][j]+M[i][j-1]-M[i-1][j-1];
            }
        }
        for(int i=1;i<=N;i++)
        {
            for(int j=1;j<=N;j++)
            {
                if(M[i][j]-M[i-1][j]-M[i][j-1]+M[i-1][j-1]==0)
                {
                    S[i][j]=min(min(S[i-2][j],S[i-1][j-1]),min(S[i-1][j+1],S[i-1][j]))+1;
                    int x1,x2,y1,y2;
                    x1=i-2*S[i][j]+2;
                    y1=j-S[i][j]+1;
                    x2=i;
                    y2=j+S[i][j]-1;
                    if(M[x2][y2]-M[x1-1][y2]-M[x2][y1-1]+M[x1-1][y1-1]==2*(S[i][j]-1)*S[i][j])
                        if(rez<2*S[i][j]-1)
                            rez=2*S[i][j]-1;
                }
            }
        }
        if(rez==1)
            cout<<"No solution";
        else
            cout<<rez;
        cout<<"\n";
    }
    return 0;
}
