#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int BASE = 3;
const int MOD1 = 1e9 + 7;
const int MOD2 = 1e9 + 9;
const int NMAX = 1000;

int p,t;
int n;
char a[NMAX + 5][NMAX + 5];
int cnt_col[NMAX + 5];
int cnt_row[NMAX + 5];

struct hash_t{
    int h1;
    int h2;

    hash_t(){
        h1 = h2 = 0;
    }

    void append(int val){
        h1 = 1LL * (h1 + val) * BASE % MOD1;
        h2 = 1LL * (h2 + val) * BASE % MOD2;
    }

    bool operator < (const hash_t &other)const{
        if(h1 != other.h1){
            return h1 < other.h1;
        }
        return h2 < other.h2;
    }

    bool operator == (const hash_t &other)const{
        return h1 == other.h1 && h2 == other.h2;
    }
    
    bool operator != (const hash_t &other)const{
        return h1 != other.h1 || h2 != other.h2;
    }
};

pair<hash_t,int> row_hash[NMAX + 5];
pair<hash_t,int> col_hash[NMAX + 5];


struct query_t{
    char type;
    int x,y;
};

vector<query_t> solve(pair<hash_t,int> stuff[],char type){
    int fst_half[] = {0,0};  
    int snd_half[] = {0,0};  

    for(int i = 1;i <= n / 2;i++){
        fst_half[stuff[i].second & 1]++;
    }
    for(int i = n / 2 + 1;i <= n;i++){
        snd_half[stuff[i].second & 1]++;
    }

    if(fst_half[1] + snd_half[0] > fst_half[0] + snd_half[1]){
        reverse(stuff + 1,stuff + 1 + n);
    }

    int j = n / 2 + 1;
    vector<query_t> ans;
    for(int i = 1;i <= n / 2;i++){
        if(stuff[i].second & 1){
            while(stuff[j].second & 1){
                j++;
            }
            ans.push_back({type,stuff[i].second,stuff[j].second});
            j++;
        }
    }

    return ans;
}

int main(){

    scanf("%d %d\n",&p,&t);

    while(t--){
        scanf("%d\n",&n);

        for(int i = 1;i <= n;i++){
            cnt_col[i] = cnt_row[i] = 0;
            row_hash[i] = col_hash[i] = {hash_t(),i};
            fgets(a[i] + 1,NMAX + 5,stdin);
        }

        for(int i = 1;i <= n;i++){
            for(int j = 1;j <= n;j++){
                cnt_row[i] += (a[i][j] == '1');
                cnt_col[j] += (a[i][j] == '1');
                row_hash[i].first.append(a[i][j] - '0');
                col_hash[j].first.append(a[i][j] - '0');
            }
        }

        bool ok = true;

        for(int i = 1;i <= n;i++){
            ok &= (cnt_row[i] == n / 2);
            ok &= (cnt_col[i] == n / 2);
        }

        sort(row_hash + 1,row_hash + 1 + n);
        sort(col_hash + 1,col_hash + 1 + n);

        for(int i = 1;i <= n;i++){
            if(i == n / 2 + 1){
                if(row_hash[i].first == row_hash[i - 1].first || col_hash[i].first == col_hash[i - 1].first){
                    ok = false;
                }
            }else if(i > 1){
                if(row_hash[i].first != row_hash[i - 1].first || col_hash[i].first != col_hash[i - 1].first){
                    ok = false;
                }
            }
        }

        if(ok == false){
            printf("0\n");
        }else{
            if(p == 1){
                printf("1\n");
            }else{
                vector<query_t> a = solve(row_hash,'L');
                vector<query_t> b = solve(col_hash,'C');

                for(auto it:b){
                    a.push_back(it);
                }
                printf("%d\n",(int)a.size());
                if(p == 3){
                    for(auto it:a){
                        printf("%c %d %d\n",it.type,it.x,it.y);
                    }
                }
            }
        }
    }

    return 0;
}
