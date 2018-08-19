/*
probabilitatea ca biletul i sa fie ales este P[i]/S
deci probabilitatea de castig = Pi*Pj*(gcd(V[i],V[j])==1)
adica probabilitarea de a alege i si j si castigam doar daca sunt prime intre ele
sau castig=1-Pi*Pj*(gcd(V[i],V[j])!=1)
deci pentru un element i vrem doar sa stim suma elementelor coprime cu el
ne gandim sa marcam divizorii,dar observam ca daca 2 numere au 2 divizori comuni,o sa scada de doua ori
deci de aici vine principiul includerii si excluderii
la un numar ma intereseaza daca are divizorul div,nu de cate ori il are,deci e ok sa generezi divizorii cu exp cel mult 1
deci intai descompunem fiecare V[i] si ii marcam divizorii conform principiului includerii si excluderii cu D[i]
iar la contruirea solutiei descompunem si adunam divizorii
*/
#include <vector>
#include <cstdio>
#define VMAX 500005
#define NMAX 100005
using namespace std;
FILE *f=fopen("porcjoc.in","r");
FILE *g=fopen("porcjoc.out","w");
long long S;
int D[NMAX];
int V[VMAX];
int div[VMAX];
int N;
int atins[VMAX];
long long ceva[VMAX];
long long gcd(long long a,long long b)
{
    if(!b) return a;
    return gcd(b,a%b);
}
vector<pair<int,int> > divizori(int val)///descompunerea lui val in divizori cu exponentul cel mult 1
{
    vector <int> primes;
    vector<pair<int,int> >rez;
    int lprime=0;
    while(val>1)
    {
        if(lprime!=div[val]){lprime=div[val];primes.push_back(lprime);}
        val/=lprime;
    }
    for(int conf=(1<<primes.size())-1;conf>=0;conf--)
    {
        int r=1,op=0;
        for(int i=primes.size()-1;i>=0;i--)
        {
            if(conf&(1<<i))
            {r*=primes[i];op^=1;}
        }
        rez.push_back(make_pair(r,op));
    }
    return rez;
}
int main()
{
    for(int i=2;i*i<VMAX;i++)///div[i]=cel mai mic nr prim cu care se divide i.folosit in descompunere
    {
        if(div[i]!=0){continue;}
        for(int j=i*i;j<VMAX;j+=i)
            if(div[j]==0)
                div[j]=i;
    }
    for(int i=2;i<VMAX;i++) if(!div[i])div[i]=i;
    fscanf(f,"%d",&N);
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d%d",&V[i],&D[i]);
        vector<pair<int,int> > a=divizori(V[i]);
        int op[]={1,-1};
        for(auto it:a)
        {
            ceva[it.first]+=op[it.second]*D[i];
        }
    }
    long long numa=0,numi=0,simp;
    for(int i=1;i<=N;i++)
    {
        numi+=D[i];
        long long tmp=0;
        vector<pair<int,int> > a=divizori(V[i]);
        for(auto it:a)
            tmp+=ceva[it.first];
        numa+=tmp*D[i];
    }
    numi*=numi;
    fprintf(g,"%lld/%lld",numa/gcd(numa,numi),numi/gcd(numa,numi));
    fclose(f);
    fclose(g);
    return 0;
}
