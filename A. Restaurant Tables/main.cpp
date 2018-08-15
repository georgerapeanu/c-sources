#include <iostream>
using namespace std;
int a,b,c,N,val,nr;
int main()
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    cin>>N>>a>>b;
    for(int i=1;i<=N;i++)
    {
        cin>>val;
        if(val==1)
        {
            if(a)
            {
                a--;
            }
            else if(b)
            {
                b--;
                c++;
            }
            else if(c)
            {
                c--;
            }
            else
                nr++;
        }
        else
        {
            if(b)
            {
                b--;
            }
            else
            {
                nr+=2;
            }
        }
    }
    cout<<nr;
    return 0;
}
