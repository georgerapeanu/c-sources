#include <iostream>

using namespace std;
int M,N;
int nr;
bool u[100];
int dist;
void btr(int pas)
{
    if(pas>N)
    {if(dist==M)
            nr++;}
    else
    {
        for(int i=1;i<=M;i++)
        {
            bool tmp=u[i];
            dist+=(tmp==0);
            u[i]=1;
            btr(pas+1);
            u[i]=tmp;
            dist-=(tmp==0);
        }
    }
}
int main()
{
    cin>>N>>M;
    btr(1);
    cout<<nr;
    return 0;
}
