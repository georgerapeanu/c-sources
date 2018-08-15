#include <iostream>
#include <vector>
#include <map>
using namespace std;
map<string,vector<string> > M;
map<string,int> V;
int t;
int N,Q,Nr;
string a,b,c;
string ceva[1605];
int main()
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    cin>>t;
    for(int i=1;i<=t;i++)
    {
        cin>>a>>Nr;
        for(int j=1;j<=Nr;j++)
        {
            cin>>b>>c;
            M[a].push_back(c);
            int nr=0;
            for(int i=0;i<b.size();i++)
                if(b[i]=='.')
                    nr^=1<<i;
            V[c]=nr;
        }
    }
    cin>>Q;
    for(int i=1;i<=Q;i++)
    {
        cin>>N;
        int nr=(1<<24)-1;
        for(int j=1;j<=N;j++)
        {
            cin>>ceva[j];
            int tmp=0;
            for(auto it:M[ceva[j]])
                tmp|=V[it];
            nr&=tmp;
        }
        if(nr==0)cout<<"No\n";
        else
        {
            cout<<"Yes";
            int ora=0;
            while(!((nr>>ora)&1))ora++;
            for(int j=1;j<=N;j++)
            {
                for(auto it:M[ceva[j]])
                {
                    if((V[it]>>ora)&1)
                    {
                        cout<<" "<<it;
                        break;
                    }
                }
            }
            cout<<"\n";
        }
    }
    return 0;
}
