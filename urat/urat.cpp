#include <cstdio>

using namespace std;

FILE *f = fopen("urat.in","r");
FILE *g = fopen("urat.out","w");

const int MOD = 543217;

int n;

long long ans_a = 0;
int ans_b = 0;
int ans_c[500005];
int tmp_c[500005];
int main() {

    fscanf(f,"%d",&n);

    if(n % 2 == 0) {
        ///(-1,1) case
        {
            long long l_ans_a = (n / 2 + 1) - (n / 2);
            int l_ans_b = 1;
            tmp_c[1] = n / 2;
            tmp_c[n] = n / 2 + 1;
            for(int i = 1; i < n / 2; i++) {
                l_ans_a -= 2 * i;
                l_ans_b = 1LL * l_ans_b * i % MOD;
            }
            for(int i = n / 2 + 2; i <= n; i++) {
                l_ans_a += 2 * i;
                l_ans_b = 1LL * l_ans_b * (i - (n / 2 + 1)) % MOD;
            }
            int st = 1,dr = n;
            for(int i = 2; i < n; i++) {
                if(i % 2 == 0) {
                    tmp_c[i] = dr--;
                }
                else {
                    tmp_c[i] = st++;
                }
            }
            if(ans_a < l_ans_a) {
                ans_a = l_ans_a;
                ans_b = l_ans_b;
                for(int i = 1; i <= n; i++)ans_c[i] = tmp_c[i];
            }
            else if(ans_a == l_ans_a) {
                ans_b = (ans_b + l_ans_b) % MOD;
            }
        }
        ///(1,-1) case
        {
            long long l_ans_a = (n / 2 + 1) - (n / 2);
            int l_ans_b = 1;
            tmp_c[1] = n / 2 + 1;
            tmp_c[n] = n / 2;
            for(int i = 1; i < n / 2; i++) {
                l_ans_a -= 2 * i;
                l_ans_b = 1LL * l_ans_b * i % MOD;
            }
            for(int i = n / 2 + 2; i <= n; i++) {
                l_ans_a += 2 * i;
                l_ans_b = 1LL * l_ans_b * (i - (n / 2 + 1)) % MOD;
            }
            int st = 1,dr = n;
            for(int i = 2; i < n; i++) {
                if(i % 2 == 0) {
                    tmp_c[i] = st++;
                }
                else {
                    tmp_c[i] = dr--;
                }
            }
            if(ans_a < l_ans_a) {
                ans_a = l_ans_a;
                ans_b = l_ans_b;
                for(int i = 1; i <= n; i++)ans_c[i] = tmp_c[i];
            }
            else if(ans_a == l_ans_a) {
                ans_b = (ans_b + l_ans_b) % MOD;
            }
        }
    }
    else {
        ///(-1,-1) case
        {
            long long l_ans_a = -(n / 2 + 1) - (n / 2);
            int l_ans_b = 2;
            tmp_c[1] = n / 2;
            tmp_c[n] = n / 2 + 1;
            for(int i = 1; i < n / 2; i++) {
                l_ans_a -= 2 * i;
                l_ans_b = 1LL * l_ans_b * i % MOD;
            }
            for(int i = n / 2 + 2; i <= n; i++) {
                l_ans_a += 2 * i;
                l_ans_b = 1LL * l_ans_b * (i - (n / 2 + 1)) % MOD;
            }
            int st = 1,dr = n;
            for(int i = 2; i < n; i++) {
                if(i % 2 == 0) {
                    tmp_c[i] = dr--;
                }
                else {
                    tmp_c[i] = st++;
                }
            }
            if(ans_a < l_ans_a) {
                ans_a = l_ans_a;
                ans_b = l_ans_b;
                for(int i = 1; i <= n; i++)ans_c[i] = tmp_c[i];
            }
            else if(ans_a == l_ans_a) {
                ans_b = (ans_b + l_ans_b) % MOD;
            }
        }
        ///(1,1) case
        {
            long long l_ans_a = (n / 2 + 1) + (n / 2 + 2);
            int l_ans_b = 2;
            tmp_c[1] = n / 2 + 1;
            tmp_c[n] = n / 2 + 2;
            for(int i = 1; i < n / 2 + 1; i++) {
                l_ans_a -= 2 * i;
                l_ans_b = 1LL * l_ans_b * i % MOD;
            }
            for(int i = n / 2 + 3; i <= n; i++) {
                l_ans_a += 2 * i;
                l_ans_b = 1LL * l_ans_b * (i - (n / 2 + 2)) % MOD;
            }
            int st = 1,dr = n;
            for(int i = 2; i < n; i++) {
                if(i % 2 == 0) {
                    tmp_c[i] = st++;
                }
                else {
                    tmp_c[i] = dr--;
                }
            }
            if(ans_a < l_ans_a) {
                ans_a = l_ans_a;
                ans_b = l_ans_b;
                for(int i = 1; i <= n; i++)ans_c[i] = tmp_c[i];
            }
            else if(ans_a == l_ans_a) {
                ans_b = (ans_b + l_ans_b) % MOD;
            }
        }
    }

    fprintf(g,"%lld\n%d\n",ans_a,ans_b);

    for(int i = 1; i <= n; i++)fprintf(g,"%d ",ans_c[i]);

    fclose(f);
    fclose(g);

    return 0;
}
