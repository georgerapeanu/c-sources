#include <fstream>
using namespace std;
ofstream f("1.out");
ofstream g("2.out");
ofstream e("3.out");
ofstream r("4.out");
int a=123,b=203,c=242,d=258,i,j,y,l;
int main()
{
    f<<123<<"\n";
    while(i*i<=a)
    {
        j=0;
        while(j*j<=a-i*i)
        {
            y=0;
            while(y*y<=a-i*i-j*j)
            {
                l=0;
                while(l*l<=a-i*i-j*j-y*y)
                {
                    if(l*l==a-i*i-j*j-y*y)
                    f<<i<<" "<<j<<" "<<y<<" "<<l<<"\n";
                    l++;
                }
                y++;
            }
            j++;
        }
        i++;
    }
    i=0;
    y=0;
    j=0;
    l=0;
    g<<203<<"\n";
     while(i*i<=b)
    {
        j=0;
        while(j*j<=b-i*i)
        {
            y=0;
            while(y*y<=b-i*i-j*j)
            {
                l=0;
                while(l*l<=b-i*i-j*j-y*y)
                {
                    if(l*l==b-i*i-j*j-y*y)
                    g<<i<<" "<<j<<" "<<y<<" "<<l<<"\n";
                    l++;
                }
                y++;
            }
            j++;
        }
        i++;
    }
    i=0;
    y=0;
    j=0;
    l=0;
    e<<242<<"\n";
     while(i*i<=c)
    {
        j=0;
        while(j*j<=c-i*i)
        {
            y=0;
            while(y*y<=c-i*i-j*j)
            {
                l=0;
                while(l*l<=c-i*i-j*j-y*y)
                {
                    if(l*l==c-i*i-j*j-y*y)
                    e<<i<<" "<<j<<" "<<y<<" "<<l<<"\n";
                    l++;
                }
                y++;
            }
            j++;
        }
        i++;
    }
    i=0;
    y=0;
    j=0;
    l=0;
    r<<258<<"\n";
     while(i*i<=d)
    {
        j=0;
        while(j*j<=d-i*i)
        {
            y=0;
            while(y*y<=d-i*i-j*j)
            {
                l=0;
                while(l*l<=d-i*i-j*j-y*y)
                {
                    if(l*l==d-i*i-j*j-y*y)
                    r<<i<<" "<<j<<" "<<y<<" "<<l<<"\n";
                    l++;
                }
                y++;
            }
            j++;
        }
        i++;
    }
    i=0;
    y=0;
    j=0;
    l=0;
    return 0;
}
