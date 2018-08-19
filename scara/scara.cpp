#include<fstream>
using namespace std;
ifstream f("scara.in");
ofstream g("scara.out");
int main()
{
    long long n,grupa;
    f>>n;
    grupa=(n-1)/4;
    if(grupa%2==0)
    {
        g<<grupa+n-(grupa*4)-1 <<" "<<grupa<<"\n";
    }
    else
    {
        g<<grupa+((grupa+1)*4)-n <<" "<<grupa<<"\n";
    }
    f.close();g.close();
    return 0;
}
