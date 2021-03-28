#include <cstdio>

using namespace std;

const int NMAX = 2e5;
const int KMAX = 20;
const int MOD = 1e9 + 7;
int p,t;

int n,k;
int dp1[NMAX + 5];
int dp2[NMAX + 5];

char conf[NMAX + 5][KMAX + 5];
int fr[KMAX + 5];

inline bool ok(){
    for(int i = 1;i <= k;i++){
        if(fr[i] == 0){
            return false;
        }
    }
    return true;
}

int main(){

    scanf("%d\n",&p);
    scanf("%d\n",&t);

    while(t--){
        scanf("%d %d\n",&n,&k);

        for(int i = 1;i <= k;i++){
            fr[i] = 0;
        }

        dp1[0] = 0;
        dp2[0] = 1;

        int lst = 0;
        int pref_max = -1e9;
        int pref_cnt = 0;
        for(int i = 1;i <= n;i++){
            fgets(conf[i] + 1,KMAX + 5,stdin);
            for(int j = 1;j <= k;j++){
                if(conf[i][j] == '1'){
                    fr[j]++;
                }
            }
            while(ok()){
                for(int j = 1;j <= k;j++){
                    if(conf[lst][j] == '1'){
                        fr[j]--;
                    }
                }
                if(lst >= 1){
                    if(pref_max < dp1[lst - 1]){
                        pref_max = dp1[lst - 1];
                        pref_cnt = dp2[lst - 1];
                    }else if(pref_max == dp1[lst - 1]){
                        pref_cnt += dp2[lst - 1];
                        if(pref_cnt >= MOD){
                            pref_cnt -= MOD;
                        }
                    }
                }
                lst++;
            }
            dp1[i] = pref_max + 1;
            dp2[i] = pref_cnt;
        }
        printf("%d\n",(p == 1 ? dp1[n]:dp2[n]));
    }


    return 0;
}
