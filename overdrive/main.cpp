#include <iostream>
#include <climits>
using namespace std;
void generator(int N,int nr,long long s,vector<long long> *V)
{
    if(nr<N)
    {
        generator(N,nr+1,s+V[nr]);
        generator(N,nr+1,s);
    }
    else if(nr==N)
        V.push_back(s);
}
int main()
{

    return 0;
}