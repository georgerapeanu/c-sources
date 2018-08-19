#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
FILE *E=fopen("ev","w");
int V[1000];
int N,M;
char C;
int x,y,sz;
void rev(int x,int y)
{
    if(x>=y)return ;
    swap(V[x],V[y]);
    rev(x+1,y-1);
}
int main()
{
    freopen("secv8.in","r",stdin);
    freopen("secv8.ok","w",stdout);
    cin>>N>>M;
    for(int i=1;i<=N;i++)
    {
        cin>>C;
        if(C=='I')
        {
            cin>>x>>y;
            sz++;
            for(int i=sz;i>x;i--)V[i]=V[i-1];
            V[x]=y;
        }
        else if(C=='A')
        {
            cin>>x;
            cout<<V[x]<<"\n";
        }
        else if(C=='R')
        {
            cin>>x>>y;
            rev(x,y);
        }
        else
        {
            cin>>x>>y;
            sz-=(y-x+1);
            for(int i=x;i<=sz;i++)
                V[i]=V[y+(i-x)+1];
        }
        for(int i=1;i<=sz;i++)
            fprintf(E,"%d ",V[i]);
        fprintf(E,"\n");
    }
    for(int i=1;i<=sz;i++)
        cout<<V[i]<<" ";
    return 0;
}
