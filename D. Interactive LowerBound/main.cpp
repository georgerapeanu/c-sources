#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#define bucket 999
#define LIM 1999
using namespace std;
int val=-1000000,nxt;
int N,start,x;
int main()
{
    srand(time(NULL));
    cin>>N>>nxt>>x;
    std::random_device                  rand_dev;
    std::mt19937                        generator(rand_dev());
    std::uniform_int_distribution<int>  distr(1,N);
    for(int i=1;i<=bucket;i++)
    {
        int tmp,n;
        cout<<"? "<<((rand()<<16)+rand())%N+1<<endl;
        cin>>tmp>>n;
        if(tmp<=x&&val<tmp)
        {
            val=tmp;
            nxt=n;
        }
    }
    if(val==x)
    {
        cout<<"! "<<x<<endl;
        return 0;
    }
    if(nxt==-1)
    {
        cout<<"! -1"<<endl;
        return 0;
    }
    int ind=bucket+1;
    while(val<x&&nxt!=-1&&ind<LIM)
    {
        cout<<"? "<<nxt<<endl;
        cin>>val>>nxt;
        ind++;
    }
    cout<<"! "<<(val<x ? -1:val)<<endl;
    return 0;
}
