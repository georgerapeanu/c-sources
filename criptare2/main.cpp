#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
using namespace std;
unordered_set<string> S;
string tmp;
int N,M;
string cripteaza(string a)
{
    unordered_map<char,char> I;
    for(char c='a';c<='z';c++)
        I[c]='\0';
    string rez;
    rez.clear();
    char c='a';
    for(auto it:a)
    {
        if(I[it]=='\0')
            I[it]=c++;
        rez.push_back(I[it]);
    }
    return rez;
}
int main()
{
    freopen("criptare2.in","r",stdin);
    freopen("criptare2.out","w",stdout);
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>tmp;
        S.insert(cripteaza(tmp));
    }
    cin>>M;
    for(int i=1;i<=M;i++)
    {
        cin>>tmp;
        if(S.find(cripteaza(tmp))!=S.end())
            cout<<"1\n";
        else
            cout<<"0\n";
    }
    return 0;
}
