#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>
using namespace std;
int nxt[280];
int ant[280];
bool viz[280];
bool used[280];
string a;
int N;
void giveup()
{
    cout<<"NO";
    exit(0);
}
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>a;
        for(auto it:a)used[it]=1;
        for(int i=0;i<a.size()-1;i++)
        {
            if(nxt[a[i]]&&nxt[a[i]]!=a[i+1])giveup();
            nxt[a[i]]=a[i+1];
            if(ant[a[i+1]]&&ant[a[i+1]]!=a[i])giveup();
            ant[a[i+1]]=a[i];
        }
    }
    vector<string> V;
    for(char i='a';i<='z';i++)
    {
        if((!used[i])||viz[i])continue;
        char nod=i;
        while(ant[nod]&&ant[nod]!=i)
            nod=ant[nod];
        if(ant[nod]==i)giveup();
        string tmp="";
        while(nxt[nod])
        {
            viz[nod]=1;
            tmp+=nod;
            nod=nxt[nod];
        }
        viz[nod]=1;
        tmp+=nod;
        V.push_back(tmp);
    }
    sort(V.begin(),V.end());
    for(auto it:V)cout<<it;
    return 0;
}
