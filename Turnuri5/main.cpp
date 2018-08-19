#include <cstdio>
#include <cassert>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;
FILE *f = fopen("turnuri5.in","r");
FILE *g = fopen("turnuri5.out","w");
int N,M,T;
struct turnul{
    int h,l,r;
    vector<pair<int,int> > tmp;
    bool operator < (const turnul &other)const{
        if(h != other.h){
            return h < other.h;
        }
        return l < other.l;
    }
}V[100005];
const int MOD = (1e9) + 7;
int add(int a,int b){
    a += b;
    if(a >= MOD){
        a -= MOD;
    }
    return a;
}
int mult(int a,int b){
    return 1LL * a * b % MOD;
}
int base;///recalc base to mean num of ways of choosing the base
set<pair<int,int> > S;
int C(int N,int K){
    int a = N;
    int b = N - 1;
    if(a % 2){
        b /= 2;
    }
    else{
        a /= 2;
    }
    return mult(a,b);
}
bool cmp(turnul a,turnul b){
    if(a.l == b.l){
        assert(false);
    }
    return a.l < b.l;
}
int main(){
    fscanf(f,"%d %d %d",&N,&M,&T);
    base = 0;
    V[0].h = -1;
    V[0].l = -1;
    V[0].r = -1;
    for(int i = 1;i <= T;i++){
        fscanf(f,"%d %d %d",&V[i].h,&V[i].l,&V[i].r);
    }
    V[++T] = {N - 1,M,M};
    sort(V + 1,V + 1 + T,cmp);
    for(int i = 1;i <= T;i++){
        if(V[i - 1].r + 1 <= V[i].l - 1){
            S.insert({V[i - 1].r + 1,V[i].l - 1});
            base = add(base,C(V[i].l - 1 - V[i - 1].r,2));
        }
    }
    sort(V + 1,V + T);
    int len = 0;
    for(int i = 1;i <= T;i++){
        if(V[len].h != V[i].h){
            len++;
            V[len].h = V[i].h;
            V[len].l = V[i].l;
            V[len].r = V[i].r;
            V[len].tmp.clear();
        }
        V[len].tmp.push_back(make_pair(V[i].l,V[i].r));
    }
    T = len;///(i-1,i]
    int rez = 0;
    N--;
    for(int i = 1;i <= T;i++){
        int ceva = 2 * N - V[i].h - V[i - 1].h - 1;
        if(ceva % 2 == 0){
            ceva /= 2;
            ceva = mult(ceva,V[i].h - V[i - 1].h);
        }
        else{
            ceva = mult(ceva,(V[i].h - V[i - 1].h) / 2);
        }
        rez = add(rez,mult(base,ceva));
        set<pair<int,int> > :: iterator it;
        for(auto it2:V[i].tmp){
            int l = it2.first;
            int r = it2.second;
            base = add(base,C(r - l + 1,2));
            it = S.lower_bound({l,0});
            bool ins1 = 0;
            if(it != S.end() && it -> first == r + 1){
                pair<int,int> dada = {l,it -> second};
                base = add(base,mult(r - l + 1,it -> second - it -> first + 1));
                S.erase(it);
                S.insert(dada);
                r = dada.second;
                ins1 = 1;
            }
            it = S.lower_bound({l,0});
            bool ins2 = 0;
            if(it != S.begin()){
                it--;
                if(it -> second + 1 == l){
                     pair<int,int> dada = {it -> first,r};
                    base = add(base,mult(r - l + 1,it -> second - it -> first + 1));
                    S.erase(it);
                    if(ins1){
                        S.erase(make_pair(l,r));
                    }
                    S.insert(dada);
                    ins2 = 1;
                }
            }
            if(!ins1 && !ins2){
                S.insert(make_pair(l,r));
            }
        }
    }
    fprintf(g,"%d",rez);
    fclose(f);
    fclose(g);
    return 0;
}
