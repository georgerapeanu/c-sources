#include <fstream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
ifstream f("permbit.in");
ofstream g("permbit.out");
string S[1000005];
int C;
int N,M;
const int MOD1 = (1e9) + 7;
const int MOD2 = 666013;
const int BASE = 31;
const int IBASE1 = 129032259;
const int IBASE2 = 515623;
int pw1[1000005];
int pw2[1000005];
struct hsh{
    int h1,h2,len;
    void add_front(char c){
        h1 = (1LL * (c - 'a' + 1) * pw1[len] + h1) % MOD1;
        h2 = (1LL * (c - 'a' + 1) * pw2[len] + h2) % MOD2;
        len++;
    }
    void add_back(char c){
        h1 = (1LL * h1 * BASE + h1) % MOD1;
        h2 = (1LL * h2 * BASE + h2) % MOD2;
        len++;
    }
    void del_front(char c){
        len--;
        h1 = ((h1 - 1LL * (c - 'a' + 1) * pw1[len]) % MOD1 + MOD1) % MOD1;
        h2 = ((h2 - 1LL * (c - 'a' + 1) * pw2[len]) % MOD2 + MOD2) % MOD2;
    }
    void del_back(char c){
        len--;
        h1 = (1LL * (h1 - (c - 'a' + 1)) * IBASE1 % MOD1 + MOD1) % MOD1;
        h2 = (1LL * (h2 - (c - 'a' + 1)) * IBASE2 % MOD2 + MOD2) % MOD2;
    }
    bool operator == (const hsh &other)const{
        return len == other.len && h1 == other.h1 && h2 == other.h2;
    }
    bool operator < (const hsh &other)const{
        if(len != other.len){
            return len < other.len;
        }
        if(h1 != other.h1){
            return h1 < other.h1;
        }
        return h2 < other.h2;
    }
};
hsh P[1000005];
hsh F[1000005];
map<hsh,vector<int> > MA;
int main(){
    pw1[0] = pw2[0] = 1;
    for(int i = 1;i <= 1000000;i++){
        pw1[i] = 1LL * pw1[i - 1] * BASE % MOD1;
        pw2[i] = 1LL * pw2[i - 1] * BASE % MOD2;
    }
    f >> C;
    f >> N >> M;
    for(int i = 1;i <= N;i++){
        f >> S[i];
        S[i] = " " + S[i];
    }
    for(int j = 1;j <= M;j++){
        P[j] = {0,0,0};
        F[j] = {0,0,0};
        for(int i = 1;i <= N;i++){
            if(i < N){
                P[j].add_back(S[i][j]);
            }
            if(i > 1){
                F[j].add_back(S[i][j]);
            }
        }
    }
    f.close();
    g.close();
    return 0;
}
