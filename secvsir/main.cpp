#include <fstream>
#include <fstream>
#include <cstring>
using namespace std;
ifstream f("secvsir.in");
ofstream g("secvsir.out");
int N,l,i,j,k;
char c[1500],desc[3];
int main()
{
    f>>N;
    for(i=1;i<=N;i++)
    {
        if(i<=9)
        {
            desc[0]=i+'0';
            strcat(c,desc);
            l++;
        }
        else if(i<=99)
        {
            k=0;
            j=0;
            desc[0]='0'+i/10;
            desc[1]='0'+i%10;
            while(k<2&&j<l)
            {
                for(k=0;k<2&&desc[k]==c[j]&&j<=l;k++)
                {
                    j++;
                }
                j++;
            }
            if(k<2)
            {
                strcat(c,desc);
                l+=2;
            }
        }
        else
        {
            k=0;
            j=0;
            desc[0]='0'+i/100;
            desc[1]='0'+i/10%10;
            desc[2]='0'+i%10;
            while(k<3&&j<l)
            {
                for(k=0;k<3&&desc[k]==c[j]&&j<=l;k++)
                {
                    j++;
                }
                j++;
            }
            if(k<3)
            {
                strcat(c,desc);
                l+=3;
            }
        }
    }
    g<<c;
    return 0;
}
