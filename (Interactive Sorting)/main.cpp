#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
char A[30];
char tmp[30];
int N,Q;
int nr;
char q(int x,int y)
{
    char rez;
    nr++;
    if(nr<=Q){cout<<"? "<<A[x]<<" "<<A[y]<<endl;cin>>rez;}
    else rez=(rand()%2==0 ? '<':'>');
    return rez;
}
void ms(int st,int dr)
{
    if(st==dr)return ;
    ms(st,(st+dr)/2);
    ms((st+dr)/2+1,dr);
    int x=st,y=(st+dr)/2+1;
    int ind=st;
    while(x<=(st+dr)/2&&y<=dr)
    {
        char c;c=q(x,y);
        if(c=='<')
            tmp[ind++]=A[x++];
        else
            tmp[ind++]=A[y++];
    }
    while(x<=(st+dr)/2)
        tmp[ind++]=A[x++];
    while(y<=dr)
        tmp[ind++]=A[y++];
    for(int i=st;i<=dr;i++)
        A[i]=tmp[i];
}
int main()
{
    srand(time(NULL));
    cin>>N>>Q;
    for(int i=1;i<=N;i++)A[i]=i+'A'-1;
    ms(1,N);
    cout<<"! "<<A+1<<endl;
    return 0;
}
