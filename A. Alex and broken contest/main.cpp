#include <iostream>
#include <map>
using namespace std;
map<string,int> fr;
string a;
int main()
{
    cin>>a;
    for(int i=0;i<a.size();i++)
    {
        for(int j=i;j<a.size();j++)
        {
            fr[a.substr(i,j-i+1)]++;
        }
    }
    int nr=fr["Danil"]+fr["Olya"]+fr["Slava"]+fr["Ann"]+fr["Nikita"];
    cout<<(nr==1 ? "YES":"NO");
    return 0;
}
