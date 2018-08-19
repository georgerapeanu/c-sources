#include <cstdio>
#include <set>
#include <vector>

using namespace std;
int D[1000006];
int rez;
long long AIB[300005];
int stage[300005];
int V[300005];
int N,Q;
void u(int pos,int val){
    for(;pos <= N;pos += (-pos) & pos){
        AIB[pos] += val;
    }
}
long long q(int pos){
    long long rez = 0;
    for(;pos;pos -= (-pos) & pos){
        rez += AIB[pos];
    }
    return rez;
}
set<int> S;
int main()
{
    for(int i = 1;i <= 1e6;i++){
        for(int j = i;j <= 1e6;j += i){
            D[j]++;
        }
    }
    scanf("%d %d",&N,&Q);
    for(int i = 1;i <= N;i++){
        scanf("%d",&V[i]);
        stage[i] = 1;
        S.insert(i);
        u(i,V[i]);
    }
    while(Q--){
        int tip,l,r;
        scanf("%d %d %d",&tip,&l,&r);
        if(tip == 1){
            set<int> :: iterator it = S.lower_bound(l);
            vector<int> toErase;
            for(;it != S.end() && *it <= r;it++){
                stage[*it]++;
                if(stage[*it] > 7){
                    toErase.push_back(*it);
                }
                u(*it,-V[*it]);
                V[*it] = D[V[*it]];
                u(*it,V[*it]);
            }
            for(auto it:toErase){
                S.erase(it);
            }
        }
        else{
            printf("%I64d\n", q(r) - q(l - 1));
        }
    }

    return 0;
}
