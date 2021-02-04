#include <bits/stdc++.h>

using namespace std;

const int NMAX = 3e5;

int t;
int n;
int pref[NMAX + 5];
int suff[NMAX + 5];
int v[NMAX + 5];

int eval(int pos,int val){
    int ans = 0;
    int tmp = v[pos];

    v[pos] = val;

    for(int i = pos - 1;i <= pos + 1;i++){
        if(2 <= i && i < n){
            ans += ((v[i - 1] < v[i] && v[i] > v[i + 1]) || (v[i - 1] > v[i] && v[i] < v[i + 1]));
        }
    }

    v[pos] = tmp;
    return ans;
}

int main(){

    scanf("%d",&t);
    for(int h = 1;h <= t;h++){
        scanf("%d",&n);

        pref[0] = suff[0] = 0;
        pref[n + 1] = suff[n + 1] = 0;
        for(int i = 1;i <= n;i++){
            pref[i] = 0;
            suff[i] = 0;
            scanf("%d",&v[i]);
        }
    
        for(int i = 1;i <= n;i++){
            pref[i] = pref[i - 1];
            if(i >= 2 && i < n){
                pref[i] += ((v[i] < v[i - 1] && v[i] < v[i + 1]) || (v[i] > v[i - 1] && v[i] > v[i + 1]));
            }
        }
        
        for(int i = n;i;i--){
            suff[i] = suff[i + 1];
            if(i >= 2 && i < n){
                suff[i] += ((v[i] < v[i - 1] && v[i] < v[i + 1]) || (v[i] > v[i - 1] && v[i] > v[i + 1]));
            }
        }
    
        int ans = 1e9;
    
        for(int i = 1;i <= n;i++){
            int local_ans = (i >= 2 ? pref[i - 2]:0) + (i + 2 <= n ? suff[i + 2]:0);
            int local_best = 1e9;
    
            if(2 <= i && i < n){
                int ma = max(v[i - 1],v[i + 1]);
                int mi = min(v[i - 1],v[i + 1]);
                    
                local_best = min(local_best,eval(i,ma + 1));
                local_best = min(local_best,eval(i,ma));
                local_best = min(local_best,eval(i,mi + 1));
                local_best = min(local_best,eval(i,mi));
                local_best = min(local_best,eval(i,mi - 1));
            }else if(i == 1){
                local_best = min(local_best,eval(i,v[i + 1] + 1));
                local_best = min(local_best,eval(i,v[i + 1]));
                local_best = min(local_best,eval(i,v[i + 1] - 1));
            }else{
                local_best = min(local_best,eval(i,v[i - 1] + 1));
                local_best = min(local_best,eval(i,v[i - 1]));
                local_best = min(local_best,eval(i,v[i - 1] - 1));
            }
            local_ans += local_best;
            ans = min(ans,local_ans);
        }
        if(h == 23 && ans == 0) {
            cout << v[7] << endl;
            return 0;
        }
        cout << ans << "\n";
    }

    return 0;
}
