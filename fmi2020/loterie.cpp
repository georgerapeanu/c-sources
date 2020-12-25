#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

FILE *f = fopen("loterie.in","r");
FILE *g = fopen("loterie.out","w");

const int VMAX = 50000;

int q;
int phi[VMAX + 5];
long long pref[VMAX + 5];

const int LEN = 1 << 12;
char buff[LEN];
int ind = LEN - 1;

int gcd(int a,int b){
    if(b == 0){
        return a;
    }
    return gcd(b,a % b);
}

int i32(){
    int ans = 0;
    
    while(buff[ind] < '0' || buff[ind] > '9'){
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }
    
    while(!(buff[ind] < '0' || buff[ind] > '9')){
        ans = ans * 10 + (buff[ind] - '0');
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }
    return ans;
}

vector<pair<int,int> > query[105];
long long ans[100005];

int main(){

    for(int i = 2;i <= VMAX;i++){
        phi[i] = i;
    }

    for(int i = 2;i <= VMAX;i++){
        if(phi[i] == i){
            for(int j = i;j <= VMAX;j += i){
                phi[j] = (phi[j] / i) * (i - 1);
            }
        }
    }

    for(int i = 1;i <= VMAX;i++){
        pref[i] = pref[i - 1] + phi[i];
    }

    q = i32();

    for(int i = 1;i <= q;i++){
        int a,b;
        a = i32();
        b = i32();
        query[a].push_back({b,i});
    }

    for(int i = 1;i <= 100;i++){
        for(auto it:query[i]){
            ans[it.second] = pref[it.first] - pref[i - 1];
        }
        for(int j = i;j <= VMAX;j++){
            if(gcd(i,j) == 1){
                phi[j]--;
            }
            pref[j] = pref[j - 1] + phi[j];
        }
    }

    for(int i = 1;i <= q;i++){
        fprintf(g,"%d\n",ans[i]);
    }
    
    fclose(f);
    fclose(g);

    return 0;    
}
