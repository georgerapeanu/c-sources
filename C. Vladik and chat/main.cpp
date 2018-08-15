#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <cctype>
#include <stack>
using namespace std;
int T,N,nr,M;
unordered_map <string,int> m;
unordered_set <int> S[110];
string C[110],user;
int A[110];
int dp[110][110];
vector<string> names;
void read()
{
    cin>>N;
    m.clear();
    names.clear();
    for(int i=1;i<=N;i++)
    {
        cin>>user;
        m[user]=i;
        names.push_back(user);
    }
    cin>>M;getline(cin,C[0]);
    for(int i=0;i<M;i++)
    {
        S[i+1].clear();
        A[i+1]=0;
        getline(cin,C[i]);
        int j;
        if(C[i][0]=='?') A[i+1]=-1,j=2;
        else
        {
            user.clear();
            j=0;
            while(C[i][j]!=':')
            {
                user.push_back(C[i][j]);
                j++;
            }
            j++;
            A[i+1]=m[user];
        }
        string tmp=C[i].substr(j);
        C[i].assign(tmp,0,tmp.size());
        int len=C[i].size();
        user.clear();
        for(char c:C[i])
        {
            if(isalnum(c))
                user+=c;
            else
            {
                if(m.find(user)!=m.end()) S[i+1].insert(m[user]);
                user.clear();
            }
        }
        if(!user.empty())
        {
            if(m.find(user)!=m.end()) S[i+1].insert(m[user]);
                user.clear();
        }
    }
}
void solve()
{
    for(int i=0;i<=M;i++)
        for(int j=0;j<=N;j++)
            dp[i][j]=-1;
    dp[0][0]=0;
    for(int i=0;i<M;i++)
    {
        for(int j=min(1,i);j<=N;j++)
        {
            if(dp[i][j]>=0)
            {
                if(A[i+1]!=-1)
                   {if(j!=A[i+1])
                        dp[i+1][A[i+1]]=j;}
                else
                {
                    for(int k=1;k<=N;k++)
                    {
                        if(j!=k&&S[i+1].find(k)==S[i+1].end())
                            dp[i+1][k]=j;
                    }
                }
            }
        }
    }
}
void write()
{
    int ind=0;
    for(int i=1;i<=N&&!ind;i++)
        ind=i*(dp[M][i]!=-1);
    if(!ind)
        {cout<<"Impossible\n";return;}
    stack<int> st;
    int nvl=M;
    while(ind>0)
    {
        st.push(ind);
        ind=dp[nvl][ind];
        nvl--;
    }
    nvl=0;
    while(!st.empty())
    {
        cout<<names[st.top()-1]<<":"<<C[nvl]<<"\n";
        nvl++;
        st.pop();
    }
}
int main()
{
    cin>>T;
    while(T)
    {
        read();
        solve();
        write();
        T--;
    }
    return 0;
}
