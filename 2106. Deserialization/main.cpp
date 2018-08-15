#include <iostream>
#include <cstdio>
#include <map>
#include <vector>
using namespace std;
map <string,int> M;
string ord[245];
vector <int> cmp[245];
int N,L,nr,i;
string C;
string  nume;
int htod(char c)
{
    if('0'<=c&&c<='9')
        return c-'0';
    return 10+c-'A';
}
long long decodint()
{
    long long rez=0,poz=i;
    for(;i<poz+8;i++)
    {
        rez=rez*16+htod(C[i]);
    }
    return rez;
}
void decodstring(int spatii)
{
    long long lung=decodint(),poz=i;
    while(spatii)
    {
        cout<<" ";
        spatii--;
    }
    cout<<"string ";
    for(;i<poz+2*lung;i+=2)
    {
        char c=0;
        c=htod(C[i])*16+htod(C[i+1]);
        cout<<c;
    }
    cout<<'\n';
}
void solve(int nrstr,int spatii)
{
    for(int i=1;i<=spatii;i++)
        cout<<" ";
    cout<<ord[nrstr]<<"\n";
    for(int i=0;i<cmp[nrstr].size();i++)
    {
        if(cmp[nrstr][i]==-1)
        {
            for(int i=0;i<=spatii;i++)
                cout<<" ";
            cout<<"int ";
            cout<<decodint()<<"\n";
        }
        else if(cmp[nrstr][i]==0)
            decodstring(spatii+1);
        else
            solve(cmp[nrstr][i],spatii+1);
    }
}
int main()
{
    ///freopen("1.in","r",stdin);
    ///freopen("1.out","w",stdout);
    cin>>N>>L;
    getline(cin, C);
    for(i=1;i<=L;i++)
    {
        getline(cin, C);
        if(C[0]=='s')
        {
            nume=C.substr(7);
            ++nr;
            M[nume]=nr;
            ord[nr]=nume;
        }
        else
        {
            if(C==" int")
                cmp[nr].push_back(-1);
            else if(C==" string")
                cmp[nr].push_back(0);
            else
                cmp[nr].push_back(M[C.substr(1)]);
        }
    }
    getline(cin,C);
    N=C.size();
    for(i=0;i<N;)
    {
        solve(decodint(),0);
    }
    return 0;
}
