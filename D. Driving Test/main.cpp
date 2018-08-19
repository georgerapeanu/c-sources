#include <iostream>
#include <stack>
#define inf (1<<30)
using namespace std;
stack<int> S;
int N;
int T;
int s;
int rez;
int over;
int main()
{
    cin>>N;
    S.push(inf);
    for(int i=1;i<=N;i++)
    {
        while(s>S.top()){S.pop();rez++;}
        cin>>T;
        int x;
        if(T==1)
        {
            cin>>x;
            s=x;
        }
        else if(T==2)
        {
            rez+=over;
            over=0;
        }
        else if(T==3)
        {
            cin>>x;
            S.push(x);
        }
        else if(T==4)
        {
            over=0;
        }
        else if(T==5)
        {
            S.push(inf);
        }
        else
        {
            over++;
        }
    }
    while(s>S.top()){S.pop();rez++;}
    cout<<rez;
    return 0;
}
