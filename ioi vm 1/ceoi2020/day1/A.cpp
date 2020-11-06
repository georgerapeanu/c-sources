#include <cstdio>
#include <cassert>
#include <algorithm>

using namespace std;

const int MOD = 1e9 + 7;
const int inv2 = 5e8 + 4;
const int NMAX = 1e5;
const int DEB = 0;

int sum = 0;
pair<int,int> st[NMAX + 5];
int len;

int n;
int hh[NMAX + 5];
int ww[NMAX + 5];

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

void del(){
    int h1 = st[len - 1].first;
    int h2 = scad(st[len].first,1);
    int val = st[len - 1].second;
    int fst = add(h2,h1);
    int snd = add(scad(h2,h1),1);
    sum = scad(sum,mult(val,mult(inv2,mult(fst,snd))));
    
    len--;
    
    if(DEB){
    printf("deleted\n");
    for(int i = 1;i <= len;i++){
        printf("%d %d\n",st[i].first,st[i].second);
    }
    printf("%d\n",sum);
    }
}

void ins(int h,int x){
    while(st[len].first >= h){
        del();
    }
    int h1 = st[len].first;
    int h2 = scad(h,1);
    int val = st[len].second;
    int fst = add(h2,h1);
    int snd = add(scad(h2,h1),1);
    
    sum = add(sum,mult(val,mult(inv2,mult(fst,snd))));
    
    st[++len] = {h,x};

    if(DEB){
    printf("inserteed %d %d\n",h,x);
    for(int i = 1;i <= len;i++){
        printf("%d %d\n",st[i].first,st[i].second);
    }
    printf("%d\n",sum);
    }
}

int query(int h){
    if(st[len].first > h){
        assert(false);
    }
    int h1 = st[len].first;
    int h2 = h;
    int val = st[len].second;
    int fst = add(h2,h1);
    int snd = add(scad(h2,h1),1);
    if(DEB){
    printf("query %d\n",h);
    for(int i = 1;i <= len;i++){
        printf("%d %d\n",st[i].first,st[i].second);
    }
    printf("%d\n",sum);
    printf("%d\n",add(sum,mult(val,mult(inv2,mult(fst,snd)))));
    }
    return add(sum,mult(val,mult(inv2,mult(fst,snd))));
}

int get_lst(int h){
    for(int i = len;i;i--){
        if(st[i].first <= h){
            return st[i].second;
        }
    }
}

int lst[NMAX + 5];

int main(){

    scanf("%d",&n);

    st[++len] = {0,0};
    int pref_x = 0;
    int ans = 0;
    for(int i = 1;i <= n;i++){
        scanf("%d",&hh[i]);
    }
    for(int i = 1;i <= n;i++){
        scanf("%d",&ww[i]);
    }
    for(int i = 1;i <= n;i++){
        int fst =  add(add(add(pref_x,pref_x),ww[i]),1);
        int snd = ww[i];

        int a = mult(inv2,mult(fst,snd));
        int b = mult(inv2,mult(hh[i],add(hh[i],1)));
        int tmp_ans = mult(a,b);

        while(st[len].first > hh[i]){
            del();         
        }

        tmp_ans = scad(tmp_ans,mult(ww[i],query(hh[i])));

        ans = add(ans,tmp_ans);

        pref_x = add(pref_x,ww[i]);
        ins(hh[i] + 1,pref_x);
    }

    printf("%d\n",ans);

    return 0;
}
