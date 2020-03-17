#include <iostream>

using namespace std;


const int BUCK = 1e4;
const int NMAX = 5e3;

int n,m;
int k,q;
int d[NMAX + 5];
int dp[NMAX + 5];
long long p[NMAX + 5];
long long sum;

long long get_val(long long pos){
    return (p[pos % k] + sum * (pos / k)) % m;
}

int main(){

    cin >> k >> q;

    for(int i = 1;i <= k;i++){
        cin >> d[i];
    }

    while(q--){
        cin >> n >> d[0] >> m;

        n--;

        p[0] = d[0] % m;
        dp[0] = d[0] % m;

        for(int i = 1;i <= k;i++){
            dp[i] = d[i] % m;
            p[i] = dp[i] + p[i - 1];
            p[i] %= m;
        }

        sum = (m + p[k] - p[0]) % m;

        if(m <= BUCK){
            //periodic m * k
            long long ans = 0;
            for(int i = 0;i < m * k && i < n;i++){
                if(get_val(i) < get_val(i + 1)){
                    ans += (n - i - 1) / (m * k) + 1;
                }
            }
            cout << ans << "\n";
        }
        else{
            //few multiples

            long long ans = 0;

            for(int jp = 0;jp < k;jp++){
                if(sum == 0){
                    ans += 1LL * (get_val(jp) < m - dp[jp + 1] && dp[jp + 1] % m != 0) * ((n - 1 - jp) / k + 1);
                    continue;
                }
                if(dp[jp + 1] == 0){
                    continue;
                }
                for(long long mult = 0;;mult += m){
                    long long fst = max(0LL,(mult - p[jp] + (sum - 1)) / sum);///inclusive
                    long long snd = (mult + m - p[jp] - dp[jp + 1] + (sum - 1)) / sum;///exclusive
                    //cout << ans << " " << jp << " " << mult << " " << fst << " " << snd << " (" << sum << " " << (mult + m - p[jp] - dp[jp + 1])<< ")\n";
                    if(1LL * fst * k + jp >= n){
                        break;
                    }

                    snd = min(snd,(n - 1 - jp) / k + 1LL);

                    //cout << "devine " << ans << " " << jp << " " << mult << " " << fst << " " << snd << " (" << sum << " " << (mult + m - p[jp] - dp[jp + 1] + (sum - 1)) / sum << ")\n";

                    ans += snd - fst;
                }
            }
            cout << ans << "\n";
        }
    }

    return 0;
}
