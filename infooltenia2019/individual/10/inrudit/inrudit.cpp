#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

FILE *f = fopen("inrudit.in","r");
FILE *g = fopen("inrudit.out","w");

const int LIM = 1e9 + 10;
const int NMAX = 1e3;
const int SIGMA = 10;

int dp[NMAX + 5];///common pref;

vector<int> fr;

int k;
char n[1005];

int comb[1005][1005];

int numbers_with_fr(const vector<int> &fr){
    int ans = 1;
    int total = 0;
    
    for(auto it:fr){
        int mult = comb[it + total][total];

        if(ans < LIM / mult){
            ans *= mult;
        }
        else{
            ans = LIM;
        }

        total += it;
    }

    return ans;
}

char ans[NMAX + 5];

int main(){

    for(int i = 0;i <= NMAX;i++){
        comb[i][0] = comb[i][i] = 1;
        for(int j = 1;j < i;j++){
            if(comb[i - 1][j - 1] < LIM - comb[i - 1][j]){
                comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];
            }
            else{
                comb[i][j] = LIM;
            }
        }
    }

    fscanf(f,"%d\n",&k);
    fgets(n + 1,NMAX + 5,f);
    int len = strlen(n + 1);
    len -= (n[len] == '\n');

    vector<int> fr(SIGMA);

    dp[len] = 0;

    for(int i = len;i >= 1;i--){
        fr[n[i] - '0']++;
        dp[i - 1] = dp[i];
        for(int x = n[i] - '0' + 1;x < SIGMA;x++){
            if(fr[x]){
                fr[x]--;
                int tmp = numbers_with_fr(fr);
                if(dp[i - 1] < LIM - tmp){
                    dp[i - 1] += tmp;
                }
                else{
                    dp[i - 1] = LIM;
                }
                fr[x]++;
            }
        }
    } 

    if(dp[0] < k){
        fprintf(g,"-1");
        return 0;
    }

    int pref = len + 1;

    for(int i = 1;i <= len;i++){
        if(dp[i] < k){
            k -= dp[i];
            pref = i - 1;
            break;
        }
    }

    fr = vector<int>(SIGMA,0);

    for(int i = 1;i <= pref;i++){
        ans[i] = n[i];
    }

    for(int i = pref + 1;i <= len;i++){
        fr[n[i] - '0']++;
    }

    if(pref + 1 <= len){
        for(int cf = n[pref + 1] - '0' + 1;cf < SIGMA;cf++){
            if(fr[cf]){
                fr[cf]--;
                int tmp = numbers_with_fr(fr);
                if(k > tmp){
                    k -= tmp;
                }
                else{
                    ans[pref + 1] = cf + '0';
                    break;
                }
                fr[cf]++;
            }    
        }
    }

    for(int i = pref + 2;i <= len;i++){
        for(int cf = 0;cf < SIGMA;cf++){
            if(fr[cf]){
                fr[cf]--;
                int tmp = numbers_with_fr(fr);

                if(k > tmp){
                    k -= tmp;
                }
                else{
                    ans[i] = cf + '0';
                    break;
                }
                fr[cf]++;
            }
        }
    }

    fputs(ans + 1,g);

    fclose(f);
    fclose(g);

    return 0;
}
