#include<fstream>
#include<iostream>
using namespace std;
ifstream f("chibrituri.in");
ofstream g("chibrituri.out");
int main()
{
    int ve,ori,hh=0,m1=0,m2=0,i=0,a,b,h=0,maxim=0,l;
    f>>ve;
    f>>ori;
    m2=0;
    while(hh<=23)
    {
        a=0;
        b=0;
        if(hh<=9)
        {
            a=a+4;
            b=b+2;
        }
        if(m2==10)
        {
            m2=0;
            m1++;
        }
        if(m1==6)
        {
            hh++;
            m1=0;
        }
        switch(hh)
        {
            case 0:a+=4;b+=2;
            break;
            case 1:a=a+2;
            break;
            case 2:a=a+2;b=b+3;
            break;
            case 3:a=a+2;b=b+3;
            break;
            case 4:a+=3;b+=1;
            break;
            case 5:a+=2;b+=3;
            break;
            case 6:a+=3;b+=3;
            break;
            case 7:a+=2;b+=1;
            break;
            case 8:a+=4;b+=3;
            break;
            case 9:a+=3;b+=3;
            break;
            case 10:a+=6;b+=2;
            break;
            case 11:a+=4;
            break;
            case 12:a+=4;b+=3;
            break;
            case 13:a+=4;b+=3;
            break;
            case 14:a+=5;b+=1;
            break;
            case 15:a+=4;b+=3;
            break;
            case 16:a+=5;b+=3;
            break;
            case 17:a+=4;b+=1;
            break;
            case 18:a+=5;b+=3;
            break;
            case 19:a+=5;b+=3;
            break;
            case 20:a+=6;b+=5;
            break;
            case 21:a+=4;b+=3;
            break;
            case 22:a+=4;b+=6;
            break;
            case 23:a+=4;b+=6;
            break;
        }
        switch(m2)
        {
            case 0:a+=4;b+=2;
            break;
            case 1:a=a+2;
            break;
            case 2:a=a+2;b=b+3;
            break;
            case 3:a=a+2;b=b+3;
            break;
            case 4:a+=3;b+=1;
            break;
            case 5:a+=2;b+=3;
            break;
            case 6:a+=3;b+=3;
            break;
            case 7:a+=2;b+=1;
            break;
            case 8:a+=4;b+=3;
            break;
            case 9:a+=3;b+=3;
            break;
        }
        switch(m1)
        {
            case 0:a+=4;b+=2;
            break;
            case 1:a=a+2;
            break;
            case 2:a=a+2;b=b+3;
            break;
            case 3:a=a+2;b=b+3;
            break;
            case 4:a+=3;b+=1;
            break;
            case 5:a+=2;b+=3;
            break;
        }
        if(a==ve&&b==ori)
           {
            i++;
           }
        if(i==1&&h==0)
        {
            h=hh*100+m1*10+m2;
        }
        l=hh*100+m1*10+m2;
        if(a==ve&&b==ori&&l>maxim)
            maxim=l;
        m2++;
    }

        g<<i<<"\n";
        if(h/100<=9)
        {
            if(h%100<=9)
            g<<"0"<<(h/100)<<":"<<"0"<<(h%100)<<"\n";
        else
            g<<"0"<<(h/100)<<":"<<(h%100)<<"\n";
        }
        else
        {
            if(h%100<=9)
                g<<(h/100)<<":"<<"0"<<(h%100)<<"\n";
            else
                g<<(h/100)<<":"<<(h%100)<<"\n";
        }
        if(maxim/100<=9)
        {
        if(maxim%100<=9)
            g<<"0"<<(maxim/100)<<":"<<"0"<<(maxim%100);
        else
            g<<"0"<<(maxim/100)<<":"<<(maxim%100);
        }
        else
        {
            if(maxim%100<=9)
                g<<(maxim/100)<<":"<<"0"<<(maxim%100);
            else
                g<<(maxim/100)<<":"<<(maxim%100);
        }
        f.close();g.close();
        return 0;
}
