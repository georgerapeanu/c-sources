#include <iostream>
#include <queue>
#include <stack>
using namespace std;
int V[15];
int rez=1<<30;
int N;
int nr1,nr2;
int pw[14];
int ant[5000000];
int mod[5000000];
int finst,st;
queue<int> Q;
stack<int> S;
int getpos(int nr,int i)
{
    return (nr/pw[i])%3;
}
int main()
{
    pw[0]=1;
    cin>>N;
    for(int i=1;i<=N;i++)
        pw[i]=pw[i-1]*3;
    for(int i=1;i<=N;i++)
    {
        cin>>V[i];
        if(V[i]==1)
        {
            nr1++;
            finst+=pw[nr1-1];
            st+=pw[i-1];
        }
        else if(V[i]==2)
        {
            nr2++;
            finst+=2*pw[N-nr2];
            st+=2*pw[i-1];
        }
    }
    ant[st]=-1;
    Q.push(st);
    while(!ant[finst])
    {
        st=Q.front();Q.pop();
        int newst;
        for(int i=0;i<N;i++)
        {
            if(getpos(st,i)==1)
            {
                if(i)
                {
                    if(!getpos(st,i-1))
                    {
                        newst=st-pw[i]+pw[i-1];
                        if(ant[newst])continue;
                        ant[newst]=st;
                        mod[newst]=i;
                        Q.push(newst);
                    }
                    else if(i>1&&!getpos(st,i-2))
                    {
                        newst=st-pw[i]+pw[i-2];
                        if(ant[newst])continue;
                        ant[newst]=st;
                        mod[newst]=i;
                        Q.push(newst);
                    }
                }
            }
            else if(getpos(st,i)==2)
            {
                if(i<N-1)
                {
                    if(!getpos(st,i+1))
                    {
                        newst=st-2*pw[i]+2*pw[i+1];
                        if(ant[newst])continue;
                        ant[newst]=st;
                        mod[newst]=i;
                        Q.push(newst);
                    }
                    else if(i<N-2&&!getpos(st,i+2))
                    {
                        newst=st-2*pw[i]+2*pw[i+2];
                        if(ant[newst])continue;
                        ant[newst]=st;
                        mod[newst]=i;
                        Q.push(newst);
                    }
                }
            }
        }
    }
    while(ant[finst]!=-1)
    {
        S.push(mod[finst]);
        finst=ant[finst];
    }
    cout<<S.size()<<"\n";
    while(!S.empty())
    {
        cout<<S.top()+1<<" ";
        S.pop();
    }
    return 0;
}
