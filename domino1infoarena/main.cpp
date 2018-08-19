#include <cstdio>
#include <iostream>
#define x first
#define y second
using namespace std;
pair<int,int> st[10005],nr;
bool rotit[10005];
int N,R,E,lst,BR,BE,Blst;
bool inserare(int ro)
{
    while(E&&lst&&nr>st[lst])
    {
        R+=rotit[lst];
        E--;
        lst--;
    }
    if(!ro||R>0)
    {
        lst=lst+1;
        st[lst]=nr;
        rotit[lst]=ro;
        Blst=lst;
        while(lst&&st[lst-1]==st[lst]&&rotit[lst]==0&&rotit[lst-1]==1)
        {
            swap(rotit[lst],rotit[lst-1]);
            lst--;
        }
        lst=Blst;
        return 1;
    }
    return 0;
}
int main()
{
    freopen("domino.in","r",stdin);
    freopen("domino.out","w",stdout);
    cin>>N>>R>>E;
    for(int i=1;i<=N;i++)
    {
        cin>>nr.x>>nr.y;
        BR=R;
        BE=E;
        Blst=lst;
        if(nr.x<nr.y)
        {
            swap(nr.x,nr.y);
            if(inserare(1))
            {
                R--;
                continue;
            }
            lst=Blst;
            E=BE;
            R=BR;
            swap(nr.x,nr.y);
            inserare(0);
        }
        else
        {
            inserare(0);
        }
    }
    lst-=E;
    for(int i=1;i<=lst;i++)
        cout<<st[i].x<<st[i].y;
    return 0;
}
