#include <cstdio>
#include <algorithm>

using namespace std;

FILE *f = fopen("blackwater.in","r");
FILE *g = fopen("blackwater.out","w");

const int NMAX = 80000;
const int BUCK = 320;
int n;
int v[NMAX + 5];
long long mars[NMAX + 5];

void apply(int l,int r,int val){
    l = (l - 1) % n + 1;
    r = (r - 1) % n + 1;
    
    if(r < l){
        apply(l,n,val);
        apply(1,r,val);
        return ;
    }

    mars[l] += val;
    mars[r + 1] -= val;
}

void do_mars(){
    for(int i = 1;i <= n;i++){
        mars[i] += mars[i - 1];
    }
}

const int LEN = 1 << 12;
char buff[LEN];
int ind = LEN - 1;

int i32(){
    int ans = 0;

    while(buff[ind] < '0' || buff[ind] > '9'){
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }

    while('0' <= buff[ind] && buff[ind] <= '9'){
        ans = ans * 10 + buff[ind] - '0';
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }
    return ans;
}

int main(){

    n = i32();

    for(int i = 1;i <= n;i++){
        v[i] = i32();
    }

    reverse(v + 1,v + 1 + n);

    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= BUCK && j <= n;j++){
            if(v[i] / j <= BUCK){
                break;
            }
            apply(i + j - 1,i + j - 1,v[i] / j);
        }
        for(int j = 1;j <= BUCK;j++){
            int l = v[i] / (j + 1) + 1;
            int r = min(n,v[i] / j);
            if(l > r){
                continue;
            }
            apply(i + l - 1,i + r - 1,j);
        }
    }

    do_mars();

    long long ans = 0;

    for(int i = 1;i <= n;i++){
        ans = max(ans,mars[i]);
    }

    fprintf(g,"%lld\n",ans);

    fclose(f);
    fclose(g);

    return 0;
}
