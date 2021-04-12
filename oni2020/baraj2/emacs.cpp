#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 3e5;
const int LGMAX = 18;///TODO check this

const int MOD = 1e9 + 7;

int add(int a,int b){
    a += b;
    if(a >= MOD){
        a -= MOD;
    }
    return a;
}

int scad(int a,int b){
    a -= b;
    if(a < 0){
        a += MOD;
    }
    return a;
}

int mult(int a,int b){
    return 1LL * a * b % MOD;
}

int n;
int e[NMAX + 5];
int rmq[LGMAX + 1][NMAX + 1];
int lg2[NMAX + 5];
vector<pair<int,int> > stuff;

int get_max(int l,int r){
    int h = lg2[r - l + 1];
    return max(rmq[h][r],rmq[h][l + (1 << h) - 1]);
}

int l[NMAX + 5];
int r[NMAX + 5];
int v[NMAX + 5];
int st[NMAX + 5];
int len;


int eval(const vector<int> &pos){
    if((int)pos.size() <= 1){
        return 0;
    }
    int ans = 0;
    int n = (int)pos.size() - 1;

    for(int i = 1;i <= n;i++){
        v[i] = get_max(pos[i - 1],pos[i]);
    }

    st[len = 0] = 0;
    for(int i = 1;i <= n;i++){
        while(len > 0 && v[st[len]] <= v[i]){
            len--;
        }
        l[i] = st[len]; 
        st[++len] = i;
    }

    st[len = 0] = n + 1;

    for(int i = n;i >= 1;i--){
        while(len > 0 && v[st[len]] < v[i]){
            len--;
        }
        r[i] = st[len];
        st[++len] = i;
    }

    for(int i = 1;i <= n;i++){
        ans = add(ans,mult(v[i],mult(i - l[i],r[i] - i)));
    }

    return ans;
}

int main(){

    for(int i = 2;i <= NMAX;i++){
        lg2[i] = 1 + lg2[i >> 1];
    }

    scanf("%d",&n);

    int ans = 0;

    for(int i = 1;i <= n;i++){
        scanf("%d",&rmq[0][i]);
        ans = add(ans,rmq[0][i]);
    }

    for(int h = 1;h <= LGMAX;h++){
        for(int i = 1;i <= n;i++){
            rmq[h][i] = rmq[h - 1][i];
            if(i >= (1 << (h - 1))){
                rmq[h][i] = max(rmq[h][i],rmq[h - 1][i - (1 << (h - 1))]);
            }
        }
    }

    for(int i = 1;i <= n;i++){
        scanf("%d",&e[i]);
        stuff.push_back({e[i],i});
    }

    sort(stuff.begin(),stuff.end());

    vector<int> pos;

    for(auto it:stuff){
        if(pos.empty() == false && e[pos.back()] != e[it.second]){
            ans = add(ans,eval(pos));
            pos.clear();
        }
        pos.push_back(it.second);
    }

    ans = add(ans,eval(pos));

    printf("%d\n",ans);
    
    return 0;
}
