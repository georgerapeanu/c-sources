#include <cstdio>
using namespace std;
FILE *f=fopen("antobroasca.in","r");
FILE *g=fopen("antobroasca.out","w");
int A,B,X,Y,Z,T;
int gcd(int a,int b)
{
    if(!b)return a;
    return gcd(b,a%b);
}
int main()
{
    fscanf(f,"%d",&T);
    while(T--)
    {
        fscanf(f,"%d%d%d%d%d",&X,&Y,&Z,&A,&B);
        fputs((A%gcd(X,Z)==0&&B%gcd(Y,Z)==0&&(A-B)%gcd(X,Y)==0) ? "DA\n":"NU\n",g);
    }
    fclose(f);
    fclose(g);
    return 0;
}
