#include <iostream>
#include <set>
using namespace std;
int N;
set<string> S;
string rez;
int nr=1<<30;
int sol[]={0,1,2,3,4,5,6,7,7,8,8,8,8,8,8,8,8,8,8,8,8};
int tmp=15;
string ceva[]={
    "",
    "0",
    "00",
    "000",
    "0000",
    "00000",
    "000000",
    "0000000",
    "00101100",
    "000101100",
    "0001011000",
    "00101100101",
    "001011001011",
    "0010110010110",
    "00101100101100",
    "001011001011001"
};
int eval(string a)
{
    S.clear();
    for(int i=0;i<a.size();i++)
    {
        for(int j=i;j<a.size();j++)
        {
            bool ok=1;
            for(int st=i,dr=j;st<dr;st++,dr--)if(a[st]!=a[dr]){ok=0;break;}
            if(ok)S.insert(a.substr(i,j-i+1));
        }
    }
    return S.size();
}
int main()
{
    cin>>N;
    if(N<=tmp)
    {
        cout<<sol[N]<<"\n"<<ceva[N];
    }
    else
    {
        string rez;
        for(int i=1;i<=N;i+=6)
        {
            rez+="001011";
        }
        while(rez.size()>N)rez.pop_back();
        cout<<eval(rez)<<"\n"<<rez;
    }
    return 0;
}
