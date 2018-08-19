#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
int T;
int dist(int a,int b)
{
    return min(abs(b-a),abs(b-100-a));
}
int main() {
    cin>>T;
    while(T--)
    {
        int nrq=0;
        bool rez;
        vector<int> b;
        for(int i=0;i<=99&&b.size()<2;i+=11)
        {
            nrq++;
            cout<<i<<endl;
            bool rez;
            cin>>rez;
            if(rez)b.push_back(i);
        }
        if(b.size()==1)cout<<b[0]+10<<endl;
        else
        {
            for(int i=0;i<=99&&nrq<11;i++)
            {
                if(i%11!=0&&i%10!=b[0]%10&&i%10!=b[1]%10&&dist(b[0],i)>9&&dist(b[1],i)>9)
                {
                    cout<<i<<endl;
                    nrq++;
                }
            }
        }
    }
    return 0;
}
