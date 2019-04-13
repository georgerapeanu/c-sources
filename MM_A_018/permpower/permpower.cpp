#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

FILE *f = fopen("permpower.in","r");
FILE *g = fopen("permpower.out","w");

const int NMAX = 1e6;

int n;
int p[NMAX + 5];
int q[NMAX + 5];

bool viz[NMAX + 5];

int rest[NMAX + 5];

bool is_not_prime[NMAX + 5];
pair<int,int> most[NMAX + 5];

unsigned long long add(unsigned long long a,unsigned long long b,unsigned long long MOD){
    if(a >= MOD -  b){
        a = a - (MOD - b);
    }
    else{
        a = a + b;
    }

    return a;
}

unsigned long long mult(unsigned long long a,unsigned long long b,unsigned long long MOD){
    unsigned long long ans = 0;
    while(a){
        if(a & 1){
            ans = add(ans,b,MOD);
        }
        a >>= 1;
        b = add(b,b,MOD);
    }
    return ans;
}

unsigned long long lgpow(unsigned long long b,unsigned long long e,unsigned long long MOD){
    unsigned long long p = 1;

    while(e){
        if(e & 1){
            p = mult(p,b,MOD);
        }
        b = mult(b,b,MOD);
        e >>= 1;
    }

    return p;
}

int main(){
    fscanf(f,"%d",&n);

    for(int i = 1;i <= n;i++){
        rest[i] = -1;
        fscanf(f,"%d",&p[i]);
    }

    for(int i = 1;i <= n;i++){
        fscanf(f,"%d",&q[i]);
    }

    for(int i = 1;i <= n;i++){
        if(viz[i] == true){
            continue;
        }

        int k = 0,nod = i;

        while(p[nod] != q[i]){
            nod = p[nod];
            k++;
        }

        int len = 0;
        nod = i;
        while(viz[nod] == false){
            viz[nod] = true;
            nod = p[nod];
            len++;
        }

        rest[len] = (k + 1) % len;
    }

    vector<pair<unsigned long long,unsigned long long> > tcr;
    vector<unsigned long long> phi;
    for(int i = 2;i <= n;i++){
        if(is_not_prime[i] == false){
            pair<unsigned long long,unsigned long long> ans = {1,0};
            for(int j = i;j <= n;j += i){
                is_not_prime[j] = true;
                if(rest[j] != -1){
                    int cj = j;
                    int num = 1;
                    while(cj % i == 0){
                        cj /= i;
                        num *= i;
                    }
                    ans = max(ans,{num,rest[j]});
                }
            }
            if(ans.first != 1){
                tcr.push_back(ans);
                phi.push_back(ans.first / i * (i - 1));
            }
        }
    }

    unsigned long long P = 1;
    vector<unsigned long long> pref(tcr.size());
    vector<unsigned long long> suff(tcr.size());

    for(int i = 0;i < (int)tcr.size();i++){
        pref[i] = tcr[i].first;
        if(i > 0){
            pref[i] = pref[i - 1] * tcr[i].first;
        }
    }

    for(int i = (int)tcr.size() - 1;i >= 0;i--){
        suff[i] = tcr[i].first;
        if(i < (int)tcr.size() - 1){
            suff[i] = suff[i + 1] * tcr[i].first;
        }
    }

    P = suff[0];

    unsigned long long ans = 0;

    for(int k = 0;k < (int)tcr.size();k++){
        if(tcr[k].first == 1){
            continue;
        }
        unsigned long long pi = 1;
        if(k > 0){
            pi = mult(pi,pref[k - 1],P);
        }
        if(k < (int)tcr.size() - 1){
            pi = mult(pi,suff[k + 1],P);
        }
        unsigned long long a = tcr[k].second;
        unsigned long long b = lgpow(pi % tcr[k].first,phi[k] - 1,tcr[k].first);
        unsigned long long c = mult(pi,b,P);
        unsigned long long d = mult(c,a,P);
        ans = add(ans,d,P);
    }

    if(ans == 0){
        ans = P;
    }

    fprintf(g,"%llu\n",ans);

    fclose(f);
    fclose(g);

    return 0;
}
