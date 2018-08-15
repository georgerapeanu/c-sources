#include <fstream>
using namespace std;
ifstream f("romane.in");
ofstream g("romane.out");
int n,uc,nrI,nrV,nrX,nrC,nrL,pc,dc,i;
int main()
{
    f>>n;
    for(i=1;i<=n;i++)
    {
    pc=i/100;dc=i/10%10;uc=i%10;
    switch(uc)
    {
        case 0:;
        break;
        case 1:nrI++;
        break;
        case 2:nrI+=2;
        break;
        case 3:nrI+=3;
        break;
        case 4:nrI++;nrV++;
        break;
        case 5:nrV++;
        break;
        case 6:nrI++;nrV++;
        break;
        case 7:nrI+=2;nrV++;
        break;
        case 8:nrI+=3;nrV++;
        break;
        case 9:nrI++;nrX++;
        break;
    }
    switch(dc)
    {
        case 0:;
        break;
        case 1:nrX++;
        break;
        case 2:nrX+=2;
        break;
        case 3:nrX+=3;
        break;
        case 4:nrX++;nrL++;
        break;
        case 5:nrL++;
        break;
        case 6:nrX++;nrL++;
        break;
        case 7:nrX+=2;nrL++;
        break;
        case 8:nrX+=3;nrL++;
        break;
        case 9:nrC++;nrX++;
        break;
    }
        switch(pc)
    {
        case 0:;
        break;
        case 1:nrC++;
        break;
        case 2:nrC+=2;
        break;
        case 3:nrC+=3;
        break;
    }
    }
    g<<nrI<<" "<<nrV<<" "<<nrX<<" "<<nrL<<" "<<nrC;
    f.close();g.close();
    return 0;
}
