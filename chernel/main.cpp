#include <cstdio>
#include <cmath>
using namespace std;
FILE *f=fopen("chernel.in","r");
FILE *g=fopen("chernel.out","w");
long long N,M,i,rez,a,b,j;
int facprim[1005];
int expo[1005];
int P[1005];
bool ok;
int numereprime[185]={0,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,271,277,281,283,293,307,311,313,317,331,337,347,349,353,359,367,373,379,383,389,397,401,409,419,421,431,433,439,443,449,457,461,463,467,479,487,491,499,503,509,521,523,541,547,557,563,569,571,577,587,593,599,601,607,613,617,619,631,641,643,647,653,659,661,673,677,683,691,701,709,719,727,733,739,743,751,757,761,769,773,787,797,809,811,821,823,827,829,839,853,857,859,863,877,881,883,887,907,911,919,929,937,941,947,953,967,971,977,983,991,997};
void desc()
{
    i=1;
    while(M!=1&&numereprime[i]!=0)
    {
        if(M%numereprime[i]==0)
        {
            facprim[++facprim[0]]=numereprime[i];
            while(M%numereprime[i]==0)
            {
                expo[facprim[0]]++;
                M/=numereprime[i];
            }
        }
        i++;
    }
    if(M!=1)
    {facprim[++facprim[0]]=M;expo[facprim[0]]=1;}
}
/*double A,tmpdouble,basicval;//basicaval-tine minte log(M) ca sa nu mai fie apelat
//A tine minte la ce putere este ridicat 10 ca sa dea rezultatul combinarilor la care suntem
int main()
{
    fscanf(f,"%lld %lld",&N,&M);
    if(M==1)//salveaza timp
    {fprintf(g,"%lld",N);return 0;}
    N--;//pentru N valori,coeficenti vor fi C(N-1,k),k intre 0 si N-1;
    basicval=log10(M);
    for(i=1;i<=(N-1)/2;i++)
    {
        A=A+log10(N-i+1)-log10(i);//derivata din faptul ca C(N,K)=C(N,K-1)*(N-k+1)/k
        tmpdouble=pow(10,((A/basicval)-1)*basicval);//tmpdouble stie cat este C(N,K)/M;
        if((long long)(A/basicval)>0&&((tmpdouble)-(long long)(tmpdouble)<=0.00000000000001||(long long)(tmpdouble)+1-(tmpdouble)<=0.00000000000001))
            rez+=2;
    }
    if(!(N&1))
     {
         A=A+log10(N-i+1)-log10(i);
        tmpdouble=pow(10,((A/basicval)-1)*basicval);
        if((long long)(A/basicval)>0&&((tmpdouble)-(long long)(tmpdouble)<=0.00000000000001||(long long)(tmpdouble+1)-(tmpdouble)<=0.00000000000001))
            rez++;
    }
    fprintf(g,"%lld",rez);
    fclose(f);
    fclose(g);
    return 0;

}
*/
int main()
{
    fscanf(f,"%lld %lld",&N,&M);
     if(M==1)//salveaza timp
    {fprintf(g,"%lld",N);return 0;}
    N--;
    desc();
    for(i=1;i<=(N-1)/2;i++)
    {
        ok=1;
        for(j=1;j<=facprim[0];j++)
        {
            a=N-i+1;
            b=i;
            while(a%facprim[j]==0)
            {
                P[j]++;
                a/=facprim[j];
            }
            while(b%facprim[j]==0)
            {
                P[j]--;
                b/=facprim[j];
            }
            ok=ok&(P[j]>=expo[j]);
        }
        if(ok)
            rez+=2;
    }
    if(!(N&1))
    {
        ok=1;
        for(j=1;j<=facprim[0];j++)
        {
            a=N-i+1;
            b=i;
            while(a%facprim[j]==0)
            {
                P[j]++;
                a/=facprim[j];
            }
            while(b%facprim[j]==0)
            {
                P[j]--;
                b/=facprim[j];
            }
            if(P[j]<expo[j])
            {
                ok=0;
                break;
            }
        }
        if(ok)
            rez++;
    }
    fprintf(g,"%lld",rez);
    fclose(f);
    fclose(g);
}
