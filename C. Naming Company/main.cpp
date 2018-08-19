#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
int st,dr,turn;
string a,b;
int tI,tO;
string C,tmp;
string strategie1()
{
    string rez;rez.clear();
    int tmpI=tI;
    int tmpO=tO;
    tmp=C;
    int lo=st,hi=dr,t=turn;
    while(lo<=hi)
    {
        if(!t)tmp[lo++]=a[tmpO++];
        else tmp[lo++]=b[tmpI--];
        t=1-t;
    }
    rez=tmp;
    cout<<rez<<"\n";
    tmpI=tI;
    tmpO=tO;
    tmp=C;
    lo=st,hi=dr,t=turn;
    while(lo<=hi)
    {
        if(!t)tmp[lo++]=a[tmpO++];
        else tmp[hi--]=b[tmpI--];
        t=1-t;
    }
    if(turn==0)rez=max(rez,tmp);
    else rez=min(rez,tmp);
     cout<<tmp<<"\n";
    return rez;
}
string strategie2()
{
    string rez;rez.clear();
    int tmpI=tI;
    int tmpO=tO;
    tmp=C;
    int lo=st,hi=dr,t=turn;
    while(lo<=hi)
    {
        if(!t)tmp[hi--]=a[tmpO++];
        else tmp[lo++]=b[tmpI--];
        t=1-t;
    }
    rez=tmp;
    cout<<rez<<"\n";
    tmpI=tI;
    tmpO=tO;
    tmp=C;
    lo=st,hi=dr,t=turn;
    while(lo<=hi)
    {
        if(!t)tmp[hi--]=a[tmpO++];
        else tmp[hi--]=b[tmpI--];
        t=1-t;
    }
    if(turn==0)rez=max(rez,tmp);
    else rez=min(rez,tmp);
    cout<<tmp<<"\n";
    return rez;
}
int main()
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    cin>>a>>b;
    int iAmSorryButQueueStoppedSoISubmitedOnceAgain=1;
    st=1;dr=a.size();
    for(int i=0;i<=dr;i++)C+='?';
    sort(a.begin(),a.end());tO=0;
    sort(b.begin(),b.end());tI=dr-1;
    while(st<=dr)
    {
        if(a[tO]<b[tI])
        {
            if(!turn)
                {C[st++]=a[tO++];}
            else
                {C[st++]=b[tI--];}
        }
        else
        {
            break;
        }
        turn=1-turn;
    }
    if(turn==0)C=min(strategie1(),strategie2());
    else C=max(strategie1(),strategie2());
    cout<<C.substr(1);
    return 0;
}
