#include <cstdio>
#define zeros(x) x&(x^(x-1))
using namespace std;
FILE *f=fopen("costperm.in","r");
FILE *g=fopen("costperm.out","w");
int N;
long long rez,sumaelemdr;
long long AIB[100005];///AIB[i]-suma elementelor care au aparut deja in intervalul i-zeros(i)+1,i
int V[100005];
/*
sa zicem ca avem configuratie x....N....y
este evident ca N va face swap cu toti din dreapta sa pentru a ajunge la pozitia lui
acum putem lua configuratie fara N,si tot asa
ajungem la concluzia ca pentru un element,costul minim va fi egal cu suma elementelor mai mici decat el din dreapta sa,deoarece va face evident swap cu ele
folosim AIB pentru complexitate
*/
void update(int poz,int val)
{
    for(int i=poz;i<=N;i+=zeros(i))
        AIB[i]+=val;
}
long long querry(int poz)
{
    long long sum=0;
    for(int i=poz;i;i-=zeros(i))
        sum+=AIB[i];
    return sum;
}
int main()
{
    fscanf(f,"%d",&N);
    for(int i=1;i<=N;i++)
        fscanf(f,"%d",&V[i]);
    for(int i=N;i>0;i--)
    {
        long long sumaelemmaimari=querry(N)-querry(V[i]);
        rez+=sumaelemdr-sumaelemmaimari;
        sumaelemdr+=V[i];
        update(V[i],V[i]);
    }
    fprintf(g,"%lld",rez);
    return 0;
}
