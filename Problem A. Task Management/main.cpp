#include <iostream>
using namespace std;
int poz;
int AIB[200006];
int N;
int val;
int P[200006];
long long rez;
void u(int pos,int val)
{
    for(;pos<=N;pos+=(-pos)&pos)
        AIB[pos]+=val;
}
int q(int pos)
{
    int rez=0;
    for(;pos;pos-=(-pos)&pos)
        rez+=AIB[pos];
    return rez;
}
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++){cin>>val;P[val]=i;}
    rez=1;
    for(int i=1;i<=N;i++)
    {
        if(poz>P[i])
        {
            poz=0;
            rez++;
        }
        poz=P[i];
    }
    cout<<rez;
    return 0;
}
