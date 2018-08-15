#include <iostream>
using namespace std;
int frecv[100005];
int val,mval;
int N;
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>val;
        frecv[val]++;
        mval=max(val,mval);
    }
    int rez=0;
    for(int i=2;i<=mval;i++)
    {
        int nr=0;
        for(int j=i;j<=mval;j+=i)
            nr+=frecv[j];
        rez=max(rez,nr);
    }
    cout<<max(rez,1);
    return 0;
}
