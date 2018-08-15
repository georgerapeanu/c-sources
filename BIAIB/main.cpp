#include <fstream>
#define zeros(x) (x^(x-1))&x
using namespace std;
ifstream f("1.in");
ofstream g("1.out");
int N=3,i,j,AIB[100][100],x,y,cantitate,xx,yy,rez1,rez2,rez3,rez4,M=11,sens;
char c[300];
void add(int x,int y,int quantity)
{
    for(int i=x;i<=N;i+=zeros(i))
        for(int j=y;j<=N;j+=zeros(j))
            AIB[i][j]+=quantity;
}
int suma(int x,int y)
{
    int rez=0;
    for(int i=x;i>0;i-=zeros(i))
        for(int j=y;j>0;j-=zeros(j))
            rez+=AIB[i][j];
    return rez;
}
int main()
{
    for(i=1;i<=M;i++)
    {
       f.getline(c,200);
       x=y=xx=yy=cantitate=0;
       if(c[0]=='s')
        {
            j=0;
            while(isalpha(c[j]))j++;
            j++;
            while(isdigit(c[j])){x=x*10+c[j]-'0';j++;}
            j++;
            while(isdigit(c[j])){y=y*10+c[j]-'0';j++;}
            j++;
            while(isdigit(c[j])){xx=xx*10+c[j]-'0';j++;}
            j++;
            while(isdigit(c[j])){yy=yy*10+c[j]-'0';j++;}
            j++;
            g<<suma(xx,yy)-suma(x-1,yy)-suma(xx,y-1)+suma(x-1,y-1)<<'\n';
        }
       else
        {
            j=0;sens=1;
            while(isalpha(c[j]))j++;
            j++;
            while(isdigit(c[j])){x=x*10+c[j]-'0';j++;}
            j++;
            while(isdigit(c[j])){y=y*10+c[j]-'0';j++;}
            j++;
            while(isdigit(c[j])||c[j]=='-'){
            if(c[j]!='-')
                cantitate=cantitate*10+(c[j]-'0')*sens;
            else
                sens=-1;
            j++;
            }
            j++;
            add(x,y,cantitate);
        }
    }
    f.close();
    g.close();
    return 0;
}
