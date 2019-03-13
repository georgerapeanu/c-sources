#include <cstdio>
#include <cstring>
#include <deque>

using namespace std;

FILE *f = fopen("anagrame.in","r");
FILE *g = fopen("anagrame.out","w");

const int NMAX = 1e5;
const int SIGMA = 26;

int t;
char c[NMAX + 5];
char s[NMAX + 5];

int fr_s[SIGMA + 5];

int fst[NMAX + 5];
int dp[NMAX + 5];

int pref_fr[SIGMA + 5][NMAX + 5];

bool ok(int st,int dr){
    for(int j = 0;j < SIGMA;j++){
        if(pref_fr[j][dr] - pref_fr[j][st - 1] < fr_s[j]){
            return false;
        }
    }

    return true;
}

int tmp_fr[SIGMA + 5];

int n,m;

int sta[NMAX + 5];
int len = 0;

int solve(int st,int dr){
    for(int i = 0; i <= SIGMA;i++){
        tmp_fr[i] = fr_s[i];
    }
    len = 0;
    for(int i = st;i <= dr;i++){
        if(tmp_fr[c[i] - 'a'] == 0){
            continue;
        }
        while(len && c[sta[len]] > c[i] && pref_fr[c[sta[len]] - 'a'][dr] - pref_fr[c[sta[len]] - 'a'][i] >=
            tmp_fr[c[sta[len]] - 'a'] + 1){
            tmp_fr[c[sta[len]] - 'a']++;
            len--;
        }
        sta[++len] = i;
        tmp_fr[c[i] - 'a']--;
    }

    for(int i = 1;i <= len;i++){
        fprintf(g,"%c",c[sta[i]]);
    }

    return sta[len];
}

int main(){
    fscanf(f,"%d\n",&t);
    fgets(c + 1,NMAX + 5,f);
    fgets(s + 1,NMAX + 5,f);

    n = strlen(c + 1);n -= (c[n] == '\n');
    m = strlen(s + 1);m -= (s[m] == '\n');

    for(int i = 1;i <= m;i++){
        fr_s[s[i] - 'a']++;
    }

    for(int i = 1;i <= n;i++){
        pref_fr[c[i] - 'a'][i]++;
        for(int j = 0;j < SIGMA;j++){
            pref_fr[j][i] += pref_fr[j][i - 1];
        }
    }

    int dr = n;

    for(int i = n;i >= 1;i--){
        dp[i] = dp[i + 1];

        while(ok(i,dr)){
            dr--;
        }

        dp[i] = (dr == n ? -1:dp[dr + 2]) + 1;
    }

    if(t == 1){
        fprintf(g,"%d",dp[1]);
    }
    else{

        for(int i = 1;i <= n;i++){
            if(!fst[dp[i]]){
                fst[dp[i]] = i;
            }
        }
        int ult = 0;
        dp[0] = dp[1];
        while(dp[ult]){
            int snd = (dp[ult] <= 1 ? n:fst[dp[ult] - 2] - 2);
            int fst = ult + 1;
            ult = solve(fst,snd);
        }
    }

    fclose(f);
    fclose(g);
    return 0;
}
