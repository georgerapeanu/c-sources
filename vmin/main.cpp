#include <cstdio>
#include <algorithm>
#define b first
#define ind second
#define LL long long
using namespace std;
/*
ideea este urmatoarea:mai intai ai nevoie de o ordine initiala.
observam ca pentru x=0,functiile vor fi sortate dupa b
facem vectorul V care va avea 2 elemente:b si indicele functiei care l-a avut parametru
apoi vrem sa aflam fiecare functie de unde o sa inceapa sa fie minima
pentru asta folosim un deque,unde stim ca pentru oricare 2 functii consecutive,cea mai din stanga o sa fie minima pana cand cea dea doua incepe sa fie minima(adica in intervalul incepmin[i],incepmin[i+1]-1
acum vrem sa adaugam functia i in  deque,daca posibil
daca in vectorul sortat,functia i are a[V[i].ind] mai mare,atunci din cauza sortarii o sa aia si b[V[i].ind] mai mare,deci nu o sa fie minima
altfel,calculam intersectia ultimei functii din deq cu functia i
din moment ce query-ul e pe numere intregi,nu reala o tinem ca LL si daca da cu rest adunam 1
daca ti<unde incepe functia din deque sa fie minima,ea nu mai este minima nici unde,deci o scoatem si continuam procesul
daca ramanem fara elemente in deque sau functia e mai mare decat unde incepe una sa fie minima,o bagam in deque pe pozitia aia
in incepmin stim acum fiecare functie de unde incepe sa fie minima
queryurile se dau in ordine crescatoare dupa t,deci daca am trecut de un element din deque nu il mai consideram
si incepem cat timp se afla in intervalul acoperit de funcie(presupunand ca merge pana la infinit minima)
si unde e mai mare inceputul ne oprim,functia anterioara fiind raspunsul
*/
FILE *f=fopen("vmin.in","r");
FILE *g=fopen("vmin.out","w");
int N,M,val,ind=1;
LL A[100005],B[100005];
long long rez;
pair<LL,int> V[100005];
int dq[100005];
int st,dr;
LL incepmin[100005];
int main()
{
    fscanf(f,"%d%d",&N,&M);
    for(LL i=1;i<=N;i++)
    {
        fscanf(f,"%lld %lld",&A[i],&B[i]);
        V[i].b=B[i];
        V[i].ind=i;
    }
    sort(V+1,V+1+N);
    incepmin[1]=0;
    st=dr=1;
    dq[st]=V[1].ind;
    for(LL i=2;i<=N;i++)
    {
        int j=V[i].ind,k;
        LL ti;
        if(A[j]>=A[dq[dr]]) continue;
        for(;dr>=st;dr--)
        {
            k=dq[dr];
            ti=(B[j]-B[k])/(A[k]-A[j]);
            if((B[j]-B[k])%(A[k]-A[j])) ti++;
            if(ti>incepmin[dr]) break;
        }
        dr++;
        dq[dr]=j;
        incepmin[dr]=ti;
    }
    for(int i=1;i<=M;i++)
    {
        fscanf(f,"%d",&val);
        for(;st<=dr&&incepmin[st]<=val;st++);
        fprintf(g,"%d ",dq[st-1]);
    }
    fclose(f);
    fclose(g);
    return 0;
}
