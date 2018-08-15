#include <iostream>
using namespace std;
int main()
{
    int i,n=500,putere=5,nrputere=0;
    while(putere<n)
    {
        for(i=1;i<=n;i++)
        {
            if(i%putere)
                nrputere++;
        }
        putere*=5;
    }
    cout<<nrputere;
    return 0;
}
