#include <iostream>

using namespace std;
long long nr,p10,rad;
bool gasit;
int main()
{
    rad=4353;
    while(!gasit)
    {
        nr=rad*rad;
        p10=1;
        while(nr)
        {
            p10*=10;
            nr/=10;
        }
        p10/=10000;
        nr=rad*rad;
        if(nr/p10==1895&&nr%10000==2016)
            gasit=1;
        rad++;
    }
    cout<<nr;
    return 0;
}
