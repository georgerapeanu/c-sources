#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2e5;
const int MOD = 998244353;

int t;
int n,k;
int aib[NMAX + 5];
int inva[NMAX + 5];
int b[NMAX + 5];

void reset(){
    for(int i = 1;i <= n;i++){
        aib[i] = 0;
    }
}

void update(int pos,int val){
    for(;pos <= n;pos += (-pos) & pos){
        aib[pos] += val;
    }
}

int query(int pos){

    int sum = 0;

    for(;pos;pos -= (-pos) & pos){
        sum += aib[pos];
    }

    return sum;
}

int main(){

    scanf("%d",&t);

    while(t--){
        scanf("%d %d",&n,&k);

        reset();

        for(int i = 1;i <= n;i++){
            int val;
            scanf("%d",&val);
            inva[val] = i;
        }

        set<int> s;
        for(int i = 1;i <= k;i++){
            int val;
            scanf("%d",&val);
            b[i] = inva[val];
            s.insert(b[i]);
        }

        int ans = 1;
        for(int i = 1;i <= k;i++){
            set<int> :: iterator it = s.lower_bound(b[i]);
            int tmp = (b[i] != n) + (b[i] != 1);
            it++;
            if(it != s.end()){
                if(b[i] - query(b[i]) == *it - query(*it) - 1){
                    tmp--;
                }
            }
            it--;
            if(it != s.begin()){
                it--;
                if(b[i] - query(b[i]) == *it - query(*it) + 1){
                    tmp--;
                }
            }
            ans *= tmp;
            if(ans >= MOD){
                ans -= MOD;
            }
            s.erase(b[i]);
            update(b[i],1);
        }
        printf("%d\n",ans);
    }

    return 0;
}
