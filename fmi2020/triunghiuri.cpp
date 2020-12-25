#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

FILE *f = fopen("triunghiuri.in","r");
FILE *g = fopen("triunghiuri.out","w");

const int LEN = 1 << 12;
char buff[LEN];
int ind = LEN - 1;

int i32(){
    int ans = 0;
    int sgn = 1;


    while((buff[ind] < '0' || buff[ind] > '9') && buff[ind] != '-'){
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }
    
    if(buff[ind] == '-'){
        sgn *= -1;
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
    return ans * sgn;
}
int det_mod2(int xa,int ya,int xb,int yb,int xc,int yc){
    return abs((xa - xc) * (yb - yc) - (ya - yc) * (xb - xc)) % 2;
}

int fr[2][2];

bool valid[1 << 6];

long long comb(int n,int k){
    if(k < 0 || k > n){
        return 0;
    }

    long long ans = 1;

    for(int i = n - k + 1;i <= n;i++){
        ans *= i;
    }

    for(int i = 1;i <= k;i++){
        ans /= i;
    }

    return ans;
}

long long solve(){
    long long ans = 0;
    for(int conf = 0;conf < (1 << 6);conf++){
        if(valid[conf] == false){
            continue;
        }

        vector<pair<pair<int,int>,int>> coords;
        
        for(int k = 0;k < 6;k += 2){
            coords.push_back({{(conf >> k) & 1,(conf >> (k + 1)) & 1},1});
        }

        vector<pair<pair<int,int>,int> > stuff;

        for(int i = 0;i < (int)coords.size();i++){
            if(stuff.empty() || stuff.back().first != coords[i].first){
                stuff.push_back(coords[i]);
            }
            else{
                stuff.back().second += coords[i].second;
            }
        }

        long long local_ans = 1;

        for(auto it:stuff){
            local_ans *= comb(fr[it.first.first][it.first.second],it.second);
        }

        ans += local_ans;
    }

    return ans;
}

int main(){
    for(int conf = 0;conf < (1 << 6);conf++){
        vector<int> coords;
        
        for(int k = 0;k < 6;k++){
            coords.push_back((conf >> k) & 1);
        }

        if(make_pair(coords[0],coords[1]) > make_pair(coords[2],coords[3]) || make_pair(coords[2],coords[3]) > make_pair(coords[4],coords[5])){
            continue;
        }

        if(det_mod2(coords[0],coords[1],coords[2],coords[3],coords[4],coords[5]) == 0){
            valid[conf] = 1;
        }
        
    }
       
    int n,q;

    n = i32();
    q = i32();

    for(int i = 1;i <= n;i++){
        int x,y;
        x = abs(i32()) % 2;
        y = abs(i32()) % 2;
       
        fr[x][y]++;
    }

    fprintf(g,"%lld\n",solve());

    while(q--){
        int t,x,y;
        t = i32();
        x = abs(i32()) % 2;
        y = abs(i32()) % 2;
        if(t == 1){
            fr[x][y]++;
        }
        else{
            fr[x][y]--;
        }
        fprintf(g,"%lld\n",solve());
    }
   
    fclose(f);
    fclose(g);

    return 0;
}
