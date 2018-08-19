#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
int x,y;
char C[100],uc;
int nr;
int main()
{
    cin.getline(C+1,100);
    int ind=1;
    while(C[ind]!='\0'&&C[ind]!='\n')
    {
        int nr=0;
        while(C[ind]>='0'&&C[ind]<='9')
        {
            nr=10*nr+C[ind]-'0';
            ind++;
        }
        if(uc=='n')y+=nr;
        else if(uc=='e')x+=nr;
        else if(uc=='s')y-=nr;
        else if(uc=='w')x-=nr;
        uc=C[ind];
        ind++;
    }
    cout<<fixed<<setprecision(2)<<sqrt(1.0*(x*x+y*y));
    return 0;
}
