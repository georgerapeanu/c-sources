#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5;
const int QMAX = 1e5;
const int VMAX = 1e6;

struct query_t{
    int x,y;
    int k;
    int id;
};

int n,q;
vector<int> pos[VMAX + 5];
vector<query_t> query_pos[VMAX + 5];
bool marked[VMAX + 5];
int mobius[VMAX + 5];

int ans[QMAX + 5];

class FenwickTree{
    int n;
    vector<long long> aib;
public:

    FenwickTree(int n){
        this->n = n;
        aib = vector<long long>(n + 1);
    }

    void update(int pos,int val){
        for(;pos <= n;pos += (-pos) & pos){
            aib[pos] += val;
        }
    }

    long long query(int pos){
        long long answer = 0;

        for(;pos;pos -= (-pos) & pos){
            answer += aib[pos];
        }

        return answer;
    }
};

int main(){

    scanf("%d",&n);

    for(int i = 1;i <= n;i++){
        int value;
        scanf("%d",&value);
        pos[value].push_back(i);
    }

    scanf("%d",&q);

    for(int i = 1;i <= q;i++){
        query_t tmp;
        scanf("%d %d %d",&tmp.x,&tmp.y,&tmp.k);
        tmp.id = i;
        query_pos[tmp.k].push_back(tmp);
    }

    for(int i = 1;i <= VMAX;i++){
        mobius[i] = 1;
    }

    for(int i = 2;i <= VMAX;i++){
        if(marked[i] == false){
            for(int j = i;j <= VMAX;j += i){
                marked[j] = true;
                mobius[j] *= -1;
            }
            for(long long j = 1LL * i * i;j <= VMAX;j += 1LL * i * i){
                mobius[j] = 0;
            }
        }
    }

    FenwickTree aib(n);

    for(int i = 1;i <= VMAX;i++){
        if(mobius[i]){
            for(int j = i;j <= VMAX;j += i){
                for(auto it:pos[j]){
                    aib.update(it,1);
                }
            }

            for(int j = i;j <= VMAX;j += i){
                for(auto it:query_pos[j]){
                    ans[it.id] += mobius[i] * (aib.query(it.y) - aib.query(it.x - 1));
                }
            }
            
            for(int j = i;j <= VMAX;j += i){
                for(auto it:pos[j]){
                    aib.update(it,-1);
                }
            }
        }
    }

    for(int i = 1;i <= q;i++){
        printf("%d\n",ans[i]);
    }

    return 0;
}
