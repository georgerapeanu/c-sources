#include <fstream>
#include <cstring>
using namespace std;
ifstream f("ecuatie2.in");
ofstream g("ecuatie2.out");
char v[19];
long long a,b,i,j,tip,x;
int main()
{
    f.getline(v,19);
        if(v[i]=='x')
        {
            i++;
            switch(v[i])
            {
                case '-':tip=4;
                break;
                case '+':tip=2;
                break;
                case ':':tip=8;
                break;
                case '*':tip=6;
                break;
            }
            i++;
            while(v[i]>='0'&&v[i]<='9')
            {
                a=a*10+(v[i]-'0');i++;
            }
            i++;
            while(v[i]>='0'&&v[i]<='9'&&i<strlen(v))
            {b=b*10+(v[i]-'0');i++;}
        }
        else
        {
             while(v[i]>='0'&&v[i]<='9')
            {
                a=a*10+(v[i]-'0');i++;
            }
            switch(v[i])
            {
                case '-':tip=3;
                break;
                case '+':tip=1;
                break;
                case ':':tip=7;
                break;
                case '*':tip=5;
                break;
            }
            i++;
            i++;
            i++;
            while(v[i]>='0'&&v[i]<='9'&&i<strlen(v))
            {b=b*10+(v[i]-'0');i++;}
        }
        switch(tip)
        {
            case 1:
            case 2:x=b-a;
            break;
            case 3:x=a-b;
            break;
            case 4:x=a+b;
            break;
            case 5:
            case 6:x=b/a;
            break;
            case 7:x=a/b;
            break;
            case 8:x=a*b;
            break;
        }
        g<<tip<<'\n'<<x;
        f.close();g.close();
    return 0;
}
