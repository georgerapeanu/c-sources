#include <iostream>
#include <cassert>

using namespace std;

const int NMAX = 350;
const int MOD = 1e9 + 7;

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

int p;
string s;
int ind = 0;
int l[NMAX + 5];
int r[NMAX + 5];
int catalan[NMAX + 5];
char type[NMAX + 5];
int args[NMAX + 5];

pair<int,int> dfs(){
    int id = ind;
    if(s[ind] == '*'){
        ind++;
        l[id] = -1;
        r[id] = -1;
        type[id] = '*';
        args[id] = 0;
        return {1,1};
    }
    char op = s[ind++];
    int wh = 0;

    while('0' <= s[ind] && s[ind] <= '9'){
        wh = wh * 10 + s[ind] - '0';
        ind++;
    }

    type[id] = op;
    args[id] = wh;
    l[id] = ind;
    pair<int,int> a = dfs();
    r[id] = ind;
    pair<int,int> b = dfs();

    pair<int,int> ans;

    if(op == 'H'){
        ans.first = max(a.first,wh) + max(1,b.first);
        ans.second = max(a.second,b.second);
    }else{
        ans.first = max(a.first,b.first);
        ans.second = max(wh,a.second) + max(1,b.second);
    }

    return ans;
}

pair<int,int> dfs2(int nod){
    if(type[nod] == '*'){
        return {1,1};
    }

    pair<int,int> ans = {1,1};
    pair<int,int> a = dfs2(l[nod]);
    pair<int,int> b = dfs2(r[nod]);

    if(type[l[nod]] != type[nod]){
        a.first = mult(a.first,catalan[a.second]);
        a.second = 0;
    }
    ans.first = mult(ans.first,a.first);
    ans.second = add(ans.second,a.second);
    
    if(type[r[nod]] != type[nod]){
        b.first = mult(b.first,catalan[b.second]);
        b.second = 0;
    }
    ans.first = mult(ans.first,b.first);
    ans.second = add(ans.second,b.second);

    return ans;
}

void dfs3(int nod){
    if(type[nod] == '*'){
        cout << "*";
        return ;
    }
    while(type[l[nod]] == type[nod]){
        int nod_l = l[nod];
        int nod_r = r[nod];
        int l_l = l[l[nod]];
        int l_r = r[l[nod]];

        l[nod] = l_r;
        r[nod_l] = nod;
        args[nod] -= args[nod_l];
        nod = nod_l;
    }

    cout << type[nod] << args[nod];

    dfs3(l[nod]);
    dfs3(r[nod]);
}

int main(){

    catalan[0] = 1;
    catalan[1] = 1;

    for(int i = 2;i <= NMAX;i++){
        for(int j = 1;j <= i;j++){
            catalan[i] = add(catalan[i],mult(catalan[j - 1],catalan[i - j]));
        }
    }

    cin >> p;
    cin >> s;

    if(p == 1){
        int cnt = 1;

        for(auto it:s){
            if(it == 'H' || it == 'V'){
                cnt++;
            }
        }

        cout << cnt << "\n";
    }else if(p == 2){
        pair<int,int> ans = dfs();
        cout << ans.first << " " << ans.second << "\n";
    }else if(p == 3){
        dfs();
        pair<int,int> ans = dfs2(0);    
        ans.first = mult(ans.first,catalan[ans.second]);
        ans.second = 0;
        cout << ans.first << "\n";
    }else{
        dfs();
        dfs3(0);
    }

    return 0;
}
