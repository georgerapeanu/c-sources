#include <iostream>
using namespace std;
string b,a;
long long rez;
int fr[280];
int main()
{
    cin>>b;
    for(auto it:b)fr[it]++;
    for(int i=0;i<b.size();i++)
    {
        fr[b[i]]--;
        //cout<<(int)b.size()-1-i-fr[b[i]]<<"\n";
        rez+=((int)b.size()-1-i-fr[b[i]]);
    }
    cout<<rez+1;
    return 0;
}
