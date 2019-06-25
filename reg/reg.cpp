#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

FILE *f = fopen("reg.in","r");
FILE *g = fopen("reg.out","w");

const int NMAX = 2e6;
const int VMAX = 5e5;

int t;
int a,b,c,n,k;
int inva;

bool in[VMAX + 1];
int fr[VMAX + 5];

int lgpow(int b,int e){
    if(b == 0){
        return 0;
    }
    int p = 1;

    while(e){
        if(e & 1){
            p = 1LL * p * b % c;
        }
        b = 1LL * b * b % c;
        e >>= 1;
    }
    
    return p;
}

const int LEN = 1 << 10;
char buff[LEN];
int ind = LEN - 1;

int i32(){
    int ans = 0;
    
    while('0' > buff[ind] || buff[ind] > '9'){
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }

    while('0' <= buff[ind] && buff[ind] <= '9'){
        ans = ans * 10 + (buff[ind] - '0');
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }

    return ans;
}

int main() {

    t = i32();

    while(t--) {

        memset(fr,0,sizeof(fr));
        memset(in,0,sizeof(in));

        a = i32();
        b = i32();
        c = i32();
        n = i32();
        k = i32();

        a %= c;
        b %= c;

        inva = lgpow(a,c - 2);

        int st = 1,dr = n;
        int fst = 1,lst = 1;
        int sz = 0;

        fr[1]++;

        for(int i = 2;i <= n;i++){
            lst = (1LL * lst * a + 1LL * b * i) % c;
            fr[lst]++;
        }

        int ans = 1;
        bool cas = a;

        while(st <= dr){
            if(in[fst] == false){
                if(sz < k){
                    in[fst] = true;
                    sz++;
                }
                else{
                    bool found = false;
                    while(st <= dr && found == false){
                        fr[lst]--;
                        if(in[lst] == true && fr[lst] == 0){
                            in[fst] = true;
                            in[lst] = false;
                            found = true;
                        }
                        if(cas){
                            lst = 1LL * (lst - (1LL * b * dr) % c + c) * inva % c;
                        }
                        else{
                            lst = 1LL * b * (dr - 1) % c;
                        }
                        dr--;
                    }
                }
            }
            
            if(st <= dr){
                ans = st;
            }
            fr[fst]--;
            if(fr[fst] == 0){
                sz--;
                in[fst] = false;
            }
            
            st++;
            fst = (1LL * fst * a + 1LL * st * b) % c;
        }

        fprintf(g,"%d\n",ans);
    }

    fclose(f);
    fclose(g);

    return 0;
}
