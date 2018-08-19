#include <iostream>
#include <cstring>
using namespace std;
int fr[100000];
string a;
int nr;
int T;
int N;
int main()
{
    cin>>T;
    while(T--)
    {
        memset(fr,0,sizeof(fr));
        cin>>N;
        int rez=0,tmp=0;
        while(N--)
        {
            cin>>a>>nr;
            fr[nr]++;
            if(fr[nr]>tmp)
            {
                tmp=fr[nr];
                rez=nr;
            }
            else if(fr[nr]==tmp)
            {
                rez=min(rez,nr);
            }
        }
        cout<<rez<<"\n";
    }
    return 0;
}
