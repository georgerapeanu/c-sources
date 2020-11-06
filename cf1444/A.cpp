#include <bits/stdc++.h>

using namespace std;

int main(){

    int t;
    cin >> t;
    while(t--){
        
        long long p,q;

        scanf("%lld %lld",&p,&q);

        if(p % q != 0){
            printf("%lld\n",p);
            continue;
        }

        long long ans = 0;
        
        for(int i = 2;1LL * i * i <= q;i++){
            if(q % i == 0){
                int exp = 0;
                while(q % i == 0){
                    q /= i;
                    exp++;
                }
                int exp2 = 0;
                long long tmp_p = p;
                while(tmp_p % i == 0){
                    tmp_p /= i;
                    exp2++;
                }
                tmp_p = p;
                for(int j = exp;j <= exp2;j++){
                    tmp_p /= i;
                }
                ans = max(ans,tmp_p);
            }
        }
            
        if(q != 1){
            int exp = 1;
            int exp2 = 0;
            long long tmp_p = p;
            while(tmp_p % q == 0){
                tmp_p /= q;
                exp2++;
            }
            tmp_p = p;
            for(int j = exp;j <= exp2;j++){
                tmp_p /= q;
            }
            ans = max(ans,tmp_p);
        }
        printf("%lld\n",ans);
    }



    return 0;
}
