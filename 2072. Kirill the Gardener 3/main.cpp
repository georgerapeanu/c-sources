#include <iostream>
#define inf 10000000000
#include <algorithm>
using namespace std;
pair<int,int> V[100005];
int st,dr,N;
long long D[100005][2],rez,minst,mindr,nextminst,nextmindr;
int prevst,prevdr;
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>V[i].first;
        V[i].second=i;
    }
    sort(V+1,V+1+N);
    V[0].second=1;
    int i=1;
    while(i<=N)
    {
        st=i;
        while(V[st].first==V[i].first)
            i++;
        dr=i-1;
        nextminst=nextmindr=inf;
        for(int i=st;i<=dr;i++)
        {
            if(V[i].second>V[prevdr].second)
            {
                D[i][0]=V[dr].second-V[st].second+V[dr].second-V[i].second;///distanta daca il luam pe i primul si parcurgem pe cei de acelasi ranc inspre dreapta,apoi terminam in stanga
                D[i][0]+=V[i].second-V[prevdr].second;///distanta de a ajunge in dreapta anterioara
                D[i][0]+=mindr;///minimul care se termina in dr
                D[i][1]=V[dr].second-V[st].second+V[i].second-V[st].second;///distanta daca il luam pe i primul si parcurgem pe cei de acelasi ranc inspre stanga,apoi terminam in dreapta
                D[i][1]+=V[i].second-V[prevdr].second;
                D[i][1]+=mindr;
            }
            else if(V[i].second<V[prevst].second)
            {
                D[i][0]=V[dr].second-V[st].second+V[dr].second-V[i].second;///distanta daca il luam pe i primul si parcurgem pe cei de acelasi ranc inspre dreapta,apoi terminam in stanga
                D[i][0]+=V[prevst].second-V[i].second;
                D[i][0]+=minst;
                D[i][1]=V[dr].second-V[st].second+V[i].second-V[st].second;///distanta daca il luam pe i primul si parcurgem pe cei de acelasi ranc inspre stanga,apoi terminam in dreapta
                D[i][1]+=V[prevst].second-V[i].second;
                D[i][1]+=minst;
            }
            else
            {
                D[i][0]=V[dr].second-V[st].second+V[dr].second-V[i].second+min(minst+V[i].second-V[prevst].second,mindr+V[prevdr].second-V[i].second);
                D[i][1]=V[dr].second-V[st].second+V[i].second-V[st].second+min(minst+V[i].second-V[prevst].second,mindr+V[prevdr].second-V[i].second);
            }
            nextminst=min(nextminst,D[i][0]);
            nextmindr=min(nextmindr,D[i][1]);

        }
        prevst=st;
        prevdr=dr;
        minst=nextminst;
        mindr=nextmindr;
    }
    rez=inf;
    rez=min(minst,mindr);
    cout<<rez+N;
    return 0;
}
