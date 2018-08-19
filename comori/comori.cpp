#include<fstream>
using namespace std;
ifstream f("comori.in");
ofstream g("comori.out");
int x,y,a,b,n,i;
int main()
{
    f>>n;
    for(i=1;i<=n;i++)
    {
        f>>a>>b;
        switch(a)
        {
        case 1:y=y+b;
            break;
        case 2:y=y+b;x=x+b;
            break;
        case 3:x=x+b;
            break;
        case 4:y=y-b;x=x+b;
            break;
        case 5:y=y-b;
            break;
        case 6:x=x-b;y=y-b;
            break;
        case 7:x=x-b;
            break;
        case 8:x=x-b;y=y+b;
            break;
        }
    }
    g<<x<<" "<<y;
    f.close();g.close();
    return 0;
}
