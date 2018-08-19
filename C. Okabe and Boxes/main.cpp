#include <iostream>
#include <bitset>
#include <stack>
using namespace std;
bitset<300005> B;
int st[300005];
int N;
string a;
int val;
int u=1;
int rez;
void altii()
{
    cin>>N;
    stack<int> q;
    for(int i=1;i<=2*N;i++)
    {
        cin>>a;
        if(a=="add")
        {
            cin>>val;
            q.push(val);
        }
        else
        {
            if(!q.empty())
            {
                if(q.top()==u)
                {
                    q.pop();
                }
                else
                {
                    rez++;
                    while(!q.empty())
                        q.pop();
                }
            }
            u++;
        }
    }
}
void eu()
{
    cin>>N;
    for(int i=1;i<=2*N;i++)
    {
        cin>>a;
        if(a=="add")
        {
            cin>>val;
            st[++st[0]]=val;
        }
        else
        {
            if(st[st[0]]==u||(st[0]==0&&B[u]))
            {
                u++;
                if(st[0])st[0]--;
            }
            else
            {
                rez++;
                u++;
                for(int i=1;i<=st[0];i++)B[st[i]]=1;
                st[0]=0;
            }
        }
    }
}
int main()
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    altii();
    cout<<rez;
    return 0;
}
