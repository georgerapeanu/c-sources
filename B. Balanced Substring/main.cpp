#include <iostream>
#include <map>
#define OFF 104000
using namespace std;
map<int,int> lst;
string a;
int N;
int rez,tmp;
int main()
{
    cin>>N>>a;a=" "+a;
    lst[0]=0;
    for(int i=1;i<a.size();i++)
    {
        tmp+=(a[i]=='0' ? -1:1);
        if(lst.count(tmp))rez=max(rez,i-lst[tmp]);
        else lst[tmp]=i;
    }
    cout<<rez;
    return 0;
}
