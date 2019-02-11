#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#define Nmax 100002
#define ll long long
using namespace std;

ifstream f("fft2d.in");
ofstream g("fft2d.out");

ll F,T,lst,nr,MX,val;
ll ans;

struct negru{
    int h,x;
    int NX;
}v[Nmax];

bool comp(negru a,negru b){return (a.h==b.h ? a.x<b.x : a.h<b.h);}

struct trie{
    trie *L,*R;
    ll nr;
    trie(){
        L = R = 0;
        nr = 0;
    }
};

unordered_map<ll, trie*> Root[31];

void add(trie *nod,int x,ll val){
    nod->nr += val;
    for (int i=0;i<F;x/=2,i++){
        if (x%2){
            if (!nod->R) nod->R = new trie();
            nod = nod->R;
        }
        else{
            if (!nod->L) nod->L = new trie();
            nod = nod->L;
        }
        nod->nr += val;
    }
}

ll _find(trie *nod, int x,int fst){
    for (int i=0;i<fst;x/=2,i++)
        if (x%2){
            if (!nod->R) return 0;
            nod = nod->R;
        }
        else{
            if (!nod->L) return 0;
            nod = nod->L;
        }
    return nod->nr;
}

ll getINV(int x){
    ll ans = 0;
    for (int i=1;i<F;i++){
        ans = ans * 2 + x%2;
        x/=2;
    }
    return ans;
}

int main()
{

    f>>F>>T;

    for (int i=1;i<=T;i++) f>>v[i].h>>v[i].x;

    ans = (1LL<<(F-1)) * (1LL<<(F-1));
    MX = (1LL<<(F-1));

    sort(v+1,v+T+1,comp);

    lst = 1;
    for (int ln = 0;ln<F;ln++){
        while (lst<=T && v[lst].h==ln){
            val = MX<<ln;
            ll inv = getINV(v[lst].x);
            for (int k=0;k<ln;k++)
            {
                ll aux = inv & ((1<<k)-1);
                if (Root[k].find(aux)==Root[k].end()) Root[k][aux] = new trie();
                val -= _find(Root[k][aux],v[lst].x,F-ln-1);
            }
            inv = getINV(v[lst].x) & ((1<<ln)-1);
            if (Root[ln].find(inv)==Root[ln].end()) Root[ln][inv] = new trie();
            add(Root[ln][inv],v[lst].x,val);
            ans -= (val>>ln);
            lst++;
        }
    }

    g<<ans;

    return 0;
}

/*g<<"30 100000\n";
    for (int i=0;i<50000;i++){
        g<<4<<' '<<i<<'\n';
    }
    for (int i=50000;i<100000;i++)
        g<<25<<' '<<i<<'\n';

    return 0;*/
