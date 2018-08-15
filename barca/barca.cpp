#include<fstream>
using namespace std;
ifstream f("barca.in");
ofstream g("barca.out");
int main()
{
    int n,t,i,k=0;
    f>>n;
    t=n*4;
    g<<t<<"\n";
    for(i=0;i<t;i++)
    {
        switch(i%4)
        {
            case 0:g<<"IG"<<"\n";
            break;
            case 1:g<<"I"<<"\n";
            break;
            case 2:k++;g<<k<<"\n";
            break;
            case 3:g<<"G"<<"\n";
        }
    }
    f.close();g.close();
    return 0;
}
