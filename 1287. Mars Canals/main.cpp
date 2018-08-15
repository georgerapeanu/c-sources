#include <iostream>

using namespace std;
int N,rezs,rezS;
int s[2][1405][4];
int S[2][1405][4];
string C;
int main()
{
    cin>>N;
    getline(cin,C);
    for(int i=1;i<=N;i++)
    {
        getline(cin,C);
        for(int j=0;j<N;j++)
        {
            if(C[j]=='S')
            {
                S[i%2][j][0]=S[1-i%2][j][0]+1;
                S[i%2][j][1]=S[i%2][j-1][1]+1;
                S[i%2][j][2]=S[1-i%2][j-1][2]+1;
                S[i%2][j][3]=S[1-i%2][j+1][3]+1;
                s[i%2][j][0]=s[i%2][j][1]=s[i%2][j][2]=s[i%2][j][3]=0;
            }
            else
            {
                s[i%2][j][0]=s[1-i%2][j][0]+1;
                s[i%2][j][1]=s[i%2][j-1][1]+1;
                s[i%2][j][2]=s[1-i%2][j-1][2]+1;
                s[i%2][j][3]=s[1-i%2][j+1][3]+1;
                S[i%2][j][0]=S[i%2][j][1]=S[i%2][j][2]=S[i%2][j][3]=0;
            }
            rezs=max(s[i%2][j][0],rezs);
            rezs=max(s[i%2][j][1],rezs);
            rezs=max(s[i%2][j][2],rezs);
            rezs=max(s[i%2][j][3],rezs);
            rezS=max(S[i%2][j][0],rezS);
            rezS=max(S[i%2][j][1],rezS);
            rezS=max(S[i%2][j][2],rezS);
            rezS=max(S[i%2][j][3],rezS);
        }
    }
    if(rezs<rezS)
        cout<<"S\n";
    else if(rezs>rezS)
        cout<<"s\n";
    else
        cout<<"?\n";
    cout<<max(rezS,rezs);
    return 0;
}
