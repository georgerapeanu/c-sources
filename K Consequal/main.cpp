#include <iostream>
#include <stack>
using namespace std;
stack <pair<char,int>> s;
stack <char> rez;
pair <char,int> aux;
int N,K;
char C[100005];
int main()
{
    cin>>N>>K;
    cin.getline(C,100005);
    cin.getline(C+1,100005);
    for(int i=1;i<=N;i++)
    {
        if(s.empty())
        {
            s.push(make_pair(C[i],1));
        }
        else if((s.top()).first==C[i])
        {
            (s.top()).second++;
        }
        else
        {
            if((s.top()).second>=K)
                (s.top()).second%=K;
            if(!(s.top()).second)
                s.pop();
            if(!s.empty()&&(s.top()).first==C[i])
            {
                (s.top()).second++;
            }
            else
                s.push(make_pair(C[i],1));
        }
    }
    while(!s.empty()&&s.top().second>=K)
    {
        if((s.top()).second>=K)
                (s.top()).second%=K;
        if(!(s.top()).second)
                s.pop();
    }
    while(!s.empty())
    {
        while((s.top()).second)
        {
            (s.top()).second--;
            rez.push((s.top()).first);
        }
        s.pop();
    }
    while(!rez.empty())
    {
        cout<<rez.top();
        rez.pop();
    }
    return 0;
}
