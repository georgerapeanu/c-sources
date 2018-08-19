#include <iostream>
#include <bitset>
#define LEN 6
using namespace std;
int V[2*LEN+3];
bitset<LEN+1> B;
int nr;
int eval()
{
    for(int i=1;i<=LEN;i++)
        if(V[i]<max(V[2*i],V[2*i+1]))
            return 0;
    return 1;
}
void gen(int pas)
{
    if(pas>LEN)
        nr+=eval();
    else
    {
        for(int i=1;i<=LEN;i++)
        {
            if(!B[i])
            {
                V[pas]=i;
                B[i]=1;
                gen(pas+1);
                B[i]=0;
            }
        }
    }
}
int main()
{
    gen(1);
    cout<<nr;
    return 0;
}
