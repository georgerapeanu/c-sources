#include <fstream>
#include <iostream>
#include <cstring>
using namespace std;
ifstream f("timer.in");
ofstream g("timer.out");
char a[8],b[300000002];
long long int z,h,m,s,h2,m2,s2,adm,adh,c=1,i,p;
int main()
{
    f>>a;
    f>>b;
    h=(a[0]-'0')*10+(a[1]-'0');
    m=(a[3]-'0')*10+(a[4]-'0');
    s=(a[6]-'0')*10+(a[7]-'0');
     for(i=strlen(b)-1;i>=0;i--)
    {
        p=1;
        while(b[i]>='0'&&b[i]<='9')
        {
            if(c==1)
                {s2=(b[i]-'0')*p+s2;}
            if(c==2)
                {m2=(b[i]-'0')*p+m2;}
            if(c==3)
               {h2=(b[i]-'0')*p+h2;}
               p=p*10;
                        i--;
                  if(i<0)
                            break;
        }
        c++;
    }
    adm=s2/60;
    s2=s2%60;
    m2=m2+adm;
    adh=m2/60;
    m2=m2%60;
    h2=h2+adh;
    z=h2/24;
    h2=h2%24;
    s+=s2;
    m+=m2;
    h+=h2;
    adm=s/60;
    s=s%60;
    m+=adm;
    adh=m/60;
    m=m%60;
    h+=adh;
    z+=h/24;
    h=h%24;
    if(h<=9)
        g<<"0"<<h<<":";
    else
        g<<h<<":";
    if(m<=9)
        g<<"0"<<m<<":";
    else
        g<<m<<":";
    if(s<=9)
        g<<"0"<<s;
    else
        g<<s;
        if(z!=0)
        g<<"+"<<z;
        f.close();g.close();
    return 0;
}
