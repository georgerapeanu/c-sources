#include <bits/stdc++.h>

using namespace std;

const long long BUCK = 1e5;

long long t;
long long a,b,p,q;
pair<long long,long long> vals[BUCK + 5];

long long get_dist(int r,int t,int mod){
    return min(abs(r - t),mod - abs(r - t));
}

int main(){

    cin >> t;

    while(t--){
        cin >> a >> b >> p >> q;
        long long best = a,dist = 1e9;
        while((b - a + 1) % BUCK != 0){
            long long ndist = get_dist(((2LL * p * b) % (2 * q)),q,2 * q);
            if(dist >= ndist){
                dist = ndist;
                best = b;
            }
            b--;
        } 

        if(a < b){
            for(long long i = a;i < a + BUCK;i++){
                vals[i - a + 1].first = (2LL * p * i) % (2 * q);
                vals[i - a + 1].second = i - a;
            }

            sort(vals + 1,vals + 1 + BUCK);

            long long n = 1;

            for(long long i = 2;i <= BUCK;i++){
                if(vals[n].first != vals[i].first){
                    vals[++n] = vals[i];
                }
            }

            vals[0] = vals[n];
            vals[n + 1] = vals[1];

            long long target = q;
            while(a < b){
                
                long long st = 0,dr = n + 1;
                while(dr - st > 1){
                    long long mid = (st + dr) / 2;
                    if(vals[mid].first < target){
                        st = mid;
                    }
                    else{
                        dr = mid;
                    }
                }

                long long cost_a = get_dist(vals[st].first,target,2 * q);
                long long ind_a = a + vals[st].second;
                long long cost_b = get_dist(vals[dr].first,target,2 * q);
                long long ind_b = a + vals[dr].second;

                if(dist > cost_a || (dist == cost_a && ind_a < best)){
                    best = ind_a;
                    dist = cost_a;
                }

                if(dist > cost_b || (dist == cost_b && ind_b < best)){
                    best = ind_b;
                    dist = cost_b;
                }
                
                target = ((target - 2LL * p * BUCK) % (2 * q)) + 2 * q;
                target %= (2 * q);
                a += BUCK;
            }
        }
        cout << best << "\n";
    }


    return 0;
}
