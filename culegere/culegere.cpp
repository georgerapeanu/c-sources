#include<fstream>
#include<cmath>
using namespace std;
ifstream f("culegere.in");
ofstream g("culegere.out");
long long P,N,M,nt,putere10=1,x,nrcif,nr,i;
int main()
{

   f>>P>>N;
    M=sqrt(double(N));
    while(M*(M+1)/2<N)
        M++;
    nt=P*(P+1)/2;
    x=nt;
    while(x)
    {
        nrcif++;x/=10;
    }
    i=1;
    while(i<nrcif)
    {
        nr=nr+i*9*putere10;
        i++;
        putere10*=10;
    }
    nr+=(nt-putere10+1)*nrcif;
    g<<nr<<"\n"<<M;
   f.close();g.close();
   return 0;
}
