#include <iostream>
using namespace std;
string a;
int N,rez;
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>a;
        switch(a[0])
        {
            case 'T':rez+=4;break;
            case 'C':rez+=6;break;
            case 'O':rez+=8;break;
            case 'D':rez+=12;break;
            case 'I':rez+=20;break;
        }
    }
    cout<<rez;
    return 0;
}
