/*#include <fstream>
#include <iostream>
using namespace std;
ifstream f("fractie.in");
ofstream g("fractie.out");
long long  cmmdc,coo,coo2;
long long nrcifre[2000];
char rez[2000];
void euclid(long long a,long long b)
{
     long long r=a%b;
     if(r!=0)
     euclid(b,r);
     if(r==0)
     cmmdc=b;
}
void transpunere(long long nr)
{
     long long pow=1,cnr=nr;
     if(nr==0)
     nrcifre[coo2]++;
     while(cnr!=0)
     {
         pow*=10;cnr/=10;nrcifre[coo2]++;
     }
     pow/=10;
     if(nr==0)
     {
         rez[coo++]='0';
     }
     else
     while(nr!=0)
     {rez[coo++]=nr/pow+'0';nr%=pow;pow/=10;}
}
void transpunere_int(long long nr)
{
     long long pow=1,cnr=nr;
     if(nr==0)
     while(cnr!=0)
     {
         pow*=10;cnr/=10;
     }
     pow/=10;
     if(nr==0)
     {
         rez[coo++]='0';
     }
     else
     while(nr!=0)
     {rez[coo++]=nr/pow+'0';nr%=pow;pow/=10;}
}
void simpla(long long a,long long b)
{
    long long r;
    transpunere(a/b);
    r=a%b;
    if(r!=0)
    {
        rez[coo++]='.';
        while(r!=0)
        {
            r*=10;
            transpunere(r/b);
            r=r%b;
        }
    }
}
void periodica_simpla(long long a,long long b)
{
    long long r;
    bool rest[1000000];
    for(long long i=0;i<b;i++)
    rest[i]=0;
    transpunere(a/b);
    r=a%b;
    rez[coo++]='.';
    rez[coo++]='(';
     while(rest[r]==0)
        {
            rest[r]=1;
            r*=10;
            transpunere(r/b);
            r=r%b;
        }
        rez[coo]=')';
}
void periodica_mixta(long long a,long long b)
{
     long long r;
    bool rest[1000000];
    long long ordine[2000];
    for(long long i=0;i<b;i++)
    rest[i]=0;
    transpunere_int(a/b);
    r=a%b;
    rez[coo++]='.';
     while(rest[r]==0)
        {
            rest[r]=1;
            r*=10;
            transpunere(r/b);
            ordine[coo2++]=r;
            r=r%b;
        }
        r*=10;
        rez[coo++]=')';
        long long s=0,i;
        for(i=0;i<coo2;i++)
        if(ordine[i]==r)
        break;
        else
        s+=nrcifre[i];
        s+=2;
        for(i=coo;i>=s;i--)
        rez[i]=rez[i-1];
        rez[s]='(';
}
int main()
{
    long long cb=0,a=0,b=0;
    f>>a>>b;cout<<a<<" "<<b;
    euclid(a,b);
    a/=cmmdc;
    b/=cmmdc;cb=b;
    while(cb%5==0)
    cb/=5;
    while(cb%2==0)
    cb/=2;
    if(cb==1)
    {
           simpla(a,b);
    }
    else if(cb==b)
    {
          periodica_simpla(a,b);
    }
    else
    {
        periodica_mixta(a,b);
    }
    g<<rez;
    f.close();g.close();
    return 0;
}
*/
#include <stdio.h>

int main() {
  FILE *fin, *fout;
  int i, a, b, ac, bc, r, p2, p5, z;

  fin = fopen( "fractie.in", "r" );
  fscanf( fin, "%d%d", &a, &b );
  fclose( fin );
  ac = a;
  bc = b;
  while ( bc > 0 ) {
    r = ac % bc;
    ac = bc;
    bc = r;
  }
  a /= ac;
  b /= ac;
  fout = fopen( "fractie.out", "w" );
  fprintf( fout, "%d", a / b );
  if ( a % b > 0 ) {
    fprintf( fout, "." );
    a %= b;
    // calcul numar zecimale pina in perioada in variabila z
    bc = b;
    p2 = p5 = 0;
    while ( bc % 2 == 0 ) {
      p2++;
      bc /= 2;
    }
    while ( bc % 5 == 0 ) {
      p5++;
      bc /= 5;
    }
    z = p2 > p5 ? p2 : p5;
    // afisam z cifre
    for ( i = 0; i < z; i++ ) {
      a *= 10;
      fprintf( fout, "%d", a / b );
      a %= b;
    }
    if ( a > 0 ) {
      // avem perioada
      fprintf( fout, "(" );
      ac = a;
      do {
        a *= 10;
        fprintf( fout, "%d", a / b );
        a %= b;
      } while ( a != ac );
      fprintf( fout, ")" );
    }
  }
  fclose( fout );
  return 0;
}
