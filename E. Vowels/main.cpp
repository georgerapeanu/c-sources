#include <iostream>

using namespace std;
int N;
string a;
int F[1<<24];
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>a;
        int nr=0;
        for(auto it:a)
            nr|=(1<<(it-'a'));
        F[nr]++;
    }
    for(int i=0;i<24;i++)
    {
        for(int j=0;j<(1<<24);j++)
        {
            if((j&(1<<i))==0)
            {

            }
        }
    }
    return 0;
}
