#include <bits/stdc++.h>

using namespace std;

const int NMAX = 3e5;
const int LMAX = 3e5;
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

int lgpow(int b,int e){
    int p = 1;

    while(e){
        if(e & 1){
            p = mult(p,b);
        }
        b = mult(b,b);
        e >>= 1;
    }
    return p;
}


int n,m,k;
int dp[LMAX + 5];
int pw[LMAX + 5];
int i_pw[LMAX + 5];
int fr[LMAX + 5];
int delta[LMAX + 5];
int prefix_ban[LMAX + 5];
string s;

struct node_t{
    node_t* son[26];
    bool leaf;

    node_t(){
        memset(son,0,sizeof(son));
        leaf = false;
    }
};

void add(node_t *root,int pos,const string &s){
    if(pos >= (int)s.size()){
        root->leaf = true;
        return ;
    }

    int c = s[pos] - 'a';

    if(root->son[c] == NULL){
        root->son[c] = new node_t();
    }

    add(root->son[c],pos + 1,s);
}

void process(node_t *root,int length){
    prefix_ban[length] = add(prefix_ban[length],1);
    dp[length] = scad(dp[length],1);
    if(root->leaf == true){
        delta[length + 1] = add(delta[length + 1],k);
//        for(int j = length + 1;j <= LMAX;j++){
//            dp[j] = scad(dp[j],pw[j - length]);
//        }
        return ;
    }
    for(int i = 0;i < k;i++){
        if(root->son[i] != NULL){
            process(root->son[i],length + 1);
        }
    }
}

int main(){
    
    cin >> n >> m >> k;

    dp[0] = pw[0] = 1;
    i_pw[0] = 1;
    int inv_k = lgpow(k,MOD - 2);

    for(int i = 1;i <= LMAX;i++){
        pw[i] = mult(pw[i - 1],k);
        i_pw[i] = mult(i_pw[i - 1],inv_k);
        dp[i] = pw[i];
    }

    node_t* root = new node_t();

    for(int i = 1;i <= n;i++){
        cin >> s;
        add(root,0,s);
    }

    process(root,0);

    for(int i = 1;i <= m;i++){
        int value;
        cin >> value;
        fr[value]++;
    }

    int ans = 1;
    int current_mult = 1;

    for(int l = 1;l <= LMAX;l++){
        current_mult = scad(current_mult,mult(delta[l],i_pw[l]));
        while(fr[l] > 0){
            fr[l]--;
            ans = mult(ans,scad(mult(pw[l],current_mult),prefix_ban[l]));
//            ans = mult(ans,dp[l]);
//            for(int j = l;j <= LMAX;j++){
//                dp[j] = scad(dp[j],pw[j - l]);
//            }
            prefix_ban[l] = add(prefix_ban[l],1);
            delta[l + 1] = add(delta[l + 1],k);
        }
    }

    printf("%d\n",ans);

    return 0;
}
