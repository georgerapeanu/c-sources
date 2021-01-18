#include <cstdio>
#include <algorithm>

using namespace std;

FILE *f = fopen("ghemotoace.in","r");
FILE *g = fopen("ghemotoace.out","w");

const int NMAX = 20000;
const int QMAX = 1e6;

int n,t;
int q;
int nrTestCase;

const int LEN = 1 << 12;
char buff[LEN];
int ind = LEN - 1;

int initial_position[NMAX + 5];
int position[NMAX + 5];

pair<int,int> sw[QMAX + 5];

int i32(){
    int ans = 0;

    while(buff[ind] < '0' || buff[ind] > '9'){
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }
    
    while(!(buff[ind] < '0' || buff[ind] > '9')){
        ans = ans * 10 + buff[ind] - '0';
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }

    return ans;
}

unsigned long long pw[NMAX + 5];

int main(){
    
    n = i32();
    t = i32();
    nrTestCase = i32();

    pw[0] = 1;

    for(int i = 1;i <= n;i++){
        pw[i] = 23 * pw[i - 1];
    }

    unsigned long long ans = 0;

    for(int i = 1;i <= n;i++){
        position[i] = i;
        ans += pw[n - i] * i;
    }

    while(t--){
        q = i32();

        for(int i = 1;i <= q;i++){
            sw[i].first = i32();
            sw[i].second = i32();
            initial_position[sw[i].first] = position[sw[i].first];
            initial_position[sw[i].second] = position[sw[i].second];
        }

        for(int i = 1;i <= q;i++){
            ans -= sw[i].first * pw[n - position[sw[i].first]];
            ans -= sw[i].second * pw[n - position[sw[i].second]];
            if(initial_position[sw[i].first] < initial_position[sw[i].second]){
                position[sw[i].first]++;
                position[sw[i].second]--;
            }
            else{
                position[sw[i].first]--;
                position[sw[i].second]++;
            }
            ans += sw[i].first * pw[n - position[sw[i].first]];
            ans += sw[i].second * pw[n - position[sw[i].second]];
        }

        fprintf(g,"%llu\n",ans);
    }

    return 0;
}
