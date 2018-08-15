#include <iostream>
#include <set>
using namespace std;
int N;
string a;
pair<char,char> c;
int mat[257][257];
int rez;
int dletters(string a)
{
    set <int> E;
    E.clear();
    for(auto it:a)
        {E.insert(it);if(E.size()>2) return 3;}
    c.first=*E.begin();
    c.second=*E.rbegin();
    return E.size();
}
int update()
{
    if(c.first==c.second)
    {
        for(int i=0;i<257;i++)
            {mat[c.first][i]+=a.size(),mat[i][c.first]+=a.size()*(c.first!=i);rez=max(rez,max(mat[i][c.first],mat[c.first][i]));}
    }
    else
    {
        mat[c.first][c.second]+=a.size();mat[c.second][c.first]+=a.size();
        rez=max(rez,max(mat[c.first][c.second],mat[c.second][c.first]));
    }
}
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>a;
        if(dletters(a)<=2)
            update();
    }
    cout<<rez;
    return 0;
}
