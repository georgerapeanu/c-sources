#include <iostream>
#include <cstdio>
#include <stack>
#define MOD 666013
using namespace std;
int cul[100006];
char C[100006];
int nr=0,N,M;
int ind=1;
/*
reprezinti ca arbore
incepi de la dinamici proaste
d1[nod][c1][c2]-colorarea subarborelui nod astfel incat prima paranteza e c1,ultima e c2
d2[fiu][c1][c2]-colorarea fiilor lui nod pana la nodul fiu,prima paranteza a primului fiu e c1,ultima e c2
apoi observi ca se repeta valori,si anume o sa obtii 2 valori diferite:
daca ultima paranteza a fiului e colorata la fel cu prima a tatalui
si daca nu
d1[fiu][c1][c2] e constant
d2[fiu][0]-numarul de variante daca c2!=culoare tata(dinamica veche)
ies recurentele destul de smecher
*/
int dfs()
{
    if(C[ind]==')')
    {
        ind++;
        return 1;
    }
    int d1=0,d2[]={0,1},nd2[2];
    while(C[ind]!=')')
    {
        ind++;
        int tmp=dfs();
        nd2[0]=(1LL*tmp*((1LL*(M-2)*((d2[1]+1LL*d2[0]*(M-2)))%MOD)+1LL*(M-1)*d2[0])%MOD)%MOD;
        nd2[1]=(((1LL*((1LL*d2[1]+1LL*d2[0]*(M-2))%MOD)*tmp)%MOD)*(M-1))%MOD;
        d2[0]=nd2[0];
        d2[1]=nd2[1];
    }
    d1=(d2[1]+1LL*d2[0]*(M-2))%MOD;
    ind++;
    return d1;
}
int main()
{
    freopen("spirt.in","r",stdin);
    freopen("spirt.out","w",stdout);
    cin>>N>>M;
    cin.getline(C+1,1000006);
    cin.getline(C+1,1000006);
    int rez=1;
    ind=1;
    bool fst=1;
    while(ind<=N)
    {
        ind++;
        int tmp=dfs();
        rez=(1LL*((1LL*(1LL*(M-(!fst))*(M-1)%MOD)*tmp)%MOD)*rez)%MOD;
        fst=0;
    }
    cout<<rez;
    return 0;
}
