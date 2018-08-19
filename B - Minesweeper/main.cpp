#include <iostream>
using namespace std;
int N,M;
string S[55];
string ans[55];
int d[]={-1,0,1};
int main()
{
    cin>>N>>M;
    for(int i=1;i<=N;i++)
    {
        cin>>S[i];
        S[i]=" "+S[i];
        ans[i].resize(M+1);
    }
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=M;j++)
        {
            if(S[i][j]=='#')
            {
                ans[i][j]='#';
            }
            else
            {
                ans[i][j]='0';
                for(int k=0;k<3;k++)
                {
                    for(int l=0;l<3;l++)
                    {
                        int x=i+d[k];
                        int y=j+d[l];
                        if(x&&y&&x<=N&&y<=M)
                        {
                            ans[i][j]+=(S[x][y]=='#');
                        }
                    }
                }
            }
        }
        cout<<ans[i].substr(1)<<"\n";
    }
    return 0;
}
