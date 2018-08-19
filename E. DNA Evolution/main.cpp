#include <iostream>

using namespace std;
int N;
int tip;
string s;
int x;
char c;
int l,r;
string e;
void u(int V[],int pos,int val)
{
    for(int i=pos;i<=s.size();i+=(-i)&i)
        V[i]+=val;
}
int q(int V[],int pos)
{
    int sum=0;
    for(int i=pos;i;i-=(-i)&i)
        sum+=V[i];
    return sum;
}
int AIB[5][11][11][100005];
int chartoint(char c)
{
    if(c=='A')return 1;
    if(c=='T')return 2;
    if(c=='G')return 3;
    return 4;
}
int main()
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    cin>>s;
    for(int i=1;i<=s.size();i++)
        for(int j=1;j<=10;j++)
            u(AIB[chartoint(s[i-1])][j][i%j],i,1);
    cin>>N;
    while(N--)
    {
        cin>>tip;
        if(tip==1)
        {
            cin>>x>>c;
            for(int j=1;j<=10;j++)u(AIB[chartoint(s[x-1])][j][x%j],x,-1);
            for(int j=1;j<=10;j++)u(AIB[chartoint(c)][j][x%j],x,1);
            s[x-1]=c;
        }
        else
        {
            cin>>l>>r>>e;
            int rez=0;
            for(int i=0;i<e.size();i++)
            {
                rez+=q(AIB[chartoint(e[i])][e.size()][(l%e.size()+i)%e.size()],r)-q(AIB[chartoint(e[i])][e.size()][(l%e.size()+i)%e.size()],l-1);
            }
            cout<<rez<<"\n";
        }
    }
    return 0;
}
