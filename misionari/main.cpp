#include <fstream>
using namespace std;
ifstream f("misionari.in");
ofstream g("misionari.out");
int m,c,md,cd;
int main()
{
    f>>m>>c;
    md=0;cd=0;
    while(m!=0||c!=0)
    {
        if(m!=0&&c!=0)
           {
               m--;c--;md++;cd++;g<<1<<" "<<1<<"\n";
           }
           else
           {
               if(m>1)
               {
                   g<<2<<" "<<"\n";
                   m-=2;md+=2;
               }
               else
               {
                   g<<1<<" 0"<<"\n";
                   m--;md++;
               }
           }
           if(m==0&&c==0)
           break;
           if(m>c&&cd!=0)
           {
               g<<0<<" "<<1<<"\n";
               cd--;c++;
           }
           else
           {
              g<<1<<" "<<0<<"\n";
              md--;m++;
           }
    }
    f.close();g.close();
    return 0;
}
