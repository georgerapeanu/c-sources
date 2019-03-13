#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

FILE *f = fopen("eq4.in","r");
FILE *g = fopen("eq4.out","w");

const int NMAX = 1e5;

char c[NMAX + 5];
int last;

int get_sgn(){
    int ans = (c[last] == '-' ? -1:1);
    last++;
    return ans;
}

int get_num(){
    if(c[last] >= 'a' && c[last] <= 'z'){
        return 1;
    }

    int ans = 0;
    while('0' <= c[last] && c[last] <= '9'){
        ans = ans * 10 + (c[last] - '0');
        last++;
    }
    return ans;
}

int get_var(){
    char tmp = c[last];

    if(tmp < 'a' || tmp > 'z'){
        return 0;
    }

    last++;
    return (tmp == 't' ? 4 : tmp - 'x' + 1);
}

int n;
int t;
int coef[10];
int a,b;
long long e;

int main(){

    fscanf(f,"%d\n",&t);
    fgets(c + 1,NMAX + 5,f);
    fscanf(f,"%d %d %lld",&a,&b,&e);

    last = 1;

    n = strlen(c + 1);
    n -= (c[n] == '\n');

    while(last <= n){
        int val = get_sgn() * get_num();
        int vr = get_var();

        coef[vr] += val;
    }

    if(t == 1){
        long long ans = 0;
        for(int i = 0;i < 5;i++){
            ans += coef[i];
        }
        fprintf(g,"%lld\n",ans);
    }
    else{
        vector<pair<long long,int> > fst,snd;

        for(int x = a;x <= b;x++){
            for(int y = a;y <= b;y++){
                fst.push_back({1LL * coef[1] * x + 1LL * coef[2] * y,1});
            }
        }

        for(int z = a;z <= b;z++){
            for(int t = a;t <= b;t++){
                snd.push_back({1LL * coef[3] * z + 1LL * coef[4] * t,1});
            }
        }

        sort(fst.begin(),fst.end());
        sort(snd.begin(),snd.end());

        int last_fst = 0;

        for(int i = 1;i < (int)fst.size();i++){
            if(fst[last_fst].first != fst[i].first){
                last_fst++;
                fst[last_fst] = fst[i];
            }
            else{
                fst[last_fst].second += fst[i].second;
            }
        }

        fst.resize(last_fst + 1);

        int last_snd = 0;

        for(int i = 1;i < (int)snd.size();i++){
            if(snd[last_snd].first != snd[i].first){
                last_snd++;
                snd[last_snd] = snd[i];
            }
            else{
                snd[last_snd].second += snd[i].second;
            }
        }

        snd.resize(last_snd + 1);

        long long ans = 0;
        int j = (int)snd.size() - 1;

        for(int i = 0;i < (int)fst.size();i++){
            while(j >= 0 && fst[i].first + snd[j].first + coef[0] > e){
                j--;
            }

            if(j < 0){
                break;
            }

            if(fst[i].first + snd[j].first + coef[0] == e){
                ans += 1LL * fst[i].second * snd[j].second;
            }
        }

        fprintf(g,"%lld",ans);
    }

    fclose(f);
    fclose(g);

    return 0;
}
