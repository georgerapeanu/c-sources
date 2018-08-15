#include<fstream>
using namespace std;
ifstream f("fagure.in");
ofstream g("fagure.out");
int prim(int x)
{
    if(x<2) return 0;
    else
    {
         for(int i=2;i<=x/2;i++)
         if(x%i==0) return 0;
    }
    return 1;
}
int main()
{
    int l=0,n,fag,i,p,x1,x2,y,k,d;
    f>>n>>k;
    int v[n];
    d=(n-2)/4;
    g<<d<<endl;
    for(i=0;i<n;i++)
    {
        f>>v[i];
    }
    f>>p;
    for(i=0;i<n;i++)
    {
       if(v[i]==p) y=i+1;
    }
     if(y<=6)
     {
         if((y==2)||(y==3))
            g<<"1"<<" "<<"2";
         else
            g<<"1";
     }
     else
     {
         if((y%4==0)||(y%4==1))
         {
             if(y/4+1!=d)
                g<<y/4<<" "<<y/4+1;
             else
                    g<<y/4;
         }
         else
         {
             if(y%4==3)
             {
                    g<<y/4+1;
             }
             if(y%4==2)
                g<<y/4;
         }
     }
     g<<endl;
     fag=d-k+1;
        x1=4*fag-2;
        x2=4*fag+1;
        if(prim(v[x1])&&prim(v[x2]))
        {
            if(v[x1]>v[x2]) g<<v[x1];
            else     g<<v[x2];
        }
        else
        {
            if(prim(v[x1]))g<<v[x1];
            else if(prim(v[x2]))g<<v[x2];
            else g<<0;
        }
     f.close();g.close();
    return 0;
}
