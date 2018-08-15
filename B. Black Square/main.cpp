#include <iostream>

using namespace std;
int N,M,rez=1<<30;
string a;
int S[105][105];
int nr;
int main()
{
    cin>>N>>M;
    for(int i=1;i<=N;i++)
    {
        cin>>a;
        for(int j=1;j<=M;j++)
        {
            S[i][j]=S[i-1][j]+S[i][j-1]-S[i-1][j-1]+(a[j-1]=='B');
            nr+=(a[j-1]=='B');
        }
    }
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=M;j++)
        {
            for(int l=0;i+l<=N&&j+l<=M;l++)
            {
                if(S[i+l][j+l]-S[i-1][j+l]-S[i+l][j-1]+S[i-1][j-1]==nr)
                {
                    rez=min(rez,(l+1)*(l+1)-nr);
                }
            }
        }
    }
    cout<<(rez==1<<30 ? -1:rez);
    return 0;
}
