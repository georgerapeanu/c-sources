#include <cstdio>
using namespace std;
FILE *f=fopen("multiplu.in","r");
FILE *g=fopen("multiplu.out","w");
int prime[]={0,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,271,277,281,283,293,307,311,313,317,331,337,347,349,353,359,367,373,379,383,389,397,401,409,419,421,431,433,439,443,449,457,461,463,467,479,487,491,499,503,509,521,523,541,547,557,563,569,571,577,587,593,599,601,607,613,617,619,631,641,643,647,653,659,661,673,677,683,691,701,709,719,727,733,739,743,751,757,761,769,773,787,797,809,811,821,823,827,829,839,853,857,859,863,877,881,883,887,907,911,919,929,937,941,947,953,967,971,977,983,991,997};
/// lungimea vectorului prim este170
int maximprim;
///cel mai mare numar prim care intra in descompunerea unui numar
int M[1005][1005];///elementul a[i][j]= de cate ori intra prime[j] in elementul al i-lea
int i,j,N,x,k;
int P[1005];///produsul numerelor care nu se afla in intervalul [i,j] descompus in factori primi
int p[1005];///produsul din momentul acesta
int minim=1005;
int ctr;///contor pentru exponent
bool ok()
{
    for(int k=1;k<=maximprim;k++)
        if(P[k]>p[k])
            return 0;
    return 1;
}
int main()
{
    fscanf(f,"%d",&N);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d",&x);
        j=1;
        while(x!=1)
        {
            ctr=0;
            while(x%prime[j]==0)
            {
                ctr++;
                x/=prime[j];
            }
            M[i][j]=ctr;
            P[j]+=ctr;
            j++;
        }
        if(j-1>maximprim)
            maximprim=j-1;
    }
    i=j=1;
    for(k=1;k<=maximprim;k++)
    {
        p[k]+=M[j][k];
        P[k]-=M[j][k];
    }
    while(i<N&&j<N)///folosim metoda celor 2 pointeri
    {
        while(!ok()&&j<N)///daca intervalul [i,j] nu este solutie,incercam sa luam intervalul [i,j+1]
        {
            j++;
            for(k=1;k<=maximprim;k++)
            {
                p[k]+=M[j][k];
                P[k]-=M[j][k];
            }

        }
        while(ok())///daca intervalul [i,j] este solutie, incercam sa vedem daca intervalul [i+1,j] este solutie
        {
            i++;
            for(k=1;k<=maximprim;k++)
            {
                    p[k]-=M[i-1][k];
                    P[k]+=M[i-1][k];
            }
        }
        if(j-i+2<minim)///ultima solutie a fost [i-1,j], deci actualizam minim daca se poate
            minim=j-i+2;
    }
    fprintf(g,"%d",minim);
    fclose(f);
    fclose(g);
    return 0;
}
