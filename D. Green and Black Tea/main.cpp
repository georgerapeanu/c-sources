#include <iostream>
#include <cstdio>

using namespace std;
int N,K,a,b;
string R;
int main()
{
    ///freopen("1.out","w",stdout);
    cin>>N>>K>>a>>b;
    while(a&&b)
    {
        if(a>b)
        {
            bool c=R.empty() ? 0:R.back()=='G';
            for(int i=1;i<=a&&i<=K-c;i++)
            {
                R.push_back('G');
            }
            R.push_back('B');
            a-=K-c;
            if(a<0)
                a=0;
            b--;
        }
        else
        {
            bool c=R.empty() ? 0:R.back()=='B';
            for(int i=1;i<=b&&i<=K-c;i++)
            {
                R.push_back('B');
            }
            R.push_back('G');
            b-=K-c;
            if(b<0)
                b=0;
            a--;
        }
    }
    if(a>K||b>K)
    {
        cout<<"NO";
        return 0;
    }
    while(a)
    {
        R.push_back('G');
        a--;
    }
    while(b)
    {
        R.push_back('B');
        b--;
    }
    cout<<R;
    return 0;
}
