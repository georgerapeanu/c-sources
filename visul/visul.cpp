#include<fstream>
#include<iostream>
using namespace std;
ifstream f("visul.in");
ofstream g("visul.out");
int n,a,b,c,i,j,ciur[100],gasit;
int main()
{
f>>n;
/*a=n;
if(n!=1)
{
for(i=1;i<=100&&ciur[i]!=1;i++)
{
    for(j=i+i;j<=100&&ciur[j]!=1;j+=i)
        ciur[j]=1;
}
for(i=1;i<n;i++)
{
    for(j=1;j<=9&&j%2!=0&&j%5!=0;j++)
    {
        if((ciur[a*10+j])==0)
        {
            if(i==1)
            {  cout<< n;
                g<<n;        g<<1;
                gasit=1;
                b=j;g<<b;
            }
            break;
        }
    }
    if(i==1&&gasit==0)
    {
    break;
    }
}
if(gasit==0)
    g<<"-1";
}
else
    g<<"-1";*/
    switch(n)
    {
        case 0:
        case 1:
        case 10:g<<"-1";
        break;
        case 2:g<<23;
        break;
        case 3:g<<311;
        break;
        case 4:g<<4113;
        break;
        case 5:g<<53113;
        break;
        case 6:g<<611317;
        break;
        case 7:g<<7113173;
        break;
        case 8:g<<83113717;
        break;
        case 9:g<<971131737;
        break;
    }
    f.close();g.close();
    return 0;
}
